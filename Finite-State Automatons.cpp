#include <iostream>
#include "Tests.h"
#include "RegExTests.h"
#include "FiniteAutomata.h"
#include "RegExHandler.h"
#include "AutomatonFileHandler.h"
int main()
{
	
	Tests::runAllTests();

	_CrtDumpMemoryLeaks();
	//FiniteAutomata a("(a+b)*");
	//a.minimize();
	//std::cout << a.getRegEx().getString() << std::endl;
	//FiniteAutomata b(a.getRegEx());
	//b.minimize();
	//b.print();

}