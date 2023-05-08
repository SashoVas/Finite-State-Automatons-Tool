#include <iostream>
#include "RegularExpression.h"
#include "Tests.h"
#include "FiniteAutomata.h"
int main()
{
	//Tests::runRegularExpressionTests();
	//FiniteAutomata a('a');
	//FiniteAutomata b('b');
	//FiniteAutomata c = Concatenation(a,b);
	FiniteAutomata a('a');
	a.addState();
	a.addTransition(1,FiniteAutomata::Transition(2, 'b'));
	a.makeFinal(2);
	a.print();
}