#include "FiniteAutomata.h"
#include "MyQueue.hpp"
#include"RegExHandler.h"

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
}

FiniteAutomata::FiniteAutomata(int size) :automata(size), finalStates(size) {
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
	//FiniteAutomata toReplace = (*RegExParser::buildRegExFromString(regEx)).getAutomaton();
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
	//finalStates.add(index);
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
		//std::cout << finalStates[i] << ",";
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
FiniteAutomata FiniteAutomata::Difference(const FiniteAutomata& lhs, const FiniteAutomata& rhs) {
	FiniteAutomata result(lhs);
	result.DifferenceWith(rhs);
	return result;
}
FiniteAutomata& FiniteAutomata::KleeneStar() {
	for (int i = 0; i < nodes; i++)
	{
		if (!finalStates.check(i))
		{
			continue;
		}
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
		{
			continue;
		}
		//finalStates.add();
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
		{
			continue;
		}
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
		{
			continue;
		}
		finalStates.toggle(i + initialNodes);
	}
	multiplStarts = false;

	return *this;
}
FiniteAutomata& FiniteAutomata::Complement() {
	makeDeterministic();
	//makeTotal();
	BitSet newFinals(nodes);
	for (int i = 0; i < nodes; i++)
	{
		if (!finalStates.check(i))
		{
			newFinals.toggle(i);
		}
	}
	finalStates = std::move(newFinals);
	return *this;
}
FiniteAutomata& FiniteAutomata::IntersectWith(const FiniteAutomata& rhs) {
	FiniteAutomata rhsComp = FiniteAutomata(rhs).Complement();
	Complement();
	UnionWith(rhsComp);
	Complement();
	return *this;
}
FiniteAutomata& FiniteAutomata::DifferenceWith(const FiniteAutomata& rhs) {
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
			{
				result.add(automata[node][i].dest);
			}
		}
	}
	return result;
}


bool FiniteAutomata::haveFinal(const CustomCollection<int>& nodes)const {
	for (int i = 0; i < nodes.getSize(); i++)
	{
		if (finalStates.check(nodes[i]))
		{
			return true;
		}
	}
	return false;
}

void FiniteAutomata::makeDeterministic() {

	FiniteAutomata newAutomaton;

	CustomCollection<StateTuple>stateTable(128);
	MyQueue<int>queue;
	CustomCollection<int>newStart;
	if (multiplStarts)
	{
		newStart = startStates;
	}
	else
		newStart.add(startNode);
	queue.push(0);
	stateTable.add(StateTuple(std::move(newStart), 0));
	newAutomaton.addState();
	if (finalStates.check(startNode))
	{
		newAutomaton.makeFinal(0);
	}
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
RegEx* FiniteAutomata::generateRegEx(int i, int j, int k, bool epsilon)const {
	if (k == 0)
	{
		RegEx* result= nullptr;
		bool isSet = false;
		for (int symbol = 0; symbol < alphabet.getSize(); symbol++)
		{
			if (haveTransitionWihtSymbol(i, alphabet[symbol], j))
			{
				if (!isSet)
				{
					result = RegExHandler::makeSymbol(alphabet[symbol]);
					isSet = true;
				}
				else
					result = RegExHandler::makeUnion(result, RegExHandler::makeSymbol(alphabet[symbol]));
			}
		}
		if (i == j && epsilon)
		{
			if (isSet&&!result->isEpsilon())
				result = RegExHandler::makeUnion(result, RegExHandler::makeSymbol('$'));
			else if(!isSet)
				result= RegExHandler::makeSymbol('$');
		}
		return result;
	}
	RegEx* lhs = generateRegEx(i, j, k - 1, epsilon);
	RegEx* rhs = generateRegEx(i, k - 1, k - 1, epsilon);
	RegEx* middle = generateRegEx(k - 1, k - 1, k - 1, false);
	RegEx* end = generateRegEx(k - 1, j, k - 1, epsilon);
	if (rhs==nullptr || end==nullptr)
	{
		delete middle;
		delete rhs;
		delete end;
		return lhs;
	}
	if (middle==nullptr)
		middle = RegExHandler::makeSymbol('$');
	else
		middle = RegExHandler::makeKleeneStar(middle);

	//with middle
	if (rhs->isEpsilon())
	{
		delete rhs;
		rhs = middle;
		middle = nullptr;
	}
	else if (middle->isEpsilon())
		delete middle;
	else
		rhs = RegExHandler::makeConcatenation(rhs,middle);
	
	//with end
	if (rhs->isEpsilon())
	{
		delete rhs;
		rhs = end;
		end = nullptr;
	}
	else if (end->isEpsilon())
		delete end;
	else
		rhs =RegExHandler::makeConcatenation(rhs,end);
	if (lhs==nullptr)
		return rhs;
	if (lhs->getString()==rhs->getString())
	{
		delete rhs;
		return lhs;
	}
	lhs = RegExHandler::makeUnion(lhs,rhs);
	return lhs;
}
RegExHandler FiniteAutomata::getRegEx()const {
	RegEx* result=nullptr;
	bool isSet = false;
	for (int i = 0; i < nodes; i++)
	{
		if (!finalStates.check(i))
		{
			continue;
		}
		if (!isSet)
		{
			result = generateRegEx(startNode, i, nodes, true);
			isSet = true;
		}
		else
		{
			//result=result->getUnion(generateRegEx(startNode, i, nodes, true));
			//result = new UnionRegEx(result,generateRegEx(startNode, i, nodes, true));
			result = RegExHandler::makeUnion(result,generateRegEx(startNode, i, nodes, true));
		}
	}
	return RegExHandler( result);
}

bool FiniteAutomata::accept(const MyString& word, int currentLetter, int node)const {
	if (word.length() == currentLetter)
	{
		if (currentLetter == 0)
		{
			return finalStates.check(startNode);
		}
		return finalStates.check(node);
	}
	if (node == -1)
	{
		if (multiplStarts)
		{
			for (int i = 0; i < startStates.getSize(); i++)
			{
				bool result = accept(word, currentLetter, startStates[i]);
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
FiniteAutomata FiniteAutomata::getReverse() const {
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
	if (finalStates.getTruesCount() > 1)
	{
		result.multiplStarts = true;
		CustomCollection<int>newFinals(finalStates.getTruesCount());
		for (int i = 0; i < nodes; i++)
		{
			if (finalStates.check(i))
			{
				newFinals.add(i);
			}
		}
		result.startStates = std::move(newFinals);

		result.addState();
		for (int i = 0; i < nodes; i++)
		{
			if (!finalStates.check(i))
			{
				continue;
			}
			for (int j = 0; j < result.automata[i].getSize(); j++)
			{
				result.addTransition(nodes, Transition(result.automata[i][j].dest, result.automata[i][j].symbol));
			}
		}
		result.startNode = nodes;
		if (finalStates.check(startNode))
		{
			result.makeFinal(nodes);
		}
	}
	else
	{
		for (int i = 0; i < nodes; i++)
		{
			if (finalStates.check(i))
			{
				result.startNode = i;
				break;
			}
		}
	}
	//result.addState();
	//for (int i = 0; i < nodes; i++)
	//{
	//	if (!finalStates.check(i))
	//	{
	//		continue;
	//	}
	//	for (int j = 0; j < result.automata[i].getSize(); j++)
	//	{
	//		result.addTransition(nodes, Transition(result.automata[i][j].dest, result.automata[i][j].symbol));
	//	}
	//}
	//result.startNode = nodes;
	/*if (finalStates.check(startNode))
	{
		result.makeFinal(nodes);
	}*/
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

	while (!queue.isEmpty())
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