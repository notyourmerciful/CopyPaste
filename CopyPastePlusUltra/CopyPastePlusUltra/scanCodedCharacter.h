#pragma once
//Some characters need to include a shift character, thus this object signals the code of
//that requirement

#include <Windows.h>

typedef struct scanCodedCharacter
{
	::WORD scanCodeValue;
	bool isShifted;
};