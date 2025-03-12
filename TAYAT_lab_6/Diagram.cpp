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
		scaner->PrintError("������� ������ � ��������� Program, �������� ����� ���������, ", lex);
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
			scaner->PrintError("������� ������ � ��������� Data, �������� ������������� ����������, ", lex);
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
		scaner->PrintError("������� ������ � ��������� Data, �������� ������ ';', ", lex);
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
		scaner->PrintError("������� ������ � ��������� Named_const, ��������� �������� ����� 'const', ", lex);
	}
	type = Scan(lex);
	Type();

	do {
		Assignment();
		type = Scan(lex);
	} while (type == typeComma);

	if (type != typeSemicolon)
	{
		scaner->PrintError("������� ������ � ��������� Named_const, �������� ������ ';', ", lex);
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
		scaner->PrintError("������� ������ � ���� �������, �������� ��� ������ (void), ", lex);
	}
	type = Scan(lex);
	//

	type = Scan(lex);
	if (type != typeId && type != typeMain)
	{
		scaner->PrintError("������� ������ � ��������� Function, �������� ������������� ������� ��� �������� ����� 'main', ", lex);
	}

	type = Scan(lex);
	if (type != typeLeftBracket)
	{
		scaner->PrintError("������� ������ � ��������� Function, �������� ������ '(', ", lex);
	}

	// ������������ ��������� �������, ���� ��� ����
	type = LookForward(1);
	if (type == typeInt || type == typeShort || type == typeLong || type == typeFloat)
	{
		ParameterList();
	}

	type = Scan(lex);
	if (type != typeRightBracket)
	{
		scaner->PrintError("������� ������ � ��������� Function, �������� ������ ')', ", lex);
	}

	type = Scan(lex);
	if (type != typeLeftBrace)
	{
		scaner->PrintError("������� ������ � ��������� Function, �������� ������ '{', ", lex);
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
		scaner->PrintError("������� ������ � ��������� Function, �������� ������ '}', ", lex);
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
		scaner->PrintError("������� ������ � ��������� Type, �������� ��� ������ (int, short, long), ", lex);
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
		scaner->PrintError("������� ������ � ��������� Assignment, �������� ������������� ����������, ", lex);
	}

	type = Scan(lex);
	if (type != typeEval)
	{
		scaner->PrintError("������� ������ � ��������� Assignment, �������� ������ '=', ", lex);
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
		scaner->PrintError("������� ������ � ��������� CompositeOperator, �������� ������ '{', ", lex);
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
		scaner->PrintError("������� ������ � ��������� CompositeOperator, �������� ������ '}', ", lex);
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
			scaner->PrintError("������� ������ � ��������� Operator, �������� ������ ';' ����� return <���������>, ", lex);
		}
		return;
	}

	if (type == typeSemicolon) // ������ ��������
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
			scaner->PrintError("������� ������ � ��������� Operator, �������� ������ ';', ", lex);
		}
		return;
	}

	if (type == typeId && type2 == typeEval)
	{
		Assignment();
		type = Scan(lex);
		if (type != typeSemicolon)
			scaner->PrintError("������� ������ � ��������� Operator, �������� ������ ';', ", lex);
		return;
	}

	type = Scan(lex);
	scaner->PrintError("������� ������ � ��������� Operator, �������� ��������, ", lex);
}

void Diagram::For_operator()
{
	type_lex lex;
	int type;

	type = Scan(lex);
	if (type != typeFor)
	{
		scaner->PrintError("������� ������ � ��������� For_operator, ��������� �������� ����� 'for', ", lex);
	}

	type = Scan(lex);
	if (type != typeLeftBracket)
	{
		scaner->PrintError("������� ������ � ��������� For_operator, �������� ������ '(', ", lex);
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
			scaner->PrintError("������� ������ � ��������� For_operator, �������� ������ ';', ", lex);
		}
	}
	else
	{
		type = Scan(lex);
		if (type != typeSemicolon)
		{
			scaner->PrintError("������� ������ � ��������� For_operator, �������� ������ ';', ", lex);
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
		scaner->PrintError("������� ������ � ��������� For_operator, �������� ������ ';', ", lex);
	}

	type = LookForward(1);
	if (type != typeRightBracket)
	{
		Assignment();
	}
	type = Scan(lex);
	if (type != typeRightBracket)
	{
		scaner->PrintError("������� ������ � ��������� For_operator, �������� ������ ')', ", lex);
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
		scaner->PrintError("������� ������ � ��������� FunctionCall, �������� ������������� �������, ", lex);
	}

	type = Scan(lex);
	if (type != typeLeftBracket)
	{
		scaner->PrintError("������� ������ � ��������� FunctionCall, �������� ������ '(', ", lex);
	}

	// ������������ ��������� �������, ���� ��� ����
	type = LookForward(1);
	next = -1;
	if (type == typeId || type == typeConstInt) //��� ������ ���� ������������ ���������
	{
		// ������������ ������ ����������
		do {
			// ������������ �������� ��������� (������������� ��� ���������)
			if (type == typeId || type == typeConstInt) //��� ������ ���� ������������ ���������
			{
				type = Scan(lex);
			}
			else
			{
				scaner->PrintError("������� ������ � ��������� FunctionCall, �������� ������������� ��� ���������, ", lex);
			}

			// ���������, ���� �� ��������� ��������
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
		scaner->PrintError("������� ������ � ��������� FunctionCall, �������� ������ ')', ", lex);
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
		scaner->PrintError("������� ������ � ��������� Expression, �������� ���������� ��������, ';', ')' ��� ',', ", lex);
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
			scaner->PrintError("������� ������ � ��������� ElementaryExpression, �������� ������ ')', ", lex);
		}
		return;
	}
	type = Scan(lex);
	scaner->PrintError("������� ������ � ��������� ElementaryExpression, ��������� ���������, ", lex);
}

void Diagram::ParameterList()
{
	type_lex lex;
	int type;

	do {
		// ������������ ��� ���������
		type = LookForward(1);
		if (type != typeInt && type != typeShort && type != typeLong && type != typeFloat)
		{
			scaner->PrintError("������� ������ � ��������� ParameterList, �������� ��� ��������� (int, short, long, float), ", lex);
		}
		type = Scan(lex); // ���������� ���

		// ������������ ������������� ���������
		type = Scan(lex);
		if (type != typeId)
		{
			scaner->PrintError("������� ������ � ��������� ParameterList, �������� ������������� ���������, ", lex);
		}

		// ���������, ���� �� ��������� ��������
		type = LookForward(1);
		if (type == typeComma)
		{
			type = Scan(lex); // ���������� �������
		}
	} while (type == typeComma);
}