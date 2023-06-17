#include <iostream>
//#include "Tests.h"
//#include "RegExTests.h"
#include "FiniteAutomata.h"
#include "RegExHandler.h"
//#include "AutomatonFileHandler.h"
#include "Engine.h"
int main()
{
	//Engine::run();
	{
		FiniteAutomata a("(a+b)*ab+cd+(h+j)*");
		a.print();
		//a.minimize();
		//std::cout << a.getRegEx().getString() << std::endl;
		RegEx* result = RegExHandler::buildRegExFromAutomatonWithDP(a);
		std::cout << result->getString() << std::endl;
		delete result;
	}

	_CrtDumpMemoryLeaks();
}