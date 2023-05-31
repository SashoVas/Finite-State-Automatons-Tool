#include "Concatenation.h"

ConcatenationRegEx& ConcatenationRegEx::operator=(const ConcatenationRegEx& other) {
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}
MyString ConcatenationRegEx::getString()const {
	return left->getString() + right->getString();
}
RegEx* ConcatenationRegEx::clone()const {
	return new ConcatenationRegEx(left, right);
}

void ConcatenationRegEx::copyFrom(const ConcatenationRegEx& other) {
	left = other.left->clone();
	right = other.right->clone();
}
void ConcatenationRegEx::moveFrom(ConcatenationRegEx&& other) {
	left = other.left;
	other.left = nullptr;
	right = other.right;
	other.right = nullptr;
}
void ConcatenationRegEx::free() {
	delete left;
	delete right;
}
ConcatenationRegEx::ConcatenationRegEx(RegEx* left, RegEx* right) {
	this->left = left;
	this->right = right;
}
ConcatenationRegEx::ConcatenationRegEx(const ConcatenationRegEx& other) {
	copyFrom(other);
}

ConcatenationRegEx::ConcatenationRegEx(ConcatenationRegEx&& other) {
	moveFrom(std::move(other));
}
ConcatenationRegEx& ConcatenationRegEx::operator=(ConcatenationRegEx&& other) {
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}
	return *this;
}

ConcatenationRegEx::~ConcatenationRegEx() {
	free();
}

FiniteAutomata ConcatenationRegEx::getAutomaton()const {
	return left->getAutomaton().ConcatenationWith(right->getAutomaton());
}

