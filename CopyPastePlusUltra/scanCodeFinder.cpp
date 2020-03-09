
#include "scanCodeFinder.h"
#include "ScanCodeDefines.h"


::scanCodedCharacter scanCodeFinder::findScanCodeOfCharacter(char toFind)
{
	if (isalpha(toFind))
	{
		return this->findScanCodeOfAlphabetCharacter(toFind);
	}
	else if(isdigit(toFind))
	{
		return this->findScanCodeOfNumberCharacter(toFind);
	}
	else
	{
		return this->findScanCodeOfSpecialCharacter(toFind);
	}
	return ::scanCodedCharacter{0, false};	//Error
}

::scanCodedCharacter scanCodeFinder::findScanCodeOfAlphabetCharacter(char toFind)
{
	::scanCodedCharacter toReturn{ 0, false };

	if (isupper(toFind))
	{
		toReturn.isShifted = true;
		toFind = tolower(toFind);
	}

	switch (toFind) {
	case 'a':
		toReturn.scanCodeValue = scanCode_a;
		break;
	case 'b':
		toReturn.scanCodeValue = scanCode_b;
		break;
	case 'c':
		toReturn.scanCodeValue = scanCode_c;
		break;
	case 'd':
		toReturn.scanCodeValue = scanCode_d;
		break;
	case 'e':
		toReturn.scanCodeValue = scanCode_e;
		break;
	case 'f':
		toReturn.scanCodeValue = scanCode_f;
		break;
	case 'g':
		toReturn.scanCodeValue = scanCode_g;
		break;
	case 'h':
		toReturn.scanCodeValue = scanCode_h;
		break;
	case 'i':
		toReturn.scanCodeValue = scanCode_i;
		break;
	case 'j':
		toReturn.scanCodeValue = scanCode_j;
		break;
	case 'k':
		toReturn.scanCodeValue = scanCode_k;
		break;
	case 'l':
		toReturn.scanCodeValue = scanCode_l;
		break;
	case 'm':
		toReturn.scanCodeValue = scanCode_m;
		break;
	case 'n':
		toReturn.scanCodeValue = scanCode_n;
		break;
	case 'o':
		toReturn.scanCodeValue = scanCode_o;
		break;
	case 'p':
		toReturn.scanCodeValue = scanCode_p;
		break;
	case 'q':
		toReturn.scanCodeValue = scanCode_q;
		break;
	case 'r':
		toReturn.scanCodeValue = scanCode_r;
		break;
	case 's':
		toReturn.scanCodeValue = scanCode_s;
		break;
	case 't':
		toReturn.scanCodeValue = scanCode_t;
		break;
	case 'u':
		toReturn.scanCodeValue = scanCode_u;
		break;
	case 'v':
		toReturn.scanCodeValue = scanCode_v;
		break;
	case 'w':
		toReturn.scanCodeValue = scanCode_w;
		break;
	case 'x':
		toReturn.scanCodeValue = scanCode_x;
		break;
	case 'y':
		toReturn.scanCodeValue = scanCode_y;
		break;
	case 'z':
		toReturn.scanCodeValue = scanCode_z;
		break;
	default:
		throw 9001;	//Logic error, this should never run
		break;
	}
	return toReturn;
}

::scanCodedCharacter scanCodeFinder::findScanCodeOfNumberCharacter(char toFind)
{
	::scanCodedCharacter toReturn{ 0, false };

	switch (toFind) {
	case '0':
		toReturn.scanCodeValue = scanCode_0;
		break;
	case '1':
		toReturn.scanCodeValue = scanCode_1;
		break;
	case '2':
		toReturn.scanCodeValue = scanCode_2;
		break;
	case '3':
		toReturn.scanCodeValue = scanCode_3;
		break;
	case '4':
		toReturn.scanCodeValue = scanCode_4;
		break;
	case '5':
		toReturn.scanCodeValue = scanCode_5;
		break;
	case '6':
		toReturn.scanCodeValue = scanCode_6;
		break;
	case '7':
		toReturn.scanCodeValue = scanCode_7;
		break;
	case '8':
		toReturn.scanCodeValue = scanCode_8;
		break;
	case '9':
		toReturn.scanCodeValue = scanCode_9;
		break;
	default:
		throw 9002;	//Logic error, this should never run
		break;
	}

	return toReturn;
}


//This one sucks
::scanCodedCharacter scanCodeFinder::findScanCodeOfSpecialCharacter(char toFind)
{
	::scanCodedCharacter toReturn{ 0, false };

	switch (toFind){
	case '`':
		toReturn.scanCodeValue = scanCode_specialApostrophe;
		break;
	case '~':
		toReturn.scanCodeValue = scancode_specialSquiggley;
		toReturn.isShifted = true;
		break;
	case '!':
		toReturn.scanCodeValue = scancode_specialExclamationMark;
		toReturn.isShifted = true;
		break;
	case '@':
		toReturn.scanCodeValue = scancode_specialAtSymbol;
		toReturn.isShifted = true;
		break;
	case '#':
		toReturn.scanCodeValue = scancode_specialNumberSign;
		toReturn.isShifted = true;
		break;
	case '$':
		toReturn.scanCodeValue = scancode_specialDollarSign;
		toReturn.isShifted = true;
		break;
	case '%':
		toReturn.scanCodeValue = scancode_specialPercentSign;
		toReturn.isShifted = true;
		break;
	case '^':
		toReturn.scanCodeValue = scancode_specialCarrot;
		toReturn.isShifted = true;
		break;
	case '&':
		toReturn.scanCodeValue = scancode_specialAmpersand;
		toReturn.isShifted = true;
		break;
	case '*':
		toReturn.scanCodeValue = scancode_specialSplat;
		toReturn.isShifted = true;
		break;
	case '(':
		toReturn.scanCodeValue = scancode_specialLeftParentheses;
		toReturn.isShifted = true;
		break;
	case ')':
		toReturn.scanCodeValue = scancode_specialRightParenthese;
		toReturn.isShifted = true;
		break;
	case '-':
		toReturn.scanCodeValue = scanCode_specialMinus;
		break;
	case '_':
		toReturn.scanCodeValue = scancode_specialUnderline;
		toReturn.isShifted = true;
		break;
	case '=':
		toReturn.scanCodeValue = scanCode_specialEqualSign;
		break;
	case '+':
		toReturn.scanCodeValue = scancode_specialPlusSign;
		toReturn.isShifted = true;
		break;
	case '[':
		toReturn.scanCodeValue = scanCode_specialLeftSquareBrace;
		break;
	case '{':
		toReturn.scanCodeValue = scancode_specialLeftCurlyBrace;
		toReturn.isShifted = true;
		break;
	case ']':
		toReturn.scanCodeValue = scanCode_specialRightSquareBrace;
		break;
	case '}':
		toReturn.scanCodeValue = scancode_specialRightCurlyBrace;
		toReturn.isShifted = true;
		break;
	case ';':
		toReturn.scanCodeValue = scanCode_specialSemiColon;
		break;
	case ':':
		toReturn.scanCodeValue = scancode_specialColon;
		toReturn.isShifted = true;
		break;
	case '\'':
		toReturn.scanCodeValue = scanCode_specialSingleQuotes;
		break;
	case '"':
		toReturn.scanCodeValue = scancode_specialDoubleQuotes;
		toReturn.isShifted = true;
		break;
	case '\\':
		toReturn.scanCodeValue = scanCode_specialBackSlash;
		break;
	case '|':
		toReturn.scanCodeValue = scancode_specialPipe;
		toReturn.isShifted = true;
		break;
	case ',':
		toReturn.scanCodeValue = scanCode_specialComma;
		break;
	case '<':
		toReturn.scanCodeValue = scancode_specialLessThan;
		toReturn.isShifted = true;
		break;
	case '.':
		toReturn.scanCodeValue = scanCode_specialPeriod;
		break;
	case '>':
		toReturn.scanCodeValue = scancode_specialGreaterThan;
		toReturn.isShifted = true;
		break;
	case '/':
		toReturn.scanCodeValue = scanCode_specialForwardSlash;
		break;
	case '?':
		toReturn.scanCodeValue = scancode_specialQuestionMark;
		toReturn.isShifted = true;
		break;
	case ' ':
		toReturn.scanCodeValue = scanCode_specialSpaceBar;
		break;
	case 9:
		toReturn.scanCodeValue = scanCode_specialTab;
		break;
	case '\n':
		toReturn.scanCodeValue = scanCode_specialEnter;
		break;
	case '\r':	//Carriage return has no place in modern keyboard commands. Disregard
		toReturn.scanCodeValue = 0;	//Going to use this as a sentinel value for do not type
		break;
	default:
		throw 9003;	//Logic error, this should never run
		break;
	}

	return toReturn;	//Error
}