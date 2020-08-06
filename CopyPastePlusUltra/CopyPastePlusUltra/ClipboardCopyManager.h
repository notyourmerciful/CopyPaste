#pragma once
#include <Windows.h>
#include <vector>
#include "scanCodedCharacter.h"
#include "NumPadCombination.h"
#include "scanCodeFinder.h"

class clipboardCopyManager
{
public:
//	int processKeyStates();	//Return: state change delta

	void spoolUp();	//This is the function that runs the program. Statemachine

	typedef struct scanCodedMessage	//Represents a message processed to a vector of scan codes and ready to send
	{
		std::vector<scanCodedCharacter> message;
	};

	clipboardCopyManager();//constructor
private:
	bool keyCombinationCopyCheck();	//True if copy key combination checked
	bool keyCombinationPasteCheck();//True if paste key combination checked
	bool keyCombinationPastePattern2Check();//True if paste patter 2 key combination checked
	bool keyCombinationPastePattern3Check();//True if paste patter 2 key combination checked
	bool keyQuickPasteCheck();//Used for instant pasts from clipboard
	bool keyQuickAltPasteCheck();//Used for instant pasts from clipboard
	bool keyQuickPasteCheck(int);//Used to test against a provided key
	numpadCombination numpadCombinationCheck();//Returns two buttons held down on numpad
	void storeScanCodedMessageInTree(numpadCombination, scanCodedMessage);
	scanCodedMessage translateToScanCodedMessage(std::string);
	scanCodedMessage retrieveScanCodedMessage(numpadCombination);
	bool checkForKeyup();//use for state transition act on keydowns
//	void buildTreeOfScanCodeMessages();	//This function sets up the storage for the scan coded messages


	typedef struct scanCodedMessageTreeNode
	{
		scanCodedMessageTreeNode *root;
		scanCodedMessageTreeNode *parent;
		std::vector<scanCodedMessageTreeNode *> children;//lowest number first. This means never start by finding 9
		scanCodedMessage message;
		int value;	//This should be self-evident by looking at the indexing
	};

	enum stateMachineState
	{
		copyRequestedKeyDown,//Wait for key up
		pasteRequestedKeyDown,//wait for key up
		pasteRequestedPattern2KeyDown,//wait for key up
		pasteRequestedPattern3KeyDown,//wait for key up
		pasteRequestedQuickKeyDown,//wait for key up
		pasteRequestedAltQuickKeyDown,//wait for key up
		pasteRequestedBackupSuccessfulKeyDown,//wait for key up
		pasteRequestedBackupDayBehindKeyDown,//wait for key up
		pasteRequestedStartedNASBackupKeyDown,//wait for key up
		pasteRequestedStartedCloudBackupKeyDown,//wait for key up
		pasteRequestedStartedOfflineBackupKeyDown,//wait for key up
		waitingForInput	//Default idle

	};

	scanCodeFinder hardwareDecoder;

	scanCodedMessageTreeNode *messagesStorage;
};
