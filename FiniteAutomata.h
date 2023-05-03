#pragma once
#include <iostream>
#include "CustomCollection.h"
class FiniteAutomata {
	struct Transition {
		int dest=-1;
		char symbol='\0';
		Transition() = default;
		Transition(int dest, char symbol) {
			this->dest = dest;
			this->symbol = symbol;
		}
	};
	int nodes=0;
	int startNode = 0;
	CustomCollection <CustomCollection<Transition>> automata;

public:
	void addState();
	void changeStart(int index);
};

void FiniteAutomata::addState() {
	automata.add(CustomCollection<Transition>());
	nodes++;
}

void FiniteAutomata::changeStart(int index) {
	if (index>=nodes)
	{
		throw std::invalid_argument("invalid index");
	}
	startNode = index;
}