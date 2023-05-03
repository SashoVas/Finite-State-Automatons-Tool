#pragma once
#include <iostream>
#include "MyString.h"
class RegularExpression {
private:
	enum class Type {
		Concatenation,
		Union,
		KleeneStar,
		Symbol
	};
	Type type;
	RegularExpression* left=nullptr;
	RegularExpression* right=nullptr;
	char value='\0';
	RegularExpression() = default;
public:
	RegularExpression(const MyString& str);
	Type getType()const;
	MyString getRegEx()const;
	void printRegEx()const;
	const RegularExpression& getLeft()const;
	const RegularExpression& getRight()const;
	static RegularExpression* getSymbolRegEX(char value);
	static RegularExpression* extend(RegularExpression* result, Type type);
	static RegularExpression* buildRegex(const MyString& str, int& currentPosition);
};

RegularExpression::RegularExpression(const MyString& str) {
	int index=0;
	RegularExpression* regEx = buildRegex(str, index);
	left = regEx->left;
	right = regEx->right;
	type = regEx->type;
	delete regEx;
}

RegularExpression::Type RegularExpression::getType()const {
	return type;
}
MyString RegularExpression::getRegEx()const {
	if (type == Type::Symbol)
	{
		MyString toReturn(2);
		toReturn[0] = value;
		toReturn[1] = '\0';
		return toReturn;
	}
	else if (type == Type::Concatenation)
		return left->getRegEx() + right->getRegEx();
	else if (type == Type::Union)
		return "(" + left->getRegEx() + "+" + right->getRegEx() + ")";
	else
		return "(" + left->getRegEx() + ")*";
	
}
void RegularExpression::printRegEx()const {

	if (type == Type::Symbol)
		std::cout << value;
	else if (type == Type::Concatenation)
	{
		left->printRegEx();
		if (right != nullptr)
			right->printRegEx();

	}
	else if (type == Type::KleeneStar)
	{
		std::cout << "(";
		left->printRegEx();
		std::cout << ")*";
	}
	else {
		std::cout << "(";
		left->printRegEx();
		std::cout << "+";
		right->printRegEx();
		std::cout << ")";
	}
}
const RegularExpression& RegularExpression::getLeft()const {
	return *left;
}
const RegularExpression& RegularExpression::getRight()const {
	return *right;
}
RegularExpression* RegularExpression::getSymbolRegEX(char value) {
	RegularExpression* val = new RegularExpression();
	val->value = value;
	val->type = Type::Symbol;
	return val;
}
RegularExpression* RegularExpression::extend(RegularExpression* result, Type type) {
	RegularExpression* newResult = new RegularExpression();
	newResult->left = result;
	newResult->type = type;
	return newResult;
}
RegularExpression* RegularExpression::buildRegex(const MyString& str, int& currentPosition) {
	RegularExpression* result = new RegularExpression();
	if (str[currentPosition] == '(')
	{
		currentPosition++;
		result->left = buildRegex(str, currentPosition);
		result->type = Type::KleeneStar;
	}
	else {
		result->left = getSymbolRegEX(str[currentPosition]);;
		result->type = Type::Concatenation;
		currentPosition++;
	}

	for (; currentPosition < str.length(); currentPosition++)
	{
		if (str[currentPosition] == '(')
		{
			currentPosition++;
			RegularExpression* rhs = buildRegex(str, currentPosition);
			if (str[currentPosition + 1] == '*')
			{
				currentPosition++;
				rhs = extend(rhs, Type::KleeneStar);
			}
			result->right = rhs;
			result = extend(result, Type::Concatenation);
		}
		else if (str[currentPosition] == ')')
		{
			RegularExpression* lhs = result->left;
			delete result;
			return lhs;
		}
		else if (str[currentPosition] == '+') {
			result->type = Type::Union;
			currentPosition++;
			if (str[currentPosition] == '(')
				currentPosition++;
			result->right = buildRegex(str, currentPosition);
			if (str[currentPosition] == ')')
				return result;
			result = extend(result, Type::Concatenation);
		}
		else {
			result->right = getSymbolRegEX(str[currentPosition]);
			result = extend(result, Type::Concatenation);
		}
	}
	RegularExpression* lhs = result->left;
	delete result;
	return lhs;
	return result;
}