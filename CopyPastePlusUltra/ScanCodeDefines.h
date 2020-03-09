#pragma once

/*
Scan code map at: http://www.philipstorr.id.au/pcbook/book3/scancode.htm
*/

//Lowercase alphabet
#define scanCode_a 0x1E
#define scanCode_b 0x30
#define scanCode_c 0x2E
#define scanCode_d 0x20
#define scanCode_e 0x12
#define scanCode_f 0x21
#define scanCode_g 0x22
#define scanCode_h 0x23
#define scanCode_i 0x17
#define scanCode_j 0x24
#define scanCode_k 0x25
#define scanCode_l 0x26
#define scanCode_m 0x32
#define scanCode_n 0x31
#define scanCode_o 0x18
#define scanCode_p 0x19
#define scanCode_q 0x10
#define scanCode_r 0x13
#define scanCode_s 0x1F
#define scanCode_t 0x14
#define scanCode_u 0x16
#define scanCode_v 0x2F
#define scanCode_w 0x11
#define scanCode_x 0x2D
#define scanCode_y 0x15
#define scanCode_z 0x2C


//Numbers - top row
#define scanCode_0 0x0B
#define scanCode_1 0x02
#define scanCode_2 0x03
#define scanCode_3 0x04
#define scanCode_4 0x05
#define scanCode_5 0x06
#define scanCode_6 0x07
#define scanCode_7 0x08
#define scanCode_8 0x09
#define scanCode_9 0x0A

//Numpad
#define scanCode_NumPad0 0x52
#define scanCode_NumPad1 0x4f
#define scanCode_NumPad2 0x50
#define scanCode_NumPad3 0x51
#define scanCode_NumPad4 0x4B
#define scanCode_NumPad5 0x4C
#define scanCode_NumPad6 0x4D
#define scanCode_NumPad7 0x47
#define scanCode_NumPad8 0x48
#define scanCode_NumPad9 0x48
#define scanCode_numpadSlash 0xE04A	//Both bytes? Check the latch for special cases
#define scanCode_numpadSplat 0x7C
#define scanCode_numpadMinus 0x7B
#define scanCode_numpadPlus 0x79
#define scanCode_numpadPeriod 0x71

//Various
#define scanCode_specialESC 0x01
#define scanCode_specialF1 0x3B
#define scanCode_specialF2 0x3C
#define scanCode_specialF3 0x3D
#define scanCode_specialF4 0x3E
#define scanCode_specialF5 0x3F
#define scanCode_specialF6 0x40
#define scanCode_specialF7 0x41
#define scanCode_specialF8 0x42
#define scanCode_specialF9 0x43		//So this is the first input
#define scanCode_specialF10 0x44
#define scanCode_specialF11 0x78
#define scanCode_specialF12 0x07
//#define scanCode_specialPrintScreen 0x
#define scanCode_specialScrollLock 0x7E
#define scanCode_specialInsert 0xE070
#define scanCode_specialHome 0xE06C
#define scanCode_specialPageUp 0xE07D
#define scanCode_specialDelete 0xE071
#define scanCode_specialEnd 0xE069
#define scanCode_specialPageDown 0xE07A
#define scanCode_specialNumLock 0x77
#define scanCode_specialArrowUp 0xE075
#define scanCode_specialArrowDown 0xE072
#define scanCode_specialArrowLeft 0xE06B
#define scanCode_specialArrowRight 0xE074
#define scanCode_specialApostrophe 0x29
#define scanCode_specialMinus 0x0C
#define scanCode_specialEqualSign 0x0D
#define scanCode_specialBackSlash 0x2B
#define scanCode_specialTab 0x0f
#define scanCode_specialLeftSquareBrace 0x1A
#define scanCode_specialRightSquareBrace 0x1B
#define scanCode_specialEnter 0x1C
#define scanCode_specialCapsLock 0x58
#define scanCode_specialSemiColon 0x27
#define scanCode_specialSingleQuotes 0x28
#define scanCode_specialLeftShift 0x12
#define scanCode_specialComma 0x33
#define scanCode_specialPeriod 0x34
#define scanCode_specialForwardSlash 0x35
#define scanCode_specialRightShift 0x36
#define scanCode_specialLeftControl 0x14
#define scanCode_specialLeftAlt 0x11
#define scanCode_specialSpaceBar 0x39
#define scanCode_specialRightAlt 0xE011
#define scanCode_specialRightControl 0xE014


/*
Since certain characters are shifted versions of others this
section provides a mapping of applicable characters
*/

//Various shifted characters
const int scancode_specialSquiggley = scanCode_specialApostrophe;
const int scancode_specialExclamationMark = scanCode_1;
const int scancode_specialAtSymbol = scanCode_2;
const int scancode_specialNumberSign = scanCode_3;
const int scancode_specialDollarSign = scanCode_4;
const int scancode_specialPercentSign = scanCode_5;
const int scancode_specialCarrot = scanCode_6;
const int scancode_specialAmpersand = scanCode_7;
const int scancode_specialSplat = scanCode_8;
const int scancode_specialLeftParentheses = scanCode_9;
const int scancode_specialRightParenthese = scanCode_0;
const int scancode_specialUnderline = scanCode_specialMinus;
const int scancode_specialPlusSign = scanCode_specialEqualSign;
const int scancode_specialLeftCurlyBrace = scanCode_specialLeftSquareBrace;
const int scancode_specialRightCurlyBrace = scanCode_specialRightSquareBrace;
const int scancode_specialColon = scanCode_specialSemiColon;
const int scancode_specialDoubleQuotes = scanCode_specialSingleQuotes;
const int scancode_specialPipe = scanCode_specialBackSlash;
const int scancode_specialLessThan = scanCode_specialComma;
const int scancode_specialGreaterThan = scanCode_specialPeriod;
const int scancode_specialQuestionMark = scanCode_specialForwardSlash;
