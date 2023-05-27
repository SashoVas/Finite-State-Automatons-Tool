#include <iostream>
#include "RegularExpression.h"
#include "Tests.h"
#include "FiniteAutomata.h"
int main()
{
	//Tests::runAllTests();
	Tests::runAutomatonComplementTests();
	RegularExpression firstRegEx("(a+b)*(c+d)+ca");
	FiniteAutomata result(firstRegEx);
	result.Complement();
	result.print();
}