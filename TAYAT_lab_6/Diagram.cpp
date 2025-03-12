#include "Diagram.h"

Diagram::Diagram(Scaner* scaner)
{
	this->scaner = scaner;
}

int Diagram::LookForward(int pos)
{
	type_lex lex;
	int saved_pointer = scaner->GetUK();
	int next_type;
	for (int i = 0; i < pos; i++)
		next_type = scaner->UseScaner(lex);
	scaner->PutUK(saved_pointer);
	return next_type;
}

int Diagram::Scan(type_lex lex)
{
	return scaner->UseScaner(lex);
}

void Diagram::Program()
{
	type_lex lex;
	int type;
	int simbol;
	int simbol2;

	type = LookForward(1);

	while (type == typeInt || type == typeShort || type == typeLong || type == typeFloat || type == typeConst || type == typeVoid)
	{
		type = LookForward(1);
		simbol = LookForward(3);
		simbol2 = LookForward(4);
		if (type == typeConst)
		{
			Named_const();
		}
		if ((type == typeInt || type == typeShort || type == typeLong || type == typeFloat || type == typeConst) && simbol != typeLeftBracket && simbol2 != typeLeftBracket)
		{
			Data();
		}
		if ((type == typeInt || type == typeShort || type == typeLong || type == typeFloat || type == typeConst || type == typeVoid) && (simbol == typeLeftBracket || simbol2 == typeLeftBracket))
		{
			Function();
		}
		type = LookForward(1);
	}

	if (type != typeEnd)
	{
		type = Scan(lex);
		scaner->PrintError("найдена ошибка в структуре Program, ожидался конец программы, ", lex);
	}
}

void Diagram::Data()
{
	type_lex lex;
	int type;
	int type2;
	Type();

	do {
		type = LookForward(1);

		if (type != typeId)
		{
			type = Scan(lex);
			scaner->PrintError("найдена ошибка в структуре Data, ожидался идентификатор переменной, ", lex);
		}

		type2 = LookForward(2);
		if (type2 == typeEval)
		{
			Assignment();
			type = Scan(lex);
		}
		else
		{
			type = Scan(lex);
			type = Scan(lex);
		}
	} while (type == typeComma);

	if (type != typeSemicolon)
	{
		scaner->PrintError("найдена ошибка в структуре Data, ожидался символ ';', ", lex);
	}
}

void Diagram::Named_const()
{
	type_lex lex;
	int type;

	type = LookForward(1);
	if (type != typeConst)
	{
		type = Scan(lex);
		scaner->PrintError("найдена ошибка в структуре Named_const, ожидалось ключевое слово 'const', ", lex);
	}
	type = Scan(lex);
	Type();

	do {
		Assignment();
		type = Scan(lex);
	} while (type == typeComma);

	if (type != typeSemicolon)
	{
		scaner->PrintError("найдена ошибка в структуре Named_const, ожидался символ ';', ", lex);
	}
}

void Diagram::Function()
{
	type_lex lex;
	int type;

	//Type();
	//
	type = LookForward(1);
	if (type != typeVoid)
	{
		type = Scan(lex);
		scaner->PrintError("найдена ошибка в типе функции, ожидался тип данных (void), ", lex);
	}
	type = Scan(lex);
	//

	type = Scan(lex);
	if (type != typeId && type != typeMain)
	{
		scaner->PrintError("найдена ошибка в структуре Function, ожидался идентификатор функции или ключевое слово 'main', ", lex);
	}

	type = Scan(lex);
	if (type != typeLeftBracket)
	{
		scaner->PrintError("найдена ошибка в структуре Function, ожидался символ '(', ", lex);
	}

	// Обрабатываем параметры функции, если они есть
	type = LookForward(1);
	if (type == typeInt || type == typeShort || type == typeLong || type == typeFloat)
	{
		ParameterList();
	}

	type = Scan(lex);
	if (type != typeRightBracket)
	{
		scaner->PrintError("найдена ошибка в структуре Function, ожидался символ ')', ", lex);
	}

	type = Scan(lex);
	if (type != typeLeftBrace)
	{
		scaner->PrintError("найдена ошибка в структуре Function, ожидался символ '{', ", lex);
	}

	type = LookForward(1);

	while (type != typeRightBrace)
	{
		OperatorsAndDescriptions();
		type = LookForward(1);
	}

	type = Scan(lex);
	if (type != typeRightBrace)
	{
		scaner->PrintError("найдена ошибка в структуре Function, ожидался символ '}', ", lex);
	}
}


void Diagram::OperatorsAndDescriptions()
{
	int type = LookForward(1);

	if (type == typeInt || type == typeShort || type == typeLong || type == typeFloat)
	{
		Data();
	}
	else Operator();
}

void Diagram::Type()
{
	type_lex lex;
	int type;
	type = LookForward(1);
	if (type != typeInt && type != typeShort && type != typeLong && type != typeFloat)
	{
		type = Scan(lex);
		scaner->PrintError("найдена ошибка в структуре Type, ожидался тип данных (int, short, long), ", lex);
	}
	type = Scan(lex);
}

void Diagram::Assignment()
{
	type_lex lex;
	int type;

	type = Scan(lex);
	if (type != typeId)
	{
		scaner->PrintError("найдена ошибка в структуре Assignment, ожидался идентификатор переменной, ", lex);
	}

	type = Scan(lex);
	if (type != typeEval)
	{
		scaner->PrintError("найдена ошибка в структуре Assignment, ожидался символ '=', ", lex);
	}

	Expression();
}

void Diagram::CompositeOperator()
{
	type_lex lex;
	int type;

	type = Scan(lex);
	if (type != typeLeftBrace)
	{
		scaner->PrintError("найдена ошибка в структуре CompositeOperator, ожидался символ '{', ", lex);
	}

	type = LookForward(1);

	while (type != typeRightBrace)
	{
		OperatorsAndDescriptions();
		type = LookForward(1);
	}

	type = Scan(lex);
	if (type != typeRightBrace)
	{
		scaner->PrintError("найдена ошибка в структуре CompositeOperator, ожидался символ '}', ", lex);
	}
}

void Diagram::Operator()
{
	type_lex lex;
	int type = LookForward(1);

	if (type == typeReturn)
	{
		type = Scan(lex);

		Expression();

		type = Scan(lex);
		if (type != typeSemicolon)
		{
			scaner->PrintError("найдена ошибка в структуре Operator, ожидался символ ';' после return <выражение>, ", lex);
		}
		return;
	}

	if (type == typeSemicolon) // пустой оператор
	{
		type = Scan(lex);
		return;
	}

	if (type == typeLeftBrace)
	{
		CompositeOperator();
		return;
	}

	if (type == typeFor)
	{
		For_operator();
		return;
	}

	int type2 = LookForward(2);
	if (type == typeId && type2 == typeLeftBracket)
	{
		FunctionCall();
		type = Scan(lex);
		if (type != typeSemicolon)
		{
			scaner->PrintError("найдена ошибка в структуре Operator, ожидался символ ';', ", lex);
		}
		return;
	}

	if (type == typeId && type2 == typeEval)
	{
		Assignment();
		type = Scan(lex);
		if (type != typeSemicolon)
			scaner->PrintError("найдена ошибка в структуре Operator, ожидался символ ';', ", lex);
		return;
	}

	type = Scan(lex);
	scaner->PrintError("найдена ошибка в структуре Operator, ожидался оператор, ", lex);
}

void Diagram::For_operator()
{
	type_lex lex;
	int type;

	type = Scan(lex);
	if (type != typeFor)
	{
		scaner->PrintError("найдена ошибка в структуре For_operator, ожидалось ключевое слово 'for', ", lex);
	}

	type = Scan(lex);
	if (type != typeLeftBracket)
	{
		scaner->PrintError("найдена ошибка в структуре For_operator, ожидался символ '(', ", lex);
	}

	type = LookForward(1);

	if (type == typeInt || type == typeShort || type == typeLong || type == typeConst)
	{
		Data();
	}
	else if (type != typeSemicolon)
	{
		Assignment();
		type = Scan(lex);
		if (type != typeSemicolon)
		{
			scaner->PrintError("найдена ошибка в структуре For_operator, ожидался символ ';', ", lex);
		}
	}
	else
	{
		type = Scan(lex);
		if (type != typeSemicolon)
		{
			scaner->PrintError("найдена ошибка в структуре For_operator, ожидался символ ';', ", lex);
		}
	}

	type = LookForward(1);
	if (type != typeSemicolon)
	{
		Expression();
	}
	type = Scan(lex);
	if (type != typeSemicolon)
	{
		scaner->PrintError("найдена ошибка в структуре For_operator, ожидался символ ';', ", lex);
	}

	type = LookForward(1);
	if (type != typeRightBracket)
	{
		Assignment();
	}
	type = Scan(lex);
	if (type != typeRightBracket)
	{
		scaner->PrintError("найдена ошибка в структуре For_operator, ожидался символ ')', ", lex);
	}

	OperatorsAndDescriptions();
}

void Diagram::FunctionCall()
{
	type_lex lex;
	int type, next;

	type = Scan(lex);
	if (type != typeId)
	{
		scaner->PrintError("найдена ошибка в структуре FunctionCall, ожидался идентификатор функции, ", lex);
	}

	type = Scan(lex);
	if (type != typeLeftBracket)
	{
		scaner->PrintError("найдена ошибка в структуре FunctionCall, ожидался символ '(', ", lex);
	}

	// Обрабатываем параметры функции, если они есть
	type = LookForward(1);
	next = -1;
	if (type == typeId || type == typeConstInt) //Тут должна быть вещественная константа
	{
		// Обрабатываем список параметров
		do {
			// Обрабатываем значение параметра (идентификатор или константа)
			if (type == typeId || type == typeConstInt) //Тут должна быть вещественная константа
			{
				type = Scan(lex);
			}
			else
			{
				scaner->PrintError("найдена ошибка в структуре FunctionCall, ожидался идентификатор или константа, ", lex);
			}

			// Проверяем, есть ли следующий параметр
			type = LookForward(1);
			if (type == typeComma)
			{
				next = Scan(lex);
				type = LookForward(1);
			}
			if (type == typeRightBracket)
			{
				next = -1;
			}
		} while (next == typeComma);
	}


	type = Scan(lex);
	if (type != typeRightBracket)
	{
		scaner->PrintError("найдена ошибка в структуре FunctionCall, ожидался символ ')', ", lex);
	}
}

void Diagram::Expression()
{
	type_lex lex;
	int type;

	Comparison();
	type = LookForward(1);
	while (type == typeEq || type == typeUnEq)
	{
		type = Scan(lex);
		Comparison();
		type = LookForward(1);
	}

	if (type != typeSemicolon && type != typeRightBracket && type != typeComma)
	{
		type = Scan(lex);
		scaner->PrintError("найдена ошибка в структуре Expression, ожидался логический оператор, ';', ')' или ',', ", lex);
	}
}

void Diagram::Comparison()
{
	type_lex lex;
	Summand();
	int type = LookForward(1);
	while (type == typeLess || type == typeLessOrEq || type == typeMore || type == typeMoreOrEq)
	{
		type = Scan(lex);
		Summand();
		type = LookForward(1);
	}
}

void Diagram::Summand()
{
	type_lex lex;
	int type;
	Multiplier();
	type = LookForward(1);
	while (type == typePlus || type == typeMinus)
	{
		type = Scan(lex);
		Multiplier();
		type = LookForward(1);
	}
}

void Diagram::Multiplier()
{
	type_lex lex;
	int type;
	UnaryOperation();
	type = LookForward(1);
	while (type == typeMul || type == typeDiv || type == typeMod)
	{
		type = Scan(lex);
		UnaryOperation();
		type = LookForward(1);
	}
}

void Diagram::UnaryOperation()
{
	type_lex lex;
	int type = LookForward(1);

	if (type == typePlus || type == typeMinus)
	{
		type = Scan(lex);
	}
	ElementaryExpression();
}

void Diagram::ElementaryExpression()
{
	type_lex lex;
	int type = LookForward(1);
	if (type == typeId)
	{
		type = LookForward(2);
		if (type == typeLeftBracket)
		{
			FunctionCall();
		}
		else
		{
			type = Scan(lex);
		}
		return;
	}
	if (type == typeConstInt || type == typeConstLongInt || type == typeConstHex || type == typeConstLongHex)
	{
		type = Scan(lex);
		return;
	}
	if (type == typeLeftBracket)
	{
		type = Scan(lex);
		Expression();
		type = Scan(lex);
		if (type != typeRightBracket)
		{
			scaner->PrintError("найдена ошибка в структуре ElementaryExpression, ожидался символ ')', ", lex);
		}
		return;
	}
	type = Scan(lex);
	scaner->PrintError("найдена ошибка в структуре ElementaryExpression, ожидалось выражение, ", lex);
}

void Diagram::ParameterList()
{
	type_lex lex;
	int type;

	do {
		// Обрабатываем тип параметра
		type = LookForward(1);
		if (type != typeInt && type != typeShort && type != typeLong && type != typeFloat)
		{
			scaner->PrintError("найдена ошибка в структуре ParameterList, ожидался тип параметра (int, short, long, float), ", lex);
		}
		type = Scan(lex); // Пропускаем тип

		// Обрабатываем идентификатор параметра
		type = Scan(lex);
		if (type != typeId)
		{
			scaner->PrintError("найдена ошибка в структуре ParameterList, ожидался идентификатор параметра, ", lex);
		}

		// Проверяем, есть ли следующий параметр
		type = LookForward(1);
		if (type == typeComma)
		{
			type = Scan(lex); // Пропускаем запятую
		}
	} while (type == typeComma);
}