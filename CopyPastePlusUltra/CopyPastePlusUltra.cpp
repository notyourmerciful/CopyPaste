// CopyPastePlusUltra.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <Windows.h>
#include <iostream>
#include <string>
#include "ScanCodeDefines.h"
#include "scanCodeFinder.h"
#include "ClipboardCopyManager.h"

void runListener();
void typeTheOutput();
std::string GetClipboardText();
void typeEachLetterOfString(std::string);

scanCodeFinder codeFinder;


int main()
{
//	runListener();

	clipboardCopyManager copyManager;
	
	copyManager.spoolUp();

    return 0;
}
/*
void runListener()
{
	bool wasPressed = false;
	bool typeRequested = false;
	while (true)
	{
		if ( !wasPressed && (GetAsyncKeyState(VK_LSHIFT) && GetAsyncKeyState(VK_F2)))
		{
//			std::cout << "3 and 0 are held down\n\n\n\n\n\n";
//			std::cout << GetClipboardText() << std::endl;
//			typeTheOutput();
//			std::string fromClipboard = GetClipboardText();
//			typeEachLetterOfString(fromClipboard);
			wasPressed = true;
			typeRequested = true;
		}
		else if ((GetAsyncKeyState(VK_LSHIFT) || GetAsyncKeyState(VK_F2)))
		{

		}
		else if (typeRequested)
		{
			std::string fromClipboard = GetClipboardText();
			typeEachLetterOfString(fromClipboard);
			typeRequested = false;
		}
		else
		{
			wasPressed = false;
		}
	}
	return;
}


void typeTheOutput()
{
	INPUT ip;
	ip.type = INPUT_KEYBOARD;
	ip.ki.time = 0;
	ip.ki.wVk = 0;
	ip.ki.dwExtraInfo = 0;

	ip.ki.dwFlags = KEYEVENTF_SCANCODE;
	ip.ki.wScan = 0x1E;

	//press
	SendInput(1, &ip, sizeof(INPUT));

	//keyup
	ip.ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;
	SendInput(1, &ip, sizeof(INPUT));

	return;
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

void typeEachLetterOfString(std::string toType)
{
	for (char const &c : toType) {
		::scanCodedCharacter tempCodedCharacter = codeFinder.findScanCodeOfCharacter(c);
		typeCodedCharacter(tempCodedCharacter);
	}
	return;
}*/