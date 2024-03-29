#include "FiniteAutomata.h"
#include "MyQueue.hpp"

namespace {//Logic for determization
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
				return i;
		}
		return -1;
	}

	int findInTableByNodeByStates(const CustomCollection<int>& currentStates, const CustomCollection<StateTuple>& stateTable) {
		for (int i = 0; i < stateTable.getSize(); i++)
		{
			if (stateTable[i].states == currentStates)
				return i;
		}
		return -1;
	}

	bool isInRange(int l, int r, int val) {
		return val >= l && val <= r;
	}
}

FiniteAutomata::FiniteAutomata(int size) :automata(size), finalStates(size) {
	startNode = 0;
	nodes = size;

	for (int i = 0; i < size; i++)
		automata.add(CustomCollection<Transition>());
}

FiniteAutomata::FiniteAutomata(char symbol) {
	if (!isInRange('0', '9', symbol) && !isInRange('a', 'z', symbol) && !isInRange('A', 'Z', symbol) && symbol != '$')
		throw std::invalid_argument("Letter not allowed!");

	startNode = 0;
	CustomCollection<Transition>t;
	if (symbol!='$')
	{
		t.add(Transition(1, symbol));
		automata.add(t);
		automata.add(CustomCollection<Transition>());
		nodes = 2;
		finalStates.add();
		finalStates.add();
		finalStates.toggle(1);
		alphabet.add(symbol);
	}
	else
	{
		automata.add(CustomCollection<Transition>());
		nodes = 1;
		finalStates.add();
		finalStates.toggle(0);
	}
}

FiniteAutomata::FiniteAutomata(const MyString& regEx) {
	FiniteAutomata toReplace = RegExHandler(regEx).getAutomata();
	*this = std::move(toReplace);
}

FiniteAutomata::FiniteAutomata(const RegExHandler& regEx) {
	*this = std::move(regEx.getAutomata());
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

	finalStates.toggle(index);
}

void FiniteAutomata::print()const {
	if (multiplStarts)
	{
		std::cout << "Start nodes:" << std::endl;
		for (int i = 0; i < startStates.getSize(); i++)
		{
			std::cout << i << ',';
		}
		std::cout << std::endl;
	}
	else
	{
		std::cout << "Start node:" << startNode << std::endl;
	}

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
	std::cout << "Final states(" << finalStates.getTruesCount() << "):";
	for (int i = 0; i < nodes; i++)
	{
		if (finalStates.check(i))
		{
			std::cout << i << ",";
		}
	}
	std::cout << std::endl;
}

void FiniteAutomata::addState() {
	automata.add(CustomCollection<Transition>());
	finalStates.add();
	nodes++;
}

void FiniteAutomata::changeStart(int index) {
	if (index >= nodes)
		throw std::invalid_argument("invalid index");

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
			automata[initialNodes + i].add(Transition(other.automata[i][j].dest + initialNodes, other.automata[i][j].symbol));
		}
	}
}

FiniteAutomata FiniteAutomata::Union(const FiniteAutomata& lhs, const FiniteAutomata& rhs) {
	FiniteAutomata result(lhs);
	result.UnionWith(rhs);
	return result;
}

FiniteAutomata FiniteAutomata::Concatenation(const FiniteAutomata& lhs, const FiniteAutomata& rhs) {
	FiniteAutomata result(lhs);
	result.ConcatenationWith(rhs);
	return result;
}

FiniteAutomata FiniteAutomata::KleeneStar(const FiniteAutomata& lhs) {
	FiniteAutomata result(lhs);
	result.KleeneStar();
	return result;
}

FiniteAutomata FiniteAutomata::Complement(const FiniteAutomata& lhs) {
	FiniteAutomata result(lhs);
	result.Complement();
	return result;
}

FiniteAutomata FiniteAutomata::Intersection(const FiniteAutomata& lhs, const FiniteAutomata& rhs) {
	FiniteAutomata result(lhs);
	result.IntersectWith(rhs);
	return result;
}

FiniteAutomata FiniteAutomata::Difference(const FiniteAutomata& lhs, const FiniteAutomata& rhs) {//A\B = A & (!B)
	FiniteAutomata result(lhs);
	result.DifferenceWith(rhs);
	return result;
}

FiniteAutomata& FiniteAutomata::KleeneStar() {
	for (int i = 0; i < nodes; i++)
	{
		if (!finalStates.check(i))
			continue;
		for (int j = 0; j < automata[startNode].getSize(); j++)
		{
			if (i == startNode)
				continue;
			automata[i].add(
				Transition(automata[startNode][j].dest
					, automata[startNode][j].symbol));
		}
	}

	if (!finalStates.check(startNode))
		finalStates.toggle(startNode);
	multiplStarts = false;
	return *this;
}

FiniteAutomata& FiniteAutomata::UnionWith(const FiniteAutomata& rhs) {
	int intitialNodes = nodes;
	combine(rhs);

	for (int i = 0; i < rhs.nodes; i++) {
		if (!rhs.finalStates.check(i))
			continue;

		finalStates.toggle(i + intitialNodes);
	}
	addState();
	for (int i = 0; i < automata[startNode].getSize(); i++)
		automata[nodes - 1].add(Transition(automata[startNode][i].dest, automata[startNode][i].symbol));
	for (int i = 0; i < rhs.automata[rhs.startNode].getSize(); i++)
		automata[nodes - 1].add(Transition(rhs.automata[rhs.startNode][i].dest + intitialNodes, rhs.automata[rhs.startNode][i].symbol));

	if (finalStates.check(startNode) || rhs.finalStates.check(rhs.startNode))
		finalStates.toggle(nodes - 1);

	startNode = nodes - 1;
	multiplStarts = false;

	return *this;
}

FiniteAutomata& FiniteAutomata::ConcatenationWith(const FiniteAutomata& rhs) {
	int initialNodes = nodes;
	combine(rhs);

	for (int i = 0; i < nodes; i++)
	{
		if (!finalStates.check(i))
			continue;
		for (int j = 0; j < rhs.automata[rhs.startNode].getSize(); j++)
		{
			automata[i].add(
				Transition(
					rhs.automata[rhs.startNode][j].dest + initialNodes
					, rhs.automata[rhs.startNode][j].symbol)
			);
		}

	}

	if (!rhs.finalStates.check(rhs.startNode))
		finalStates.empty();

	for (int i = 0; i < rhs.nodes; i++) {
		if (!rhs.finalStates.check(i))
			continue;
		finalStates.toggle(i + initialNodes);
	}
	multiplStarts = false;

	return *this;
}

FiniteAutomata& FiniteAutomata::Complement() {
	makeDeterministic();
	BitSet newFinals(nodes);
	for (int i = 0; i < nodes; i++)
	{
		if (!finalStates.check(i))
			newFinals.toggle(i);
	}
	finalStates = std::move(newFinals);
	return *this;
}

FiniteAutomata& FiniteAutomata::IntersectWith(const FiniteAutomata& rhs) {//De Morgan's law
	FiniteAutomata rhsComp = FiniteAutomata(rhs).Complement();
	Complement();
	UnionWith(rhsComp);
	Complement();
	return *this;
}

FiniteAutomata& FiniteAutomata::DifferenceWith(const FiniteAutomata& rhs) {//A\B = A & (!B)
	FiniteAutomata rhsComp = FiniteAutomata(rhs).Complement();
	IntersectWith(rhsComp);
	return *this;
}

CustomCollection<int> FiniteAutomata::getNodeStates(const CustomCollection<int>& nodes, char symbol)const {
	CustomCollection<int>result;
	for (int j = 0; j < nodes.getSize(); j++)
	{
		int node = nodes[j];

		for (int i = 0; i < automata[node].getSize(); i++)
		{
			if (automata[node][i].symbol == symbol)
				result.add(automata[node][i].dest);
		}
	}
	return result;
}

bool FiniteAutomata::haveFinal(const CustomCollection<int>& nodes)const {
	for (int i = 0; i < nodes.getSize(); i++)
	{
		if (finalStates.check(nodes[i]))
			return true;
	}
	return false;
}

//Can be improved with hash table
void FiniteAutomata::makeDeterministic() {

	FiniteAutomata newAutomaton;

	CustomCollection<StateTuple>stateTable(1024);
	MyQueue<int>queue;
	CustomCollection<int>newStart;

	if (multiplStarts)
		newStart = startStates;
	else
		newStart.add(startNode);

	queue.push(0);
	stateTable.add(StateTuple(std::move(newStart), 0));
	newAutomaton.addState();

	if (finalStates.check(startNode))
		newAutomaton.makeFinal(0);

	while (!queue.isEmpty())
	{
		int currentInNew = queue.peek();
		queue.pop();
		CustomCollection<int>& currentStates = stateTable[findInTableByNode(currentInNew, stateTable)].states;
		for (int i = 0; i < alphabet.getSize(); i++)
		{
			char currentChar = alphabet[i];
			CustomCollection<int> nextStates = getNodeStates(currentStates, currentChar);
			int nextStatesPositionInTable = findInTableByNodeByStates(nextStates, stateTable);

			if (nextStatesPositionInTable == -1)
			{
				newAutomaton.addState();
				queue.push(newAutomaton.nodes - 1);

				if (haveFinal(nextStates))
					newAutomaton.makeFinal(newAutomaton.nodes - 1);

				stateTable.add(StateTuple(std::move(nextStates), newAutomaton.nodes - 1));
				newAutomaton.addTransition(currentInNew, Transition(newAutomaton.nodes - 1, currentChar));
			}
			else
				newAutomaton.addTransition(currentInNew, Transition(stateTable[nextStatesPositionInTable].newStateIndex, currentChar));

		}
	}
	newAutomaton.makeTotal();
	*this = std::move(newAutomaton);
}

void FiniteAutomata::addErrorState() {
	addState();
	for (int i = 0; i < alphabet.getSize(); i++)
		addTransition(nodes - 1, Transition(nodes - 1, alphabet[i]));
}

bool FiniteAutomata::haveTransitionWihtSymbol(int node, char symbol, int to) const {
	for (int i = 0; i < automata[node].getSize(); i++)
	{
		if (automata[node][i].symbol == symbol)
			return to == -1 ? true : automata[node][i].dest == to;
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

RegExHandler FiniteAutomata::getRegExSlow()const {//Implementation of kleene theoreme for turning automaton to regEx
	return RegExHandler( RegExHandler::buildRegExFromAutomaton(*this));
}

RegExHandler FiniteAutomata::getRegExFast()const {//Implementation of kleene theoreme for turning automaton to regEx with dynamic programing
	return RegExHandler(RegExHandler::buildRegExFromAutomatonWithDP(*this));
}

bool FiniteAutomata::accept(const MyString& word, int currentLetter, int node)const {
	if (word.length() == currentLetter)
	{
		if (currentLetter == 0)
			return finalStates.check(startNode);

		return finalStates.check(node);
	}
	if (node == -1)
	{
		if (multiplStarts)
		{
			for (int i = 0; i < startStates.getSize(); i++)
			{
				if (accept(word, currentLetter, startStates[i]))
					return true;
			}
			return false;
		}
		return accept(word, currentLetter, startNode);
	}
	for (int i = 0; i < automata[node].getSize(); i++)
	{
		if (automata[node][i].symbol == word[currentLetter] && accept(word, currentLetter + 1, automata[node][i].dest))
			return true;
	}
	return false;
}

void FiniteAutomata::setReverseTransitions(FiniteAutomata& result)const {
	for (int i = 0; i < nodes; i++)
	{
		for (int j = 0; j < automata[i].getSize(); j++)
			result.addTransition(automata[i][j].dest, Transition(i, automata[i][j].symbol));
	}
}

void FiniteAutomata::setReverseMultipleStart(FiniteAutomata& result) const{
	result.multiplStarts = true;
	CustomCollection<int>newFinals(finalStates.getTruesCount());
	for (int i = 0; i < nodes; i++)
	{
		if (finalStates.check(i))
			newFinals.add(i);
	}
	result.startStates = std::move(newFinals);

	result.addState();
	for (int i = 0; i < nodes; i++)
	{
		if (!finalStates.check(i))
			continue;
		for (int j = 0; j < result.automata[i].getSize(); j++)
			result.addTransition(nodes, Transition(result.automata[i][j].dest, result.automata[i][j].symbol));
	}
	result.startNode = nodes;
	if (finalStates.check(startNode))
		result.makeFinal(nodes);
}

void FiniteAutomata::setFinalToBeStart(FiniteAutomata& result)const {
	for (int i = 0; i < nodes; i++)
	{
		if (finalStates.check(i))
		{
			result.startNode = i;
			break;
		}
	}
}

FiniteAutomata FiniteAutomata::getReverse() const {
	FiniteAutomata result(nodes);
	result.alphabet = alphabet;

	setReverseTransitions(result);

	result.makeFinal(startNode);

	if (finalStates.getTruesCount() > 1)
		setReverseMultipleStart(result);
	else
		setFinalToBeStart(result);

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

bool FiniteAutomata::isEmptyLanguage()const {
	MyQueue<int>queue;
	queue.push(startNode);
	bool* visited = new bool[nodes] {false};

	while (!queue.isEmpty())//BFS
	{
		int current = queue.peek();
		queue.pop();
		for (int i = 0; i < automata[current].getSize(); i++)
		{
			if (visited[automata[current][i].dest])
				continue;

			if (finalStates.check(automata[current][i].dest))
			{
				delete[] visited;
				return false;
			}
			queue.push(automata[current][i].dest);
			visited[automata[current][i].dest] = true;
		}
	}
	delete[] visited;
	return true;
}

bool FiniteAutomata::isDeterministic()const {
	int letters['z' + 1] = {0};
	for (int i = 0; i < nodes; i++)
	{
		if (automata[i].getSize()!=alphabet.getSize())
			return false;

		for (int j = 0; j < automata[i].getSize(); j++)
		{
			if (letters[automata[i][j].symbol]==i+1)
				return false;

			letters[automata[i][j].symbol] ++;
		}
	}
	return true;
}
