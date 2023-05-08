#pragma once
#include <iostream>
#include "MyString.h"
class RegularExpression {
public:
	enum class Type {
		Concatenation,
		Union,
		KleeneStar,
		Symbol
	};
private:
	Type type;
	RegularExpression* left=nullptr;
	RegularExpression* right=nullptr;
	char value='\0';
	RegularExpression() = default;

	void free();
	void copyFrom(const RegularExpression& other);
	void moveFrom(RegularExpression&& other);

public:


	RegularExpression(const RegularExpression& other);
	RegularExpression(RegularExpression&& other);
	~RegularExpression();
	RegularExpression(const MyString& str);

	RegularExpression& operator=(const RegularExpression& other);
	RegularExpression& operator=(RegularExpression&& other);

	Type getType()const;
	MyString getRegEx()const;
	char getValue()const;

	void printRegEx()const;
	const RegularExpression& getLeft()const;
	const RegularExpression& getRight()const;
	static RegularExpression* getSymbolRegEX(char value);
	static RegularExpression* extend(RegularExpression* result, Type type);
	static RegularExpression* buildRegex(const MyString& str, int& currentPosition);
};

RegularExpression::RegularExpression(RegularExpression&& other) {
	moveFrom(std::move(other));
}

RegularExpression::RegularExpression(const RegularExpression& other) {
	copyFrom(other);
}
RegularExpression::~RegularExpression(){
	free();
}
RegularExpression& RegularExpression::operator=(const RegularExpression& other) {
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}
RegularExpression& RegularExpression::operator=(RegularExpression&& other) {
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}
	return *this;
}
char RegularExpression::getValue()const {
	return value;
}

void RegularExpression::free() {
	delete left;
	left = nullptr;
	delete right;
	right = nullptr;
}
void RegularExpression::copyFrom(const RegularExpression& other){
	value = other.value;
	type = other.type;
	if (other.left != nullptr)
	{
		left = new RegularExpression();
		left->copyFrom(*(other.left));
	}
	if (other.right != nullptr)
	{
		right = new RegularExpression();
		right->copyFrom(*(other.right));
	}
}
void RegularExpression::moveFrom(RegularExpression&& other) {
	left = other.left;
	right = other.right;
	type = other.type;
	value = other.value;
	other.left = nullptr;
	other.right = nullptr;
}

RegularExpression::RegularExpression(const MyString& str) {
	int index=0;
	RegularExpression* regEx = buildRegex(str, index);
	left = regEx->left;
	right = regEx->right;
	type = regEx->type;
	value = regEx->value;
	regEx->left = nullptr;
	regEx->right = nullptr;
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
		if (str[currentPosition + 1] == '*')
		{
			result->type = Type::KleeneStar;
			currentPosition += 2;
			if (currentPosition==str.length())
				return result;
			result = extend(result, Type::Concatenation);
		}
		else {
			result->type = Type::Concatenation;
			currentPosition++;
		}
	}
	else {
		result->left = getSymbolRegEX(str[currentPosition]);;
		result->type = Type::Concatenation;
		currentPosition++;
		if (currentPosition<str.length() && str[currentPosition] == ')')
		{
			RegularExpression* lhs = result->left;
			result->left = nullptr;
			delete result;
			return lhs;
		}
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
			result->left = nullptr;
			delete result;
			return lhs;
		}
		else if (str[currentPosition] == '+') {

			result->type = Type::Union;
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
	result->left = nullptr;
	delete result;
	return lhs;
}