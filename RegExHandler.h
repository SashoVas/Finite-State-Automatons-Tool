#pragma once
#include "RegEx.h"

class RegExHandler{
	RegEx* ptr;
	void copyFrom(const RegExHandler& other);
	void moveFrom(RegExHandler&& other);
	void free();
public:
	RegExHandler(RegEx* ptr);
	RegExHandler(const MyString& str);
	~RegExHandler();

	RegExHandler(const RegExHandler& other);
	RegExHandler(RegExHandler&& other);

	static RegEx* buildRegExFromString(const MyString& str);
	static RegEx* getRegExFromString(const MyString& str, int& currentPosition);
	static RegEx* makeUnion(RegEx* left, RegEx* right);
	static RegEx* makeConcatenation(RegEx* left, RegEx* right);
	static RegEx* makeKleeneStar(RegEx* left);
	static RegEx* makeSymbol(char symbol);

	RegExHandler& operator=(const RegExHandler& other);
	RegExHandler& operator=(RegExHandler&& other);

	MyString getString();
	FiniteAutomata getAutomata();
};
