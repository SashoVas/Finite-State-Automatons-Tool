#include "Symbol.h"
namespace {
	bool isInRange(int l,int r,int val) {
		return val>=l && val<=r;
	}
}
bool Symbol::isEpsilon()const {
	return value=='$';
}
Symbol::Symbol(char val) {
	if (!isInRange('0','9',val) && !isInRange('a', 'z', val) && !isInRange('A', 'Z', val) && val!='$')
	{
		throw std::invalid_argument("Letter not allowed!");
	}
	value = val;
}
RegEx* Symbol::clone() const {
	return new Symbol(value);
}
MyString Symbol::getString()const {
	MyString toReturn(2);
	toReturn[0] = value;
	toReturn[1] = '\0';
	return toReturn;
}
FiniteAutomata Symbol::getAutomaton()const {
	return FiniteAutomata(value);
}
