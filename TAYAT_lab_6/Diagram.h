#pragma once

#include "Scaner.h"

class Diagram
{
private:
	Scaner* scaner;
	void Data();							// ������
	void Named_const();						// ����������� ���������
	void Function();						// �������
	void Type();							// ���
	void Assignment();						// ������������
	void Expression();						// ���������
	void CompositeOperator();				// ��������� ��������
	void OperatorsAndDescriptions();		// ��������� � ��������
	void Operator();						// ��������
	void FunctionCall();					// ����� �������
	void Comparison();						// ���������
	void Summand();							// ���������
	void Multiplier();						// ���������
	void UnaryOperation();					// ������� ��������
	void ElementaryExpression();			// ������������ ���������
	int LookForward(int pointer);
	int Scan(type_lex lex);
	void ParameterList();					//������ ����������
	void Switch_operator();					//�������� Switch
	void CaseOperator();					//

public:
	Diagram(Scaner* scaner);
	void Program();							// ���������
};