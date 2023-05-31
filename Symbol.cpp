#include "Symbol.h"

bool Symbol::isEpsilon()const {
	return value=='$';
}
Symbol::Symbol(char val) {
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
