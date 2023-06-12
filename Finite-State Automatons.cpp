#include <iostream>
#include "Tests.h"
#include "RegExTests.h"
#include "FiniteAutomata.h"
#include "RegEx.h"
#include "AutomatonFileHandler.h"
int main()
{
	
	Tests::runAllTests();

	_CrtDumpMemoryLeaks();
}