#pragma once
#include <Windows.h>
#include "scanCodedCharacter.h"

class scanCodeFinder
{
public:
	::scanCodedCharacter findScanCodeOfCharacter(char);
private:
	::scanCodedCharacter findScanCodeOfAlphabetCharacter(char);
	::scanCodedCharacter findScanCodeOfSpecialCharacter(char);
	::scanCodedCharacter findScanCodeOfNumberCharacter(char);
};