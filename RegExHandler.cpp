#include "RegExHandler.h"
#include "KleeneStar.h"
#include "Concatenation.h"
#include "Union.h"
#include "Symbol.h"
#include "FiniteAutomata.h"

namespace {
	RegEx* cloneOrNull(RegEx* ptr) {
		if (ptr == nullptr)
		{
			return nullptr;
		}
		return ptr->clone();
	}
	RegEx**** initializeTable(int maxI, int maxJ) {
		RegEx**** table = new RegEx * **[maxI];
		for (int i = 0; i < maxI; i++)
		{
			table[i] = new RegEx * *[maxJ];
			for (int j = 0; j < maxJ; j++)
			{
				table[i][j] = new RegEx * [2];
			}
		}

		return table;
	}
	void deleteTable(RegEx**** table, int maxI, int maxJ) {
		for (int i = 0; i < maxI; i++)
		{
			for (int j = 0; j < maxJ; j++)
			{
				delete table[i][j][0];
				delete table[i][j][1];
				delete[] table[i][j];
			}
			delete[] table[i];
		}
		delete[] table;
	}
}

void RegExHandler::copyFrom(const RegExHandler& other) {
	ptr = other.ptr->clone();
}
void RegExHandler::moveFrom(RegExHandler&& other) {
	ptr = other.ptr;
	other.ptr = nullptr;
}
void RegExHandler::free() {
	delete ptr;
}

RegExHandler::RegExHandler(RegEx* ptr) {
	this->ptr = ptr;
}
RegExHandler::RegExHandler(const MyString& str) {
	ptr = buildRegExFromString(str);
}
RegExHandler::RegExHandler(const FiniteAutomata& automata) {
	ptr = buildRegExFromAutomaton(automata);
}

RegExHandler::~RegExHandler() {
	free();
}

RegExHandler::RegExHandler(const RegExHandler& other) {
	copyFrom(other);
}
RegExHandler::RegExHandler(RegExHandler&& other) {
	moveFrom(std::move(other));
}

RegExHandler& RegExHandler::operator=(const RegExHandler& other) {
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}
RegExHandler& RegExHandler::operator=(RegExHandler&& other) {
	if (this != &other)
	{
		free();
		copyFrom(std::move(other));
	}
	return *this;
}
RegEx* RegExHandler::processWordWithKleene(RegEx* lhs, RegEx* rhs, RegEx* middle, RegEx* end) {
	if (rhs == nullptr || end == nullptr)
	{
		delete middle;
		delete rhs;
		delete end;
		return lhs;
	}
	if (middle == nullptr)
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
		rhs = RegExHandler::makeConcatenation(rhs, middle);

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
		rhs = RegExHandler::makeConcatenation(rhs, end);
	if (lhs == nullptr)
		return rhs;
	if (lhs->getString() == rhs->getString())
	{
		delete rhs;
		return lhs;
	}
	lhs = RegExHandler::makeUnion(lhs, rhs);
	return lhs;
}
RegEx* RegExHandler::buildRegExFromAutomatonWithDP(const FiniteAutomata& automaton) {
	RegEx**** last = initializeTable(automaton.nodes,automaton.nodes);
	RegEx**** current = nullptr;
	for (int i = 0; i < automaton.nodes; i++)
	{
		for (int j = 0; j < automaton.nodes; j++)
		{
			last[i][j][0] = kleeneTheoremeBase(i,j,true,automaton);
			last[i][j][1] = kleeneTheoremeBase(i, j, false, automaton);
		}
	}

	for (int k = 1; k <= automaton.nodes; k++)
	{
		current = initializeTable(automaton.nodes, automaton.nodes);
		for (int i = 0; i < automaton.nodes; i++)
		{
			for (int j = 0; j < automaton.nodes; j++)
			{
				current[i][j][0] = processWordWithKleene(
					cloneOrNull(last[i][j][0]),
					cloneOrNull(last[i][k - 1][0]),
					cloneOrNull(last[k - 1][k - 1][1]),
					cloneOrNull(last[k - 1][j][0]));

				current[i][j][1] = processWordWithKleene(
					cloneOrNull(last[i][j][1]), 
					cloneOrNull(last[i][k - 1][1]), 
					cloneOrNull(last[k - 1][k - 1][1]), 
					cloneOrNull(last[k - 1][j][1]));
			}
		}
		deleteTable(last, automaton.nodes, automaton.nodes);
		last = current;
		current = nullptr;
	}
	RegEx* result = nullptr;
	for (int i = 0; i < automaton.nodes; i++)
	{
		if (!automaton.finalStates.check(i))
			continue;

		if (result==nullptr && last[automaton.startNode][i][0]!=nullptr)
			result = last[automaton.startNode][i][0]->clone();
		else if(last[automaton.startNode][i][0]!=nullptr)
			result = makeUnion(result, last[automaton.startNode][i][0]->clone());
	}

	deleteTable(last,automaton.nodes,automaton.nodes);
	return result;
}



RegEx* RegExHandler::kleeneTheoremeBase(int i,int j,bool epsilon,const FiniteAutomata& automata) {
	RegEx* result = nullptr;
	bool isSet = false;
	for (int symbol = 0; symbol < automata.alphabet.getSize(); symbol++)
	{
		if (automata.haveTransitionWihtSymbol(i, automata.alphabet[symbol], j))
		{
			if (!isSet)
			{
				result = RegExHandler::makeSymbol(automata.alphabet[symbol]);
				isSet = true;
			}
			else
				result = RegExHandler::makeUnion(result, RegExHandler::makeSymbol(automata.alphabet[symbol]));
		}
	}
	if (i == j && epsilon)
	{
		if (isSet && !result->isEpsilon())
			result = RegExHandler::makeUnion(result, RegExHandler::makeSymbol('$'));
		else if (!isSet)
			result = RegExHandler::makeSymbol('$');
	}
	return result;
}
RegEx* RegExHandler::generateRegExFromAutomatonInRange(int i, int j, int k, bool epsilon, const FiniteAutomata& automata) {
	if (k == 0)
		return kleeneTheoremeBase(i,j,epsilon,automata);

	RegEx* lhs = generateRegExFromAutomatonInRange(i, j, k - 1, epsilon,automata);
	RegEx* rhs = generateRegExFromAutomatonInRange(i, k - 1, k - 1, epsilon, automata);
	RegEx* middle = generateRegExFromAutomatonInRange(k - 1, k - 1, k - 1, false, automata);
	RegEx* end = generateRegExFromAutomatonInRange(k - 1, j, k - 1, epsilon, automata);
	
	return processWordWithKleene(lhs,rhs,middle,end);
}

RegEx* RegExHandler::buildRegExFromAutomaton(const FiniteAutomata& automata) {
	RegEx* result = nullptr;
	bool isSet = false;
	for (int i = 0; i < automata.nodes; i++)
	{
		if (!automata.finalStates.check(i))
			continue;
		if (!isSet)
		{
			result = generateRegExFromAutomatonInRange(automata.startNode, i, automata.nodes, true, automata);
			if (result!=nullptr)
			{
				isSet = true;
			}
		}
		else{
			RegEx* toUnion = generateRegExFromAutomatonInRange(automata.startNode, i, automata.nodes, true, automata);
			if (toUnion!=nullptr)
			{
				result = RegExHandler::makeUnion(result, toUnion);
			}
		}
	}
	return result;
}

RegEx* RegExHandler::buildRegExFromString(const MyString& str) {
	int a = 0;
	return getRegExFromString(str, a);
}
RegEx* RegExHandler::getRegExFromString(const MyString& str, int& currentPosition) {
	RegEx* result = nullptr;
	if (str[currentPosition] == '(')
	{
		currentPosition++;
		result = getRegExFromString(str, currentPosition);
		if (str[currentPosition + 1] == '*')
		{
			currentPosition += 2;
			result = new KleeneStarRegEx(result);
			if (currentPosition == str.length())
				return result;
		}
		else {
			currentPosition++;
		}
	}
	else {
		result = new Symbol(str[currentPosition]);
		currentPosition++;
		if (currentPosition < str.length() && str[currentPosition] == ')')
		{
			return result;
		}
	}

	for (; currentPosition < str.length(); currentPosition++)
	{
		if (str[currentPosition] == '(')
		{
			currentPosition++;
			RegEx* rhs = getRegExFromString(str, currentPosition);
			if (str[currentPosition + 1] == '*')
			{
				currentPosition++;
				rhs = new KleeneStarRegEx(rhs);
			}
			result = new ConcatenationRegEx(result, rhs);
		}
		else if (str[currentPosition] == ')')
		{
			return result;
		}
		else if (str[currentPosition] == '+') {
			currentPosition++;
			RegEx* right = getRegExFromString(str, currentPosition);
			result = new UnionRegEx(result, right);
			if (str[currentPosition] == ')')
				return result;
		}
		else if (str[currentPosition] == '.') {
			continue;
		}
		else {
			RegEx* symbol = new Symbol(str[currentPosition]);
			result = new ConcatenationRegEx(result, symbol);
		}
	}
	return result;
}
RegEx* RegExHandler::makeUnion(RegEx* left, RegEx* right) {
	return new UnionRegEx(left, right);
}
RegEx* RegExHandler::makeConcatenation(RegEx* left, RegEx* right) {
	return new ConcatenationRegEx(left, right);
}
RegEx* RegExHandler::makeKleeneStar(RegEx* left) {
	return new KleeneStarRegEx(left);
}
RegEx* RegExHandler::makeSymbol(char symbol) {
	return new Symbol(symbol);
}
MyString RegExHandler::getString() const {
	return ptr->getString();
}
FiniteAutomata RegExHandler::getAutomata() const {
	return ptr->getAutomaton();
}

void RegExHandler::UnionWith(const RegExHandler& other) {
	ptr = new UnionRegEx(ptr,other.ptr->clone());
}
void RegExHandler::ConcatenateWith(const RegExHandler& other) {
	ptr = new ConcatenationRegEx(ptr, other.ptr->clone());
}

void RegExHandler::UnionWith(RegExHandler&& other) {
	ptr = new UnionRegEx(ptr, other.ptr);
	other.ptr = nullptr;
}
void RegExHandler::ConcatenateWith(RegExHandler&& other) {
	ptr = new ConcatenationRegEx(ptr, other.ptr);
	other.ptr = nullptr;
}
void RegExHandler::KleeneStar() {
	ptr = new KleeneStarRegEx(ptr);
}
