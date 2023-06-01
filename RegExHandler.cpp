#include "RegExHandler.h"
#include "KleeneStar.h"
#include "Concatenation.h"
#include "Union.h"
#include "Symbol.h"

void RegExHandler::copyFrom(const RegExHandler& other) {
	ptr = other.ptr->clone();
}
void RegExHandler::moveFrom(RegExHandler&& other) {
	ptr = other.ptr;
	other.ptr = nullptr;
}
void RegExHandler::free() {
	delete ptr;
}

RegExHandler::RegExHandler(RegEx* ptr) {
	this->ptr = ptr;
}
RegExHandler::RegExHandler(const MyString& str) {
	ptr = buildRegExFromString(str);
}
RegExHandler::~RegExHandler() {
	free();
}

RegExHandler::RegExHandler(const RegExHandler& other) {
	copyFrom(other);
}
RegExHandler::RegExHandler(RegExHandler&& other) {
	moveFrom(std::move(other));
}

RegExHandler& RegExHandler::operator=(const RegExHandler& other) {
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}
RegExHandler& RegExHandler::operator=(RegExHandler&& other) {
	if (this != &other)
	{
		free();
		copyFrom(std::move(other));
	}
	return *this;
}


RegEx* RegExHandler::buildRegExFromString(const MyString& str) {
	int a = 0;
	return getRegExFromString(str, a);
}
RegEx* RegExHandler::getRegExFromString(const MyString& str, int& currentPosition) {
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
RegEx* RegExHandler::makeUnion(RegEx* left, RegEx* right) {
	return new UnionRegEx(left, right);
}
RegEx* RegExHandler::makeConcatenation(RegEx* left, RegEx* right) {
	return new ConcatenationRegEx(left, right);
}
RegEx* RegExHandler::makeKleeneStar(RegEx* left) {
	return new KleeneStarRegEx(left);
}
RegEx* RegExHandler::makeSymbol(char symbol) {
	return new Symbol(symbol);
}
MyString RegExHandler::getString() {
	return ptr->getString();
}
FiniteAutomata RegExHandler::getAutomata() {
	return ptr->getAutomaton();
}