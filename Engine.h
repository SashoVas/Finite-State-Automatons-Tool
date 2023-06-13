#pragma once
#include <iostream>
#include "FiniteAutomata.h"
#include "AutomatonFileHandler.h"
class Engine {
	static void printInitialScreen();
	static void printInstructions();
	static void run();
};
void Engine::printInitialScreen() {
	std::cout << "1.Enter RegEx (string regEx)" << std::endl;
	std::cout << "2.Enter file path (string file path)" << std::endl;
}
void Engine::printInstructions() {

}

void Engine::run() {
	int mode = 0;
	char firstInput[1024];

	std::cin >> mode;
	std::cin >> firstInput;
	FiniteAutomata automaton = mode == 1 ? FiniteAutomata(firstInput) : AutomatonFileHandler::readFromFile(firstInput);
	printInstructions();
	while (true)
	{

	}
}
