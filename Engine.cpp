#include "Engine.h"
#include "AutomatonFileHandler.h"
#include "Tests.h"
#include "RegExHandler.h"
void Engine::printInitialScreen() {
	std::cout << "1.Enter RegEx (string regEx)" << std::endl;
	std::cout << "2.Enter file path (string file path)" << std::endl;
	std::cout << "3.Print tests" << std::endl;
}
void Engine::printInstructions() {
	std::cout << "0.Print" << std::endl;
	std::cout << "1.Determinize" << std::endl;
	std::cout << "2.Minimize" << std::endl;
	std::cout << "3.Totalize" << std::endl;
	std::cout << "4.Run (string word)" << std::endl;
	std::cout << "5.Is language empty" << std::endl;
	std::cout << "6.Union with (string otherAutomatonRegEx)" << std::endl;
	std::cout << "7.Concatenation with (string otherAutomatonRegEx)" << std::endl;
	std::cout << "8.Kleene Star" << std::endl;
	std::cout << "9.Compliment" << std::endl;
	std::cout << "10.Differance with(string otherAutomatonRegEx)" << std::endl;
	std::cout << "11.Intersection with(string otherAutomatonRegEx)" << std::endl;
	std::cout << "12.Get regEx" << std::endl;
	std::cout << "13.Save (string path)" << std::endl;
	std::cout << "14.Close" << std::endl;
}

void Engine::run() {
	int mode = 0;
	char currentInput[1024];
	printInitialScreen();
	std::cin >> mode;
	if (mode == 3)
	{
		bool result = Tests::runAllTests();
		std::cout << "-----------------------------------" << std::endl;
		std::cout << (result ? "Tests run successfully" : "Tests failed") << std::endl;
		std::cout << "-----------------------------------" << std::endl;
		return;
	}
	std::cin >> currentInput;
	try
	{
		FiniteAutomata automaton = mode == 1 ? FiniteAutomata(currentInput) : AutomatonFileHandler::readFromFile(currentInput);
		FiniteAutomata b;
		printInstructions();
		while (true)
		{
			std::cin >> mode;
			switch (mode)
			{
			case 0:
				automaton.print();
				break;
			case 1:
				automaton.makeDeterministic();
				break;
			case 2:
				automaton.minimize();
				break;
			case 3:
				automaton.makeTotal();
				break;
			case 4:
				std::cin >> currentInput;
				std::cout << automaton.accept(currentInput) << std::endl;
				break;
			case 5:
				std::cout << automaton.isEmptyLanguage() << std::endl;
				break;
			case 6:
				std::cin >> currentInput;
				b = FiniteAutomata(currentInput);
				automaton.UnionWith(b);
				break;
			case 7:
				std::cin >> currentInput;
				b = FiniteAutomata(currentInput);
				automaton.ConcatenationWith(b);
				break;
			case 8:
				automaton.KleeneStar();
				break;
			case 9:
				automaton.Complement();
				break;
			case 10:
				std::cin >> currentInput;
				b = FiniteAutomata(currentInput);
				automaton.DifferenceWith(b);
				break;
			case 11:
				std::cin >> currentInput;
				b = FiniteAutomata(currentInput);
				automaton.IntersectWith(b);
				break;
			case 12:
				std::cout << automaton.getRegEx().getString() << std::endl;
				break;
			case 13:
				std::cin >> currentInput;
				AutomatonFileHandler::writeToFile(currentInput, automaton);
				break;
			case 14:
				return;
				break;
			default:
				break;
			}


		}
	}
	catch (const std::exception& e)
	{
		std::cout << e.what();
	}
}
