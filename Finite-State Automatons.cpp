#include <iostream>
#include "RegularExpression.h"
#include "Tests.h"
#include "FiniteAutomata.h"
int main()
{
	//Tests::runRegularExpressionTests();
	FiniteAutomata a('a');
	FiniteAutomata b('b');
	FiniteAutomata c = Concatenation(a,b);
	c.print();
}