#pragma once
#include <iostream>
#include "CustomCollection.h"
class FiniteAutomata {
public:
	struct Transition {
		int dest = -1;
		char symbol = '\0';
		Transition() = default;
		Transition(int dest, char symbol) {
			this->dest = dest;
			this->symbol = symbol;
		}
	};
private:
	int nodes=0;
	int startNode = 0;

	CustomCollection <CustomCollection<Transition>> automata;
	CustomCollection<int> finalStates;
	CustomCollection<char> alphabet;

	void combine(const FiniteAutomata& other);
	void addToAlphabet(char symbol);
public:

	FiniteAutomata(int size);
	FiniteAutomata(char symbol);
	FiniteAutomata(const RegularExpression& regEx);

	void addState();
	void changeStart(int index);
	void addTransition(int index, const Transition& transition);
	void makeFinal(int index);

	void makeDeterministic();

	FiniteAutomata& UnionWith(const const FiniteAutomata& rhs);
	FiniteAutomata& ConcatenationWith(const const FiniteAutomata& rhs);
	FiniteAutomata& KleeneStar();

	friend FiniteAutomata Union(const FiniteAutomata& lhs,const FiniteAutomata& rhs);
	friend FiniteAutomata Concatenation(const FiniteAutomata& lhs,const FiniteAutomata& rhs);
	friend FiniteAutomata KleeneStar(const FiniteAutomata& lhs);

	void print()const;

	static FiniteAutomata buildFromRegex(const RegularExpression& regEx);
};

FiniteAutomata::FiniteAutomata(int size) {
	startNode = 0;
	for (int i = 0; i < size; i++)
	{
		automata.add(CustomCollection<Transition>());
	}
}
FiniteAutomata::FiniteAutomata(char symbol) {
	startNode = 0;
	CustomCollection<Transition>t;
	t.add(Transition(1,symbol));
	automata.add(t);
	automata.add(CustomCollection<Transition>());
	nodes = 2;
	finalStates.add(1);
	alphabet.add(symbol);
}
FiniteAutomata::FiniteAutomata(const RegularExpression& regEx) {
	FiniteAutomata toReplace = buildFromRegex(regEx);
	automata = std::move(toReplace.automata);
	finalStates = std::move(toReplace.finalStates);
	alphabet = std::move(toReplace.alphabet);
	nodes = toReplace.nodes;
	startNode = toReplace.startNode;

}
void FiniteAutomata::addToAlphabet(char symbol) {
	if (alphabet.find(symbol) != -1)
		return;
	alphabet.add(symbol);
}

void FiniteAutomata::addTransition(int index, const Transition& transition) {
	if (index>=nodes)
		throw std::invalid_argument("Invalid argument");
	automata[index].add(transition);
	addToAlphabet(transition.symbol);
}
void FiniteAutomata::makeFinal(int index) {
	if (index >= nodes)
		throw std::invalid_argument("Invalid argument");
	finalStates.add(index);
}

void FiniteAutomata::print()const {
	std::cout << "Start node:" << startNode<<std::endl;
	std::cout << "Nodes:" << nodes<<std::endl;
	std::cout << "Alphabet:";
	for (int i = 0; i < alphabet.getSize(); i++)
	{
		std::cout << alphabet[i] << "," ;
	}
	std::cout << std::endl;
	std::cout << "Transitions:" <<std::endl;
	for (int i = 0; i < nodes; i++)
	{
		std::cout << i << "->";
		for (int j = 0; j < automata[i].getSize(); j++)
		{
			std::cout <<"("<< automata[i][j].dest<<","<< automata[i][j].symbol <<")" << ",";
		}
		std::cout << std::endl;
	}
	std::cout << "Final states:";
	for (int i = 0; i < finalStates.getSize(); i++)
	{
		std::cout << finalStates[i] << ",";
	}
	std::cout<<std::endl;
}

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

void FiniteAutomata::combine(const FiniteAutomata& other) {
	int initialNodes = nodes;
	for (int i = 0; i < other.automata.getSize(); i++)
	{
		addState();
		for (int j = 0; j < other.automata[i].getSize(); j++)
		{
			addToAlphabet(other.automata[i][j].symbol);
			automata[initialNodes + i].add(FiniteAutomata::Transition(other.automata[i][j].dest + initialNodes, other.automata[i][j].symbol));
		}
	}
}
FiniteAutomata Union(const FiniteAutomata& lhs, const FiniteAutomata& rhs) {
	FiniteAutomata result(lhs);
	result.UnionWith(rhs);
	return result;
}

FiniteAutomata Concatenation(const FiniteAutomata& lhs, const FiniteAutomata& rhs) {
	FiniteAutomata result(lhs);
	result.ConcatenationWith(rhs);
	return result;
}

FiniteAutomata KleeneStar(const FiniteAutomata& lhs) {
	FiniteAutomata result(lhs);
	result.KleeneStar();
	return result;
}

FiniteAutomata& FiniteAutomata::KleeneStar() {
	for (int i = 0; i < finalStates.getSize(); i++)
	{
		for (int j = 0; j < automata[startNode].getSize(); j++)
		{
			if (finalStates[i] == startNode)
				continue;
			automata[finalStates[i]].add(
				FiniteAutomata::Transition(automata[startNode][j].dest
					, automata[startNode][j].symbol));
		}
	}

	if (finalStates.find(startNode) == -1)
		finalStates.add(startNode);

	return *this;
}

FiniteAutomata& FiniteAutomata::UnionWith(const const FiniteAutomata& rhs) {
	int intitialNodes = nodes;
	combine(rhs);

	for (int i = 0; i < rhs.finalStates.getSize(); i++)
		finalStates.add(rhs.finalStates[i] + intitialNodes);

	addState();
	for (int i = 0; i < automata[startNode].getSize(); i++)
		automata[nodes - 1].add(FiniteAutomata::Transition(automata[startNode][i].dest,automata[startNode][i].symbol));
	for (int i = 0; i < rhs.automata[rhs.startNode].getSize(); i++)
		automata[nodes - 1].add(FiniteAutomata::Transition(rhs.automata[rhs.startNode][i].dest + intitialNodes, rhs.automata[rhs.startNode][i].symbol));
	
	if (finalStates.find(startNode) != -1 || rhs.finalStates.find(rhs.startNode) != -1)
		finalStates.add(startNode);

	startNode = nodes - 1;

	return *this;
}

FiniteAutomata& FiniteAutomata::ConcatenationWith(const const FiniteAutomata& rhs) {
	int initialNodes = nodes;
	combine(rhs);

	for (int i = 0; i < finalStates.getSize(); i++)
	{
		for (int j = 0; j < rhs.automata[rhs.startNode].getSize(); j++)
		{
			automata[finalStates[i]].add(
				FiniteAutomata::Transition(
					rhs.automata[rhs.startNode][j].dest + initialNodes
					, rhs.automata[rhs.startNode][j].symbol)
			);
		}

	}

	if (rhs.finalStates.find(rhs.startNode) == -1)
		finalStates.empty();

	for (int i = 0; i < rhs.finalStates.getSize(); i++)
		finalStates.add(rhs.finalStates[i] + initialNodes);

	return *this;
}

FiniteAutomata FiniteAutomata::buildFromRegex(const RegularExpression& regEx) {
	if (regEx.getType()==RegularExpression::Type::Symbol)
	{
		return FiniteAutomata(regEx.getValue());
	}
	else if (regEx.getType()==RegularExpression::Type::Union)
	{
		FiniteAutomata lhs = buildFromRegex(regEx.getLeft());
		FiniteAutomata rhs = buildFromRegex(regEx.getRight());
		lhs.UnionWith(rhs);
		return lhs;
	}
	else if (regEx.getType()==RegularExpression::Type::Concatenation)
	{
		FiniteAutomata lhs = buildFromRegex(regEx.getLeft());
		FiniteAutomata rhs = buildFromRegex(regEx.getRight());
		lhs.ConcatenationWith(rhs);
		return lhs;
	}
	else
	{
		FiniteAutomata lhs = buildFromRegex(regEx.getLeft());
		return lhs.KleeneStar();
	}
}