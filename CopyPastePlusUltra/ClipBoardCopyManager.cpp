#pragma once

#include <Windows.h>
#include <vector>
#include "ClipboardCopyManager.h"
#include "ScanCodeDefines.h"

clipboardCopyManager::clipboardCopyManager()
{
	messagesStorage = new scanCodedMessageTreeNode;

	for (int i = 0; i < 9; i++)
	{
		messagesStorage->children.push_back(new scanCodedMessageTreeNode);//0-8
	}

	for (int i = 0; i < 9; i++)
	{
		for (int k = i + 1; k < 10; k++)
		{
			messagesStorage->children[i]->children.push_back(new scanCodedMessageTreeNode);
		}
	}
}


bool clipboardCopyManager::keyCombinationCopyCheck()
{
	SHORT temp = GetAsyncKeyState('C');
	
	if (GetAsyncKeyState('C'))//Letters need to be capital for Windows to detect them properly
	{
		if (GetAsyncKeyState(VK_LCONTROL))
		{
			if (GetAsyncKeyState(VK_LMENU))
			{
				return true;
			}
		}
	}
	return false;
}

bool clipboardCopyManager::keyCombinationPasteCheck()
{
	if (GetAsyncKeyState(VK_LCONTROL) && GetAsyncKeyState(VK_LMENU) && GetAsyncKeyState('X'))
	{
		return true;
	}
	return false;
}

bool clipboardCopyManager::keyCombinationPastePattern2Check()
{
	if (GetAsyncKeyState(VK_LCONTROL) && GetAsyncKeyState(VK_LMENU) && GetAsyncKeyState('Z'))
	{
		return true;
	}
	return false;
}

bool clipboardCopyManager::keyCombinationPastePattern3Check()
{
	if (GetAsyncKeyState(VK_LCONTROL) && GetAsyncKeyState(VK_LMENU) && GetAsyncKeyState('A'))
	{
		return true;
	}
	return false;
}

numpadCombination clipboardCopyManager::numpadCombinationCheck()
{
	int num1 = -1;
	int num2 = -1;
	int start = VK_NUMPAD0;
	for (int i = 0; i < 10; i++)
	{
		if (GetAsyncKeyState(start + i))
		{
			num1 = i;
			continue;
		}
	}

	if (num1 == -1)
	{
		return numpadCombination{-1, -1};	//This signals an invalid combination
	}

	for (int i = 0; i < 10; i++)
	{
		if (GetAsyncKeyState(start + i))
		{
			if (i != num1)
			{
				num2 = i;
			}
		}
	}

	if (num2 == -1 || num1 == num2)
	{
		return numpadCombination{ -1, -1 };	//This signals an invalid combination
	}

	if (num2 < num1)
	{
		int temp = num2;
		num2 = num1;
		num1 = temp;
	}

	return numpadCombination{ num1, num2 };
}

void clipboardCopyManager::storeScanCodedMessageInTree(numpadCombination location, scanCodedMessage message)
{
	messagesStorage->children[location.num1]->children[location.num2 - location.num1 - 1]->message = message;
	return;
}

clipboardCopyManager::scanCodedMessage clipboardCopyManager::translateToScanCodedMessage(std::string toTranslate)
{
	if (toTranslate.length() == 0)
	{
		scanCodedMessage temp;
		return temp;
	}

	scanCodedMessage toReturn;

	for (int i = 0; i < toTranslate.length(); i++)
	{
		toReturn.message.push_back(hardwareDecoder.findScanCodeOfCharacter(toTranslate[i]));
	}
	return toReturn;
}

bool clipboardCopyManager::checkForKeyup()
{
	//Don't type while special characters are pressed. Note: we only use the left side right now
	if (GetAsyncKeyState(VK_LCONTROL) || GetAsyncKeyState(VK_LMENU) || GetAsyncKeyState(VK_LSHIFT))
	{
		return false;
	}
	else
	{
		return true;
	}
}



std::string GetClipboardText()
{
	// Try opening the clipboard
	if (!OpenClipboard(nullptr))
	{
		throw 1;
	}

	// Get handle of clipboard object for ANSI text
	HANDLE hData = GetClipboardData(CF_TEXT);
	if (hData == nullptr)
	{
		throw 2;
	}

	// Lock the handle to get the actual text pointer
	char * pszText = static_cast<char*>(GlobalLock(hData));
	if (pszText == nullptr)
	{
		throw 3;
	}

	// Save text in a string class instance
	std::string text(pszText);

	// Release the lock
	GlobalUnlock(hData);

	// Release the clipboard
	CloseClipboard();

	return text;
}

clipboardCopyManager::scanCodedMessage clipboardCopyManager::retrieveScanCodedMessage(numpadCombination toFind)
{
	scanCodedMessage toReturn = messagesStorage->children[toFind.num1]->children[toFind.num2 - toFind.num1 - 1]->message;
	return toReturn;
}

void typeCodedCharacter(::scanCodedCharacter toType)
{
	if (toType.scanCodeValue == 0)
	{
		return;	//Do not print
	}


	INPUT ip[2];	//First is shift second is character
	ip[1].type = INPUT_KEYBOARD;
	ip[1].ki.time = 0;
	ip[1].ki.wVk = 0;
	ip[1].ki.dwExtraInfo = 0;

	ip[1].ki.dwFlags = KEYEVENTF_SCANCODE;
	ip[1].ki.wScan = toType.scanCodeValue;

	ip[0].type = INPUT_KEYBOARD;
	ip[0].ki.time = 0;
	ip[0].ki.wVk = 0;
	ip[0].ki.dwExtraInfo = 0;

	ip[0].ki.dwFlags = KEYEVENTF_SCANCODE;
	ip[0].ki.wScan = scanCode_specialRightShift;

	if (toType.isShifted)
	{
		//press
		SendInput(2, &ip[0], sizeof(INPUT));

		//keyup
		ip[0].ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;
		ip[1].ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;
		SendInput(2, &ip[0], sizeof(INPUT));
	}
	else
	{
		//press
		SendInput(1, &ip[1], sizeof(INPUT));

		//keyup
		ip[1].ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;
		SendInput(1, &ip[1], sizeof(INPUT));
	}


	return;
}


//EXPERIMENTAL: theory: Kaseya is not capturing the shift key properly because of the order the keydowns are sent to the OS.
//To deal with this I am sending a shift on either side of the payload character.
void typeCodedCharacterPattern2(::scanCodedCharacter toType)
{
	if (toType.scanCodeValue == 0)
	{
		return;	//Do not print
	}


	INPUT ip[3];	//First is shift second is character
	ip[2].type = INPUT_KEYBOARD;
	ip[2].ki.time = 0;
	ip[2].ki.wVk = 0;
	ip[2].ki.dwExtraInfo = 0;

	ip[2].ki.dwFlags = KEYEVENTF_SCANCODE;
	ip[2].ki.wScan = scanCode_specialRightShift;

	ip[1].type = INPUT_KEYBOARD;
	ip[1].ki.time = 0;
	ip[1].ki.wVk = 0;
	ip[1].ki.dwExtraInfo = 0;

	ip[1].ki.dwFlags = KEYEVENTF_SCANCODE;
	ip[1].ki.wScan = toType.scanCodeValue;

	ip[0].type = INPUT_KEYBOARD;
	ip[0].ki.time = 0;
	ip[0].ki.wVk = 0;
	ip[0].ki.dwExtraInfo = 0;

	ip[0].ki.dwFlags = KEYEVENTF_SCANCODE;
	ip[0].ki.wScan = scanCode_specialRightShift;

	if (toType.isShifted)
	{
		//press
		SendInput(3, &ip[0], sizeof(INPUT));

		//keyup
		ip[0].ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;
		ip[1].ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;
		ip[2].ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;
		SendInput(3, &ip[0], sizeof(INPUT));
	}
	else
	{
		//press
		SendInput(1, &ip[1], sizeof(INPUT));

		//keyup
		ip[1].ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;
		SendInput(1, &ip[1], sizeof(INPUT));
	}


	return;
}

//EXPERIMENTAL: theory: Kaseya is not printing shifted special characters properly due to the idea that it wants the shift key to
//be pressed seperately. To deal with this I am pressing the shift key and not sending the key up until after the payload character's
//keyup has been sent.
void typeCodedCharacterPattern3(::scanCodedCharacter toType)
{
	if (toType.scanCodeValue == 0)
	{
		return;	//Do not print
	}


	INPUT ip[2];	//First is shift second is character
	ip[1].type = INPUT_KEYBOARD;
	ip[1].ki.time = 0;
	ip[1].ki.wVk = 0;
	ip[1].ki.dwExtraInfo = 0;

	ip[1].ki.dwFlags = KEYEVENTF_SCANCODE;
	ip[1].ki.wScan = toType.scanCodeValue;

	ip[0].type = INPUT_KEYBOARD;
	ip[0].ki.time = 0;
	ip[0].ki.wVk = 0;
	ip[0].ki.dwExtraInfo = 0;

	ip[0].ki.dwFlags = KEYEVENTF_SCANCODE;
	ip[0].ki.wScan = scanCode_specialRightShift;

	if (toType.isShifted)
	{
		//press
		SendInput(1, &ip[0], sizeof(INPUT));//Keydown for the shift key
		SendInput(1, &ip[1], sizeof(INPUT));//Keydown for the payload character

		//keyup
		ip[0].ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;
		ip[1].ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;
		SendInput(1, &ip[1], sizeof(INPUT));//Send keyup for the payload character
		SendInput(1, &ip[0], sizeof(INPUT));//Now send shift key keyup.
	}
	else
	{
		//press
		SendInput(1, &ip[1], sizeof(INPUT));

		//keyup
		ip[1].ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;
		SendInput(1, &ip[1], sizeof(INPUT));
	}


	return;
}

void typeScanCodedMessage(clipboardCopyManager::scanCodedMessage toType)
{
	int standardPause = 10;//millis

	for (int i = 0; i < toType.message.size(); i++) {
		Sleep(10);
		typeCodedCharacter(toType.message[i]);
	}
	return;
}
void typeScanCodedMessagePattern2(clipboardCopyManager::scanCodedMessage toType)
{
	int standardPause = 10;//millis

	for (int i = 0; i < toType.message.size(); i++) {
		Sleep(10);
		typeCodedCharacterPattern2(toType.message[i]);
	}
	return;
}
void typeScanCodedMessagePattern3(clipboardCopyManager::scanCodedMessage toType)
{
	int standardPause = 10;//millis

	for (int i = 0; i < toType.message.size(); i++) {
		Sleep(10);
		typeCodedCharacterPattern3(toType.message[i]);
	}
	return;
}

void clipboardCopyManager::spoolUp()
{
	stateMachineState currentState = stateMachineState::waitingForInput;
	numpadCombination currentCombination{ 0,0 };

	while (true)
	{
		switch (currentState)
		{
		case copyRequestedKeyDown:
			if (checkForKeyup())
			{
				currentState = stateMachineState::waitingForInput;
				std::string toStore = GetClipboardText();
				if (toStore.length() > 0)
				{
					scanCodedMessage tempMessage = translateToScanCodedMessage(toStore);
					if (currentCombination.num1 != -1 && currentCombination.num2 != -1 && (currentCombination.num1 != currentCombination.num2))
					{
						storeScanCodedMessageInTree(currentCombination, tempMessage);
					}
				}
			}
			break;
		case pasteRequestedKeyDown:
			if (checkForKeyup())
			{
				currentState = stateMachineState::waitingForInput;
				if (currentCombination.num1 != -1 && currentCombination.num2 != -1 && (currentCombination.num1 != currentCombination.num2))
				{
					scanCodedMessage toType = retrieveScanCodedMessage(currentCombination);
					typeScanCodedMessage(toType);
				}
			}
			break;
		case pasteRequestedPattern2KeyDown:
			if (checkForKeyup())
			{
				currentState = stateMachineState::waitingForInput;
				if (currentCombination.num1 != -1 && currentCombination.num2 != -1 && (currentCombination.num1 != currentCombination.num2))
				{
					scanCodedMessage toType = retrieveScanCodedMessage(currentCombination);
					typeScanCodedMessagePattern2(toType);
				}
			}
			break;
		case pasteRequestedPattern3KeyDown:
			if (checkForKeyup())
			{
				currentState = stateMachineState::waitingForInput;
				if (currentCombination.num1 != -1 && currentCombination.num2 != -1 && (currentCombination.num1 != currentCombination.num2))
				{
					scanCodedMessage toType = retrieveScanCodedMessage(currentCombination);
					typeScanCodedMessagePattern3(toType);
				}
			}
			break;
		case waitingForInput:
			currentCombination.num1 = -1;//Reset to sentinel values
			currentCombination.num2 = -1;
			if (keyCombinationCopyCheck())
			{
				numpadCombination tempCombination = numpadCombinationCheck();

				//Wait for valid numpad combination
				if (tempCombination.num1 != -1 && tempCombination.num2 != -1 && (tempCombination.num1 != tempCombination.num2))
				{
					currentState = copyRequestedKeyDown;
					currentCombination = tempCombination;
				}
			}
			else if (keyCombinationPasteCheck())
			{
				numpadCombination tempCombination = numpadCombinationCheck();

				//Wait for valid numpad combination
				if (tempCombination.num1 != -1 && tempCombination.num2 != -1 && (tempCombination.num1 != tempCombination.num2))
				{
					currentState = pasteRequestedKeyDown;
					currentCombination = tempCombination;
				}

			}
			else if (keyCombinationPastePattern2Check())
			{
				numpadCombination tempCombination = numpadCombinationCheck();

				//Wait for valid numpad combination
				if (tempCombination.num1 != -1 && tempCombination.num2 != -1 && (tempCombination.num1 != tempCombination.num2))
				{
					currentState = pasteRequestedPattern2KeyDown;
					currentCombination = tempCombination;
				}

			}
			else if (keyCombinationPastePattern3Check())
			{
				numpadCombination tempCombination = numpadCombinationCheck();

				//Wait for valid numpad combination
				if (tempCombination.num1 != -1 && tempCombination.num2 != -1 && (tempCombination.num1 != tempCombination.num2))
				{
					currentState = pasteRequestedPattern3KeyDown;
					currentCombination = tempCombination;
				}

			}
			break;
		default:
			throw 11000;//This should never run
			break;
		}
		Sleep(1);//This should be adjustable and on a callback system
	}
}