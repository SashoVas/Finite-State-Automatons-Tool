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
	CustomCollection<char> alphabet;

	//used when getting the reverse
	CustomCollection<int> startStates;
	bool multiplStarts = false;

	void combine(const FiniteAutomata& other);//used in union and concatenation to combine states
	void addToAlphabet(char symbol);

	//helper functions for makeDeterministic
	bool haveTransitionWihtSymbol(int node, char symbol, int to = -1)const;
	void addErrorState();
	CustomCollection<int> getNodeStates(const CustomCollection<int>& nodes, char symbol)const;
	bool haveFinal(const CustomCollection<int>& nodes)const;

	//helper functions for reverse
	void setReverseMultipleStart(FiniteAutomata& result)const;
	void setReverseTransitions(FiniteAutomata& result)const;
	void setFinalToBeStart(FiniteAutomata& result)const;
public:

	FiniteAutomata(int size);//creating automaton with fixed size
	FiniteAutomata() = default;
	FiniteAutomata(char symbol);//creating automaton that recognizes one symbol
	FiniteAutomata(const MyString& regEx);//creating automaton by string of regEx
	FiniteAutomata(const RegExHandler& regEx);//creating automaton by regEx

	//Base functions
	void addState();
	void changeStart(int index);
	void addTransition(int index, const Transition& transition);
	void makeFinal(int index);

	void makeDeterministic();
	void makeTotal();//adds error state and transitions to it
	void minimize();
	void reverse();

	bool isEmptyLanguage()const;//BFS from start, searching for final state
	bool isDeterministic()const;

	RegExHandler getRegExSlow()const;//kleene theoreme 
	RegExHandler getRegExFast()const;//kleene theoreme with dynamic programing

	FiniteAutomata getReverse()const;

	FiniteAutomata& UnionWith(const FiniteAutomata& rhs);
	FiniteAutomata& ConcatenationWith(const FiniteAutomata& rhs);
	FiniteAutomata& KleeneStar();
	FiniteAutomata& Complement();
	FiniteAutomata& IntersectWith(const FiniteAutomata& rhs);//De Morgan's law. The automatons should have the same alphabet
	FiniteAutomata& DifferenceWith(const FiniteAutomata& rhs);//A\B = A & (!B)

	void print()const;
	bool accept(const MyString& word, int currentLetter = 0, int node = -1)const;

	static FiniteAutomata Union(const FiniteAutomata& lhs, const FiniteAutomata& rhs);
	static FiniteAutomata Concatenation(const FiniteAutomata& lhs, const FiniteAutomata& rhs);
	static FiniteAutomata KleeneStar(const FiniteAutomata& lhs);
	static FiniteAutomata Complement(const FiniteAutomata& lhs);
	static FiniteAutomata Intersection(const FiniteAutomata& lhs, const FiniteAutomata& rhs);//De Morgan's law
	static FiniteAutomata Difference(const FiniteAutomata& lhs, const FiniteAutomata& rhs);//A\B = A & (!B)

	friend class AutomatonFileHandler;//for serialization and deserialization
	friend RegEx* RegExHandler::buildRegExFromAutomaton(const FiniteAutomata& automaton);//for turning automaton to regEx
	friend RegEx* RegExHandler::buildRegExFromAutomatonWithDP(const FiniteAutomata& automaton);//for turning automaton to regEx
	friend RegEx* RegExHandler::kleeneTheoremeBase(int i, int j, bool epsilon, const FiniteAutomata& automata);//for turning automaton to regEx
};