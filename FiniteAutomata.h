#pragma once
#include <iostream>
#include "CustomCollection.hpp"
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
	int nodes = 0;
	int startNode = 0;

	CustomCollection <CustomCollection<Transition>> automata;
	CustomCollection<int> finalStates;
	CustomCollection<int> startStates;
	bool multiplStarts = false;
	CustomCollection<char> alphabet;

	void combine(const FiniteAutomata& other);
	void addToAlphabet(char symbol);
	//
	bool haveTransitionWihtSymbol(int node, char symbol, int to = -1)const;
	void addErrorState();
	CustomCollection<int> getNodeStates(const CustomCollection<int>& nodes, char symbol)const;
	RegularExpression generateRegEx(int i, int j, int k, bool epsilon)const;
	bool haveFinal(const CustomCollection<int>& nodes)const;
	//
public:

	FiniteAutomata(int size);
	FiniteAutomata() = default;
	FiniteAutomata(char symbol);
	FiniteAutomata(const RegularExpression& regEx);
	FiniteAutomata(const char* regEx);

	void addState();
	void changeStart(int index);
	void addTransition(int index, const Transition& transition);
	void makeFinal(int index);

	RegularExpression getRegEx()const;

	void makeDeterministic();
	void makeTotal();
	void minimize();
	void reverse();

	FiniteAutomata& UnionWith(const const FiniteAutomata& rhs);
	FiniteAutomata& ConcatenationWith(const const FiniteAutomata& rhs);
	FiniteAutomata& KleeneStar();
	FiniteAutomata& Complement();

	FiniteAutomata getReverse();

	void print()const;
	bool accept(const MyString& word, int currentLetter = 0, int node = -1)const;

	static FiniteAutomata buildFromRegex(const RegularExpression& regEx);
};

FiniteAutomata Union(const FiniteAutomata& lhs, const FiniteAutomata& rhs);
FiniteAutomata Concatenation(const FiniteAutomata& lhs, const FiniteAutomata& rhs);
FiniteAutomata KleeneStar(const FiniteAutomata& lhs);
FiniteAutomata Complement(const FiniteAutomata& lhs);

FiniteAutomata::FiniteAutomata(int size) {
	startNode = 0;
	nodes = size;
	for (int i = 0; i < size; i++)
	{
		automata.add(CustomCollection<Transition>());
	}
}
FiniteAutomata::FiniteAutomata(char symbol) {
	startNode = 0;
	CustomCollection<Transition>t;
	t.add(Transition(1, symbol));
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
FiniteAutomata::FiniteAutomata(const char* regEx):FiniteAutomata(RegularExpression(regEx)) {
}

void FiniteAutomata::addToAlphabet(char symbol) {
	if (alphabet.find(symbol) != -1)
		return;
	alphabet.add(symbol);
}

void FiniteAutomata::addTransition(int index, const Transition& transition) {
	if (index >= nodes)
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
	std::cout << "Start node:" << startNode << std::endl;
	std::cout << "Nodes:" << nodes << std::endl;
	std::cout << "Alphabet:";
	for (int i = 0; i < alphabet.getSize(); i++)
	{
		std::cout << alphabet[i] << ",";
	}
	std::cout << std::endl;
	std::cout << "Transitions:" << std::endl;
	for (int i = 0; i < nodes; i++)
	{
		std::cout << i << "->";
		for (int j = 0; j < automata[i].getSize(); j++)
		{
			std::cout << "(" << automata[i][j].dest << "," << automata[i][j].symbol << ")" << ",";
		}
		std::cout << std::endl;
	}
	std::cout << "Final states:";
	for (int i = 0; i < finalStates.getSize(); i++)
	{
		std::cout << finalStates[i] << ",";
	}
	std::cout << std::endl;
}

void FiniteAutomata::addState() {
	automata.add(CustomCollection<Transition>());
	nodes++;
}

void FiniteAutomata::changeStart(int index) {
	if (index >= nodes)
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
FiniteAutomata Complement(const FiniteAutomata& lhs) {
	FiniteAutomata result(lhs);
	result.Complement();
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
	multiplStarts = false;
	return *this;
}

FiniteAutomata& FiniteAutomata::UnionWith(const const FiniteAutomata& rhs) {
	int intitialNodes = nodes;
	combine(rhs);

	for (int i = 0; i < rhs.finalStates.getSize(); i++)
		finalStates.add(rhs.finalStates[i] + intitialNodes);

	addState();
	for (int i = 0; i < automata[startNode].getSize(); i++)
		automata[nodes - 1].add(FiniteAutomata::Transition(automata[startNode][i].dest, automata[startNode][i].symbol));
	for (int i = 0; i < rhs.automata[rhs.startNode].getSize(); i++)
		automata[nodes - 1].add(FiniteAutomata::Transition(rhs.automata[rhs.startNode][i].dest + intitialNodes, rhs.automata[rhs.startNode][i].symbol));

	if (finalStates.find(startNode) != -1 || rhs.finalStates.find(rhs.startNode) != -1)
		finalStates.add(nodes-1);

	startNode = nodes - 1;
	multiplStarts = false;

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
	multiplStarts = false;

	return *this;
}
FiniteAutomata& FiniteAutomata::Complement() {
	makeDeterministic();
	//makeTotal();
	CustomCollection<int>newFinals;
	for (int i = 0; i < nodes; i++)
	{
		if (finalStates.find(i)==-1)
		{
			newFinals.add(i);
		}
	}
	finalStates = std::move(newFinals);
	return *this;
}

FiniteAutomata FiniteAutomata::buildFromRegex(const RegularExpression& regEx) {
	if (regEx.getType() == RegularExpression::Type::Symbol)
	{
		return FiniteAutomata(regEx.getValue());
	}
	else if (regEx.getType() == RegularExpression::Type::Union)
	{
		FiniteAutomata lhs = buildFromRegex(regEx.getLeft());
		FiniteAutomata rhs = buildFromRegex(regEx.getRight());
		lhs.UnionWith(rhs);
		return lhs;
	}
	else if (regEx.getType() == RegularExpression::Type::Concatenation)
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
CustomCollection<int> FiniteAutomata::getNodeStates(const CustomCollection<int>& nodes, char symbol)const {
	CustomCollection<int>result;
	for (int j = 0; j < nodes.getSize(); j++)
	{
		int node = nodes[j];

		for (int i = 0; i < automata[node].getSize(); i++)
		{
			if (automata[node][i].symbol == symbol)
			{
				result.add(automata[node][i].dest);
			}
		}
	}
	return result;
}
struct StateTuple {
	CustomCollection<int> states;
	int newStateIndex = -1;
	StateTuple() = default;
	StateTuple(CustomCollection<int>&& states, int newStateIndex) {
		this->newStateIndex = newStateIndex;
		this->states = std::move(states);
	}
};
int findInTableByNode(int node, const CustomCollection<StateTuple>& stateTable) {
	for (int i = 0; i < stateTable.getSize(); i++)
	{
		if (stateTable[i].newStateIndex == node)
		{
			return i;
		}
	}
	return -1;
}
int findInTableByNodeByStates(const CustomCollection<int>& currentStates, const CustomCollection<StateTuple>& stateTable) {
	for (int i = 0; i < stateTable.getSize(); i++)
	{
		if (stateTable[i].states == currentStates)
		{
			return i;
		}
	}
	return -1;
}
bool FiniteAutomata::haveFinal(const CustomCollection<int>& nodes)const {
	for (int i = 0; i < nodes.getSize(); i++)
	{
		if (finalStates.find(nodes[i]) != -1)
		{
			return true;
		}
	}
	return false;
}

void FiniteAutomata::makeDeterministic() {

	FiniteAutomata newAutomaton;

	CustomCollection<StateTuple>stateTable(64);
	CustomCollection<int>queue;
	CustomCollection<int>newStart;
	if (multiplStarts)
	{
		newStart = startStates;
	}
	else
		newStart.add(startNode);
	queue.add(0);
	stateTable.add(StateTuple(std::move(newStart), 0));
	newAutomaton.addState();
	if (finalStates.find(startNode) != -1)
	{
		newAutomaton.makeFinal(0);
	}
	int currentCount = 0;
	while (queue.getSize() - currentCount > 0)
	{
		int currentInNew = queue[currentCount];

		CustomCollection<int>& currentStates = stateTable[findInTableByNode(currentInNew, stateTable)].states;
		for (int i = 0; i < alphabet.getSize(); i++)
		{
			char currentChar = alphabet[i];
			CustomCollection<int> nextStates = getNodeStates(currentStates, currentChar);
			int nextStatesPositionInTable = findInTableByNodeByStates(nextStates, stateTable);
			if (nextStatesPositionInTable == -1)
			{
				newAutomaton.addState();
				queue.add(newAutomaton.nodes - 1);
				if (haveFinal(nextStates))
				{
					newAutomaton.makeFinal(newAutomaton.nodes - 1);
				}
				stateTable.add(StateTuple(std::move(nextStates), newAutomaton.nodes - 1));
				newAutomaton.addTransition(currentInNew, Transition(newAutomaton.nodes - 1, currentChar));
			}
			else
			{
				newAutomaton.addTransition(currentInNew, Transition(stateTable[nextStatesPositionInTable].newStateIndex, currentChar));
			}

		}
		currentCount++;
	}
	newAutomaton.makeTotal();
	*this = std::move(newAutomaton);
}
void FiniteAutomata::addErrorState() {
	addState();
	for (int i = 0; i < alphabet.getSize(); i++)
	{
		addTransition(nodes - 1, Transition(nodes - 1, alphabet[i]));
	}

}
bool FiniteAutomata::haveTransitionWihtSymbol(int node, char symbol, int to) const {
	for (int i = 0; i < automata[node].getSize(); i++)
	{
		if (automata[node][i].symbol == symbol)
		{
			return to == -1 ? true : automata[node][i].dest == to;
		}
	}
	return false;
}

void FiniteAutomata::makeTotal() {
	bool haveError = false;
	for (int i = 0; i < nodes; i++)
	{
		for (int j = 0; j < alphabet.getSize(); j++)
		{
			if (!haveTransitionWihtSymbol(i, alphabet[j]))
			{
				if (!haveError)
				{
					addErrorState();
					haveError = true;
				}
				addTransition(i, Transition(nodes - 1, alphabet[j]));
			}
		}
	}
}
RegularExpression FiniteAutomata::getRegEx()const {
	RegularExpression result('\0');
	bool isSet = false;
	for (int i = 0; i < finalStates.getSize(); i++)
	{
		if (!isSet)
		{
			result = generateRegEx(startNode, finalStates[i], nodes, true);
			isSet = true;
		}
		else
		{
			result.UnionWith(generateRegEx(startNode, finalStates[i], nodes, true));
		}
	}
	return result;
}
RegularExpression FiniteAutomata::generateRegEx(int i, int j, int k, bool epsilon)const {
	if (k == 0)
	{
		RegularExpression result('\0');
		bool isSet = false;
		for (int symbol = 0; symbol < alphabet.getSize(); symbol++)
		{
			if (haveTransitionWihtSymbol(i, alphabet[symbol], j))
			{
				if (!isSet)
				{
					result.setValue(alphabet[symbol]);
					isSet = true;
				}
				else
					result.UnionWith(alphabet[symbol]);
			}
		}
		if (i == j && epsilon)
		{
			if (isSet)
			{
				result.UnionWith('$');
			}
			else
				result.setValue('$');
		}
		return result;
	}
	RegularExpression lhs = generateRegEx(i, j, k - 1, epsilon);
	RegularExpression rhs = generateRegEx(i, k - 1, k - 1, epsilon);
	RegularExpression middle = generateRegEx(k - 1, k - 1, k - 1, false);
	RegularExpression end = generateRegEx(k - 1, j, k - 1, epsilon);
	if (rhs.isEmpty() || end.isEmpty())
	{
		return lhs;
	}
	middle.KleeneStar();
	rhs.ConcatenationWith(middle);
	rhs.ConcatenationWith(end);

	if (lhs.isEmpty())
	{
		return rhs;
	}
	lhs.UnionWith(rhs);
	return lhs;
}
bool FiniteAutomata::accept(const MyString& word, int currentLetter, int node)const {
	if (word.length() == currentLetter)
	{
		if (currentLetter == 0)
		{
			return finalStates.find(startNode) != -1;
		}
		return finalStates.find(node) != -1;
	}
	if (node == -1)
	{
		if (multiplStarts)
		{
			for (int i = 0; i < startStates.getSize(); i++)
			{
				bool result= accept(word, currentLetter, startStates[i]);
				if (result)
				{
					return result;
				}
			}
			return false;
		}
		return accept(word, currentLetter, startNode);
	}
	for (int i = 0; i < automata[node].getSize(); i++)
	{
		if (automata[node][i].symbol == word[currentLetter])
		{
			bool result = accept(word, currentLetter + 1, automata[node][i].dest);
			if (result)
			{
				return result;
			}
		}
	}
	return false;
}
FiniteAutomata FiniteAutomata::getReverse() {
	FiniteAutomata result(nodes);
	result.alphabet = alphabet;
	for (int i = 0; i < nodes; i++)
	{
		for (int j = 0; j < automata[i].getSize(); j++)
		{
			result.addTransition(automata[i][j].dest, Transition(i, automata[i][j].symbol));
		}
	}
	result.makeFinal(startNode);
	result.addState();
	if (finalStates.getSize()>1)
	{
		result.multiplStarts = true;
		result.startStates = finalStates;
	}
	for (int i = 0; i < finalStates.getSize(); i++)
	{
		for (int j = 0; j < result.automata[finalStates[i]].getSize(); j++)
		{
			result.addTransition(nodes, Transition(result.automata[finalStates[i]][j].dest, result.automata[finalStates[i]][j].symbol));
		}
	}
	result.startNode = nodes;
	if (finalStates.find(startNode)!=-1)
	{
		result.makeFinal(nodes);
	}
	return result;
}
void FiniteAutomata::reverse() {
	FiniteAutomata result = getReverse();
	*this = std::move(result);
}

void FiniteAutomata::minimize() {
	makeDeterministic();
	reverse();
	makeDeterministic();
	reverse();
	makeDeterministic();
	multiplStarts = false;
}