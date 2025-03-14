#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define maxText 100000			// Максимальная длина текста
#define maxLex 100				// Максимальная длина лексемы
#define maxKeyword 16			// Максимальное количество ключевых слов
#define maxNumber 10			// Максимальная длина числа
#define maxHexNumber 10			// Максимальная длина 16сс числа
typedef char type_mod[maxText]; // Текст
typedef char type_lex[maxLex];  // Лексема

//Идентификатор
#define TIdent  1

//Константы
#define typeConstInt 11
#define typeConstChar 12
#define typeConstFloat 13

//Ключевые слова
#define typeInt 21
#define typeShort 22
#define typeLong 23
#define typeFloat 24
#define typeVoid 25
#define typeMain 26
#define typeConst 27
#define typeSwitch 28
#define typeCase 29
#define typeDefault 30





/**
* Знаки операций
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
* Специальные знаки
*/
#define typeSemicolon 60		// ;
#define typeComma 61			// ,
#define typeLeftBracket 62		// (
#define typeRightBracket 63		// )
#define typeLeftBrace 64		// {
#define typeRightBrace 65		// }
#define typeColon 66			// :

/**
* Дополнительно
*/
#define typeEnd 100
#define typeError 404