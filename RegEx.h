#pragma once
#include "FiniteAutomata.h"

class RegEx {
public:
	virtual bool isEpsilon()const;
	virtual RegEx* clone()const=0;
	virtual MyString getString()const =0;
	virtual ~RegEx() = default;
	virtual FiniteAutomata getAutomaton()const = 0;
};
