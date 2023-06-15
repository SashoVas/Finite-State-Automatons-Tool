#include "KleeneStar.h"
#include "Symbol.h"
#include "FiniteAutomata.h"

MyString KleeneStarRegEx::getString()const {
	return "(" + element->getString() + ")*";
}

RegEx* KleeneStarRegEx::clone()const {
	return new KleeneStarRegEx(element);
}

void KleeneStarRegEx::copyFrom(const KleeneStarRegEx& other) {
	element = other.clone();
}
void KleeneStarRegEx::moveFrom(KleeneStarRegEx&& other) {
	element = other.element;
	other.element = nullptr;
}
void KleeneStarRegEx::free() {
	delete element;
}
KleeneStarRegEx::KleeneStarRegEx(RegEx* element) {
	if (element==nullptr)
	{
		this->element = new Symbol('$');
	}
	else
	{
		this->element = element;
	}

}
KleeneStarRegEx::KleeneStarRegEx(const KleeneStarRegEx& other) :RegEx(other) {
	copyFrom(other);
}

KleeneStarRegEx& KleeneStarRegEx::operator=(const KleeneStarRegEx& other) {
	if (this != &other)
	{
		RegEx::operator=(other);
		free();
		copyFrom(other);
	}
	return *this;
}

KleeneStarRegEx::KleeneStarRegEx(KleeneStarRegEx&& other) :RegEx(std::move(other)) {
	moveFrom(std::move(other));
}
KleeneStarRegEx& KleeneStarRegEx::operator=(KleeneStarRegEx&& other) {
	if (this != &other)
	{
		RegEx::operator=(std::move(other));
		free();
		moveFrom(std::move(other));
	}
	return *this;
}

KleeneStarRegEx::~KleeneStarRegEx() {
	free();
}

FiniteAutomata KleeneStarRegEx::getAutomaton()const {
	return element->getAutomaton().KleeneStar();
}
