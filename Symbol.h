#pragma once
#include "RegEx.h"
class Symbol:public RegEx {
	char value = '\0';

public:
	RegEx* clone() const override;
	virtual MyString getString()const override;
	Symbol(char val);
	virtual FiniteAutomata getAutomaton()const override;
	virtual bool isEpsilon()const override;
};