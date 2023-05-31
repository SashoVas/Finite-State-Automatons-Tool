#pragma once
#include <iostream>
#include "RegEx.h"
class UnionRegEx :public RegEx {
	RegEx*left = nullptr;
	RegEx* right = nullptr;
	void copyFrom(const UnionRegEx& other);
	void moveFrom(UnionRegEx&& other);
	void free();
public:
	UnionRegEx(RegEx* left, RegEx* right);
	~UnionRegEx();
	UnionRegEx() = default;
	UnionRegEx(const UnionRegEx& other);
	UnionRegEx& operator=(const UnionRegEx& other);

	UnionRegEx(UnionRegEx&& other);
	UnionRegEx& operator=(UnionRegEx&& other);

	virtual RegEx* clone()const override;
	virtual MyString getString()const override;
	virtual FiniteAutomata getAutomaton()const override;
};