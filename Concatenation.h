#pragma once
#include "RegEx.h"
class ConcatenationRegEx :public RegEx {
	RegEx* left = nullptr;
	RegEx* right = nullptr;
	void copyFrom(const ConcatenationRegEx& other);
	void moveFrom(ConcatenationRegEx&& other);
	void free();
public:
	ConcatenationRegEx(RegEx* left, RegEx* right);

	~ConcatenationRegEx();
	ConcatenationRegEx() = default;
	ConcatenationRegEx(const ConcatenationRegEx& other);
	ConcatenationRegEx& operator=(const ConcatenationRegEx& other);
	ConcatenationRegEx(ConcatenationRegEx&& other);
	ConcatenationRegEx& operator=(ConcatenationRegEx&& other);

	virtual RegEx* clone()const override;
	virtual MyString getString()const override;
	virtual FiniteAutomata getAutomaton()const override;

};