#pragma once
#include "Concatenation.h"
#include "Union.h"
#include "KleeneStar.h"
#include "Symbol.h"
#include "MyString.h"
#include "SharedPointer.h"
class RegExParser {
public:
	static SharedPointer<RegEx> buildRegExFromString(const MyString& str);
	static RegEx* getRegExFromString(const MyString& str, int& currentPosition);
};