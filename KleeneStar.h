#pragma once
#include "RegEx.h"
#include <iostream>
class KleeneStarRegEx:public RegEx {
	RegEx* element=nullptr;
	void copyFrom(const KleeneStarRegEx& other);
	void moveFrom(KleeneStarRegEx&& other);
	void free();
public:
	KleeneStarRegEx(RegEx* element);

	~KleeneStarRegEx();
	KleeneStarRegEx() = default;
	KleeneStarRegEx(const KleeneStarRegEx& other);
	KleeneStarRegEx& operator=(const KleeneStarRegEx& other);

	KleeneStarRegEx(KleeneStarRegEx&& other);
	KleeneStarRegEx& operator=(KleeneStarRegEx&& other);

	virtual RegEx* clone()const override;
	virtual MyString getString()const override;
	virtual FiniteAutomata getAutomaton()const override;

};