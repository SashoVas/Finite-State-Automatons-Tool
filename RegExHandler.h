#pragma once
#include "RegEx.h"

class RegExHandler {
	RegEx* ptr;
	void copyFrom(const RegExHandler& other);
	void moveFrom(RegExHandler&& other);
	void free();
	static RegEx* processWordWithKleene(RegEx* lhs, RegEx* rhs, RegEx* middle, RegEx* end);//induction step
public:
	RegExHandler(RegEx* ptr);
	RegExHandler(const MyString& str);
	RegExHandler(const FiniteAutomata& automata);
	~RegExHandler();

	RegExHandler(const RegExHandler& other);
	RegExHandler(RegExHandler&& other);

	void UnionWith(const RegExHandler& other);
	void ConcatenateWith(const RegExHandler& other);

	void UnionWith(RegExHandler&& other);
	void ConcatenateWith(RegExHandler&& other);
	void KleeneStar();

	RegExHandler& operator=(const RegExHandler& other);
	RegExHandler& operator=(RegExHandler&& other);

	MyString getString() const;//Post-order traversal
	FiniteAutomata getAutomata() const;//Post-order traversal

	//Factory methods
	static RegEx* kleeneTheoremeBase(int i, int j, bool epsilon, const FiniteAutomata& automata);//induction base
	static RegEx* generateRegExFromAutomatonInRange(int i, int j, int k, bool epsilon, const FiniteAutomata& automata);
	static RegEx* buildRegExFromAutomaton(const FiniteAutomata& automata);//kleene theoreme 
	static RegEx* buildRegExFromAutomatonWithDP(const FiniteAutomata& automaton);//kleene theoreme with dynamic programing

	static RegEx* buildRegExFromString(const MyString& str);//parsing string to regEx tree
	static RegEx* getRegExFromString(const MyString& str, int& currentPosition);//used by buildRegExFromString
	static RegEx* makeUnion(RegEx* left, RegEx* right);
	static RegEx* makeConcatenation(RegEx* left, RegEx* right);
	static RegEx* makeKleeneStar(RegEx* left);
	static RegEx* makeSymbol(char symbol);
};
