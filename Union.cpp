#include "Union.h"

MyString UnionRegEx::getString()const {
	return "(" + left->getString() + "+" + right->getString() + ")";
}

RegEx* UnionRegEx::clone()const {
	return new UnionRegEx(left, right);
}

void UnionRegEx::copyFrom(const UnionRegEx& other) {
	left = other.left->clone();
	right = other.right->clone();
}
void UnionRegEx::moveFrom(UnionRegEx&& other) {
	left = other.left;
	other.left = nullptr;
	right = other.right;
	other.right = nullptr;
}
void UnionRegEx::free() {
	delete left;
	delete right;
}
UnionRegEx::UnionRegEx(RegEx* left, RegEx* right) {
	this->left = left;
	this->right = right;
}

UnionRegEx::UnionRegEx(const UnionRegEx& other) {
	copyFrom(other);
}
UnionRegEx& UnionRegEx::operator=(const UnionRegEx& other) {
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

UnionRegEx::UnionRegEx(UnionRegEx&& other) {
	moveFrom(std::move(other));
}
UnionRegEx& UnionRegEx::operator=(UnionRegEx&& other) {
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}
	return *this;
}

UnionRegEx::~UnionRegEx() {
	free();
}

FiniteAutomata UnionRegEx::getAutomaton()const {
	return left->getAutomaton().UnionWith(right->getAutomaton());
}
