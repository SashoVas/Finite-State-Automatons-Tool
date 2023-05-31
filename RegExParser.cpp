#include "RegExParser.h"

SharedPointer<RegEx> RegExParser::buildRegExFromString(const MyString& str) {
	int a = 0;
	return getRegExFromString(str, a);
}
RegEx* RegExParser::getRegExFromString(const MyString& str, int& currentPosition) {
	RegEx* result = nullptr;
	if (str[currentPosition] == '(')
	{
		currentPosition++;
		result = getRegExFromString(str, currentPosition);
		if (str[currentPosition + 1] == '*')
		{
			currentPosition += 2;
			result = new KleeneStarRegEx(result);
			if (currentPosition == str.length())
				return result;
		}
		else {
			currentPosition++;
		}
	}
	else {
		result = new Symbol(str[currentPosition]);
		currentPosition++;
		if (currentPosition < str.length() && str[currentPosition] == ')')
		{
			return result;
		}
	}

	for (; currentPosition < str.length(); currentPosition++)
	{
		if (str[currentPosition] == '(')
		{
			currentPosition++;
			RegEx* rhs = getRegExFromString(str, currentPosition);
			if (str[currentPosition + 1] == '*')
			{
				currentPosition++;
				rhs = new KleeneStarRegEx(rhs);
			}
			result = new ConcatenationRegEx(result, rhs);
		}
		else if (str[currentPosition] == ')')
		{
			return result;
		}
		else if (str[currentPosition] == '+') {
			currentPosition++;
			RegEx* right = getRegExFromString(str, currentPosition);
			result = new UnionRegEx(result, right);
			if (str[currentPosition] == ')')
				return result;
		}
		else {
			RegEx* symbol = new Symbol(str[currentPosition]);
			result = new ConcatenationRegEx(result, symbol);
		}
	}
	return result;
}