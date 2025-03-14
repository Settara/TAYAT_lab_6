#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define maxText 100000			// ������������ ����� ������
#define maxLex 100				// ������������ ����� �������
#define maxKeyword 16			// ������������ ���������� �������� ����
#define maxNumber 10			// ������������ ����� �����
#define maxHexNumber 10			// ������������ ����� 16�� �����
typedef char type_mod[maxText]; // �����
typedef char type_lex[maxLex];  // �������


/**
* �������� �����
*/
#define typeInt 1
#define typeShort 2
#define typeLong 3
#define typeFloat 4
#define typeVoid 5
#define typeMain 6
#define typeConst 7
#define typeSwitch 8
#define typeCase 9
#define typeDefault 10

/**
* ��� ������
*/
#define typeId 20

/**
* ���������
*/
#define typeConstInt 30
#define typeConstLongInt 31
#define typeConstChar 32
#define typeConstFloat 33

/**
* ����� ��������
*/
#define typePlus 40			    // +
#define typeMinus 41			// -
#define typeMul 42				// *
#define typeDiv 43				// /
#define typeMod 44				// %
#define typeEq 45				// ==
#define typeUnEq 46				// !=
#define typeLess 47				// <
#define typeLessOrEq 48			// <=
#define typeMore 49				// >
#define typeMoreOrEq 50			// >=
#define typeEval 51				// =



/**
* ����������� �����
*/
#define typeSemicolon 60		// ;
#define typeComma 61			// ,
#define typeLeftBracket 62		// (
#define typeRightBracket 63		// )
#define typeLeftBrace 64		// {
#define typeRightBrace 65		// }
#define typeColon 66			// :

/**
* �������������
*/
#define typeEnd 100
#define typeError 404