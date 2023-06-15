#pragma once
#include <iostream>
#include "CustomCollection.hpp"
#include "BitSet.h"
#include "MyString.h"
#include "Transition.h"
#include "RegExHandler.h";

class FiniteAutomata {
private:
	int nodes = 0;
	int startNode = 0;

	CustomCollection <CustomCollection<Transition>> automata;
	BitSet finalStates;
	CustomCollection<int> startStates;
	bool multiplStarts = false;
	CustomCollection<char> alphabet;

	void combine(const FiniteAutomata& other);
	void addToAlphabet(char symbol);
	//
	bool haveTransitionWihtSymbol(int node, char symbol, int to = -1)const;
	void addErrorState();
	CustomCollection<int> getNodeStates(const CustomCollection<int>& nodes, char symbol)const;
	bool haveFinal(const CustomCollection<int>& nodes)const;

	void setReverseMultipleStart(FiniteAutomata& result)const;
	void setReverseTransitions(FiniteAutomata& result)const;
	void setFinalToBeStart(FiniteAutomata& result)const;
	//
public:

	FiniteAutomata(int size);
	FiniteAutomata() = default;
	FiniteAutomata(char symbol);
	//
	FiniteAutomata(const MyString& regEx);
	FiniteAutomata(const RegExHandler& regEx);
	//

	void addState();
	void changeStart(int index);
	void addTransition(int index, const Transition& transition);
	void makeFinal(int index);

	FiniteAutomata getReverse()const;

	void makeDeterministic();
	void makeTotal();
	void minimize();
	void reverse();

	bool isEmptyLanguage()const;

	RegExHandler getRegEx()const;

	FiniteAutomata& UnionWith(const FiniteAutomata& rhs);
	FiniteAutomata& ConcatenationWith(const FiniteAutomata& rhs);
	FiniteAutomata& KleeneStar();
	FiniteAutomata& Complement();
	FiniteAutomata& IntersectWith(const FiniteAutomata& rhs);//The automatons should have the same alphabet
	FiniteAutomata& DifferenceWith(const FiniteAutomata& rhs);

	void print()const;
	bool accept(const MyString& word, int currentLetter = 0, int node = -1)const;

	static FiniteAutomata Union(const FiniteAutomata& lhs, const FiniteAutomata& rhs);
	static FiniteAutomata Concatenation(const FiniteAutomata& lhs, const FiniteAutomata& rhs);
	static FiniteAutomata KleeneStar(const FiniteAutomata& lhs);
	static FiniteAutomata Complement(const FiniteAutomata& lhs);
	static FiniteAutomata Intersection(const FiniteAutomata& lhs, const FiniteAutomata& rhs);
	static FiniteAutomata Difference(const FiniteAutomata& lhs, const FiniteAutomata& rhs);

	friend class AutomatonFileHandler;
	friend RegEx* RegExHandler::generateRegExFromAutomatonInRange(int i, int j, int k, bool epsilon, const FiniteAutomata& automaton);
	friend RegEx* RegExHandler::buildRegExFromAutomaton(const FiniteAutomata& automaton);
};