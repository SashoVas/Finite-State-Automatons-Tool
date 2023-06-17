#include"AutomatonTests.h"
#include "RegExHandler.h"

bool AutomatonTests::assertWordAccepted(const MyString& word, const FiniteAutomata& automata) {
	bool result = automata.accept(word);
	std::cout << result << std::endl;
	return result;
}
bool AutomatonTests::assertWordRejected(const MyString& word, const FiniteAutomata& automata) {
	bool result = automata.accept(word);
	std::cout << !result << std::endl;
	return !result;
}


bool AutomatonTests::runAutomatonUnionTests() {
	//Arange
	//RegularExpression firstRegEx("(a)*b(b)*");
	//RegularExpression secondRegEx("(c)*d");
	FiniteAutomata firstAutomaton("(a)*b(b)*");
	FiniteAutomata secondAutomaton("(c)*d");
	//Act
	FiniteAutomata result = FiniteAutomata::Union(firstAutomaton, secondAutomaton);
	//Assert
	bool isValid = true;

	isValid = isValid && assertWordRejected("a", result);
	isValid = isValid && assertWordRejected("a", result);
	isValid = isValid && assertWordRejected("bbbbbbba", result);
	isValid = isValid && assertWordRejected("dddddddd", result);
	isValid = isValid && assertWordRejected("ac", result);
	isValid = isValid && assertWordRejected("ad", result);
	isValid = isValid && assertWordRejected("ca", result);
	isValid = isValid && assertWordRejected("cb", result);
	isValid = isValid && assertWordRejected("ccccccc", result);
	isValid = isValid && assertWordRejected("", result);


	isValid = isValid && assertWordAccepted("ab", result);
	isValid = isValid && assertWordAccepted("b", result);
	isValid = isValid && assertWordAccepted("aaaaab", result);
	isValid = isValid && assertWordAccepted("aaaaabbbbbbb", result);
	isValid = isValid && assertWordAccepted("cd", result);
	isValid = isValid && assertWordAccepted("d", result);
	isValid = isValid && assertWordAccepted("cccccccd", result);
	return isValid;
}
bool AutomatonTests::runAutomatonConcatenationTests() {
	//Arange
	//RegularExpression firstRegEx("(a+b)*");
	//RegularExpression secondRegEx("(c+d)*");
	FiniteAutomata firstAutomaton("(a+b)*");
	FiniteAutomata secondAutomaton("(c+d)*");
	//Act
	FiniteAutomata result = FiniteAutomata::Concatenation(firstAutomaton, secondAutomaton);
	//Assert
	bool isValid = true;
	isValid = isValid && assertWordRejected("aabacabab", result);
	isValid = isValid && assertWordRejected("adb", result);
	isValid = isValid && assertWordRejected("acb", result);
	isValid = isValid && assertWordRejected("db", result);
	isValid = isValid && assertWordRejected("cb", result);
	isValid = isValid && assertWordRejected("ca", result);
	isValid = isValid && assertWordRejected("da", result);

	isValid = isValid && assertWordAccepted("abaabaabacdddcccd", result);
	isValid = isValid && assertWordAccepted("a", result);
	isValid = isValid && assertWordAccepted("ab", result);
	isValid = isValid && assertWordAccepted("ac", result);
	isValid = isValid && assertWordAccepted("ad", result);
	isValid = isValid && assertWordAccepted("b", result);
	isValid = isValid && assertWordAccepted("ba", result);
	isValid = isValid && assertWordAccepted("bc", result);
	isValid = isValid && assertWordAccepted("bd", result);
	isValid = isValid && assertWordAccepted("c", result);
	isValid = isValid && assertWordAccepted("cd", result);
	isValid = isValid && assertWordAccepted("d", result);
	isValid = isValid && assertWordAccepted("dc", result);
	isValid = isValid && assertWordAccepted("", result);
	return isValid;
}
bool AutomatonTests::runAutomatonKleeneStarTests() {
	//Arange
	//RegularExpression firstRegEx("a+b");
	FiniteAutomata firstAutomaton("a+b");
	//Act
	FiniteAutomata result = FiniteAutomata::KleeneStar(firstAutomaton);
	//Assert
	bool isValid = true;
	isValid = isValid && assertWordAccepted("ab", result);
	isValid = isValid && assertWordAccepted("ba", result);
	isValid = isValid && assertWordAccepted("bababaabbaaabbba", result);
	isValid = isValid && assertWordAccepted("abaaabbbbaaba", result);
	isValid = isValid && assertWordAccepted("", result);
	return isValid;
}
bool AutomatonTests::runAutomatonComplementTests() {
	//Arange
	//RegularExpression firstRegEx("(a+b)*(c+d)+ca");
	FiniteAutomata result("(a+b)*(c+d)+ca");
	//Act
	result.Complement();
	//Assert
	bool isValid = true;
	isValid = isValid && assertWordAccepted("a", result);
	isValid = isValid && assertWordAccepted("b", result);
	isValid = isValid && assertWordAccepted("ab", result);
	isValid = isValid && assertWordAccepted("ccc", result);
	isValid = isValid && assertWordAccepted("ddd", result);
	isValid = isValid && assertWordAccepted("acac", result);
	isValid = isValid && assertWordAccepted("abab", result);
	isValid = isValid && assertWordAccepted("adad", result);
	isValid = isValid && assertWordAccepted("bdbd", result);
	isValid = isValid && assertWordAccepted("baba", result);
	isValid = isValid && assertWordAccepted("bcbc", result);
	isValid = isValid && assertWordAccepted("", result);

	isValid = isValid && assertWordRejected("abc", result);
	isValid = isValid && assertWordRejected("ac", result);
	isValid = isValid && assertWordRejected("ad", result);
	isValid = isValid && assertWordRejected("bd", result);
	isValid = isValid && assertWordRejected("bc", result);
	isValid = isValid && assertWordRejected("ca", result);

	return isValid;
}
bool AutomatonTests::runAutomatonIntersectionTests() {
	//Arange
	//RegularExpression firstRegEx("((a)*bab(c)*)*");
	//RegularExpression secondRegEx("b(a)*bc(c)*");
	FiniteAutomata firstAutomaton("((a)*bab(c)*)*");
	FiniteAutomata secondAutomaton("b(a)*bc(c)*");
	//Act
	FiniteAutomata result = FiniteAutomata::Intersection(firstAutomaton, secondAutomaton);
	//Assert
	bool isValid = true;
	isValid = isValid && assertWordAccepted("babc", result);;
	isValid = isValid && assertWordAccepted("babccc", result);

	isValid = isValid && assertWordRejected("ababc", result);
	isValid = isValid && assertWordRejected("ababcababc", result);
	isValid = isValid && assertWordRejected("abab", result);
	isValid = isValid && assertWordRejected("aaaaaaabab", result);
	isValid = isValid && assertWordRejected("aaaaaaababc", result);
	isValid = isValid && assertWordRejected("abababab", result);
	isValid = isValid && assertWordRejected("bab", result);
	isValid = isValid && assertWordRejected("baaaaab", result);
	isValid = isValid && assertWordRejected("baaaaabc", result);
	isValid = isValid && assertWordRejected("baaaaabcccc", result);
	isValid = isValid && assertWordRejected("babbab", result);
	isValid = isValid && assertWordRejected("", result);

	return isValid;
}
bool AutomatonTests::runAutomatonDifferenceTests() {
	//Arange
	//RegularExpression firstRegEx("(a+b)*");
	//RegularExpression secondRegEx("((a+b)*aba(a+b)*)");
	FiniteAutomata firstAutomaton("(a+b)*");
	FiniteAutomata secondAutomaton("((a+b)*aba(a+b)*)");
	//Act
	FiniteAutomata result = FiniteAutomata::Difference(firstAutomaton, secondAutomaton);
	//Assert
	bool isValid = true;
	isValid = isValid && assertWordAccepted("aaaaaabbaaabbaaabbaa", result);
	isValid = isValid && assertWordAccepted("bab", result);
	isValid = isValid && assertWordAccepted("bbaabbabbaaabbabbaabbaaa", result);
	isValid = isValid && assertWordAccepted("aaaaaaaaaaaa", result);
	isValid = isValid && assertWordAccepted("bbbbbbb", result);
	isValid = isValid && assertWordAccepted("a", result);
	isValid = isValid && assertWordAccepted("b", result);
	isValid = isValid && assertWordAccepted("ba", result);
	isValid = isValid && assertWordAccepted("ab", result);
	isValid = isValid && assertWordAccepted("", result);

	isValid = isValid && assertWordRejected("aba", result);
	isValid = isValid && assertWordRejected("babab", result);
	isValid = isValid && assertWordRejected("baba", result);
	isValid = isValid && assertWordRejected("abab", result);
	isValid = isValid && assertWordRejected("aaaaaabaaaaaaaaaaa", result);
	isValid = isValid && assertWordRejected("abaaaabbabaababababaaba", result);
	isValid = isValid && assertWordRejected("bbbbbbbbababbbbbbbbbbbb", result);
	isValid = isValid && assertWordRejected("abaabaaaababbbaaba", result);
	isValid = isValid && assertWordRejected("bbabaabbbaabaababa", result);
	return isValid;
}
bool AutomatonTests::runAutomatonTotalizationTests() {
	//Arange
	//RegularExpression firstRegEx("(a+b)*cd");
	FiniteAutomata result("(a+b)*cd");
	//Act
	result.makeTotal();
	//Assert
	bool isValid = true;
	isValid = isValid && assertWordRejected("a", result);
	isValid = isValid && assertWordRejected("b", result);
	isValid = isValid && assertWordRejected("ab", result);
	isValid = isValid && assertWordRejected("ababababab", result);
	isValid = isValid && assertWordRejected("abababababcc", result);
	isValid = isValid && assertWordRejected("c", result);
	isValid = isValid && assertWordRejected("d", result);
	isValid = isValid && assertWordRejected("abd", result);
	isValid = isValid && assertWordRejected("abc", result);
	isValid = isValid && assertWordRejected("", result);

	isValid = isValid && assertWordAccepted("cd", result);
	isValid = isValid && assertWordAccepted("acd", result);
	isValid = isValid && assertWordAccepted("bcd", result);
	isValid = isValid && assertWordAccepted("babbaaababcd", result);
	isValid = isValid && assertWordAccepted("ababbaaababcd", result);
	return isValid;
}
bool AutomatonTests::runAutomatonDeterminizationTests() {
	//Arange
	//RegularExpression firstRegEx("(a+b)*(c+d)*+ca");
	FiniteAutomata result("(a+b)*(c+d)*+ca");
	//Act
	result.makeDeterministic();
	//Arrange
	bool isValid = true;
	isValid = isValid && assertWordRejected("cdcddcdaba", result);
	isValid = isValid && assertWordRejected("cb", result);
	isValid = isValid && assertWordRejected("db", result);
	isValid = isValid && assertWordRejected("da", result);

	isValid = isValid && assertWordAccepted("abcd", result);
	isValid = isValid && assertWordAccepted("a", result);
	isValid = isValid && assertWordAccepted("b", result);
	isValid = isValid && assertWordAccepted("c", result);
	isValid = isValid && assertWordAccepted("d", result);
	isValid = isValid && assertWordAccepted("ab", result);
	isValid = isValid && assertWordAccepted("ac", result);
	isValid = isValid && assertWordAccepted("ad", result);
	isValid = isValid && assertWordAccepted("ba", result);
	isValid = isValid && assertWordAccepted("bc", result);
	isValid = isValid && assertWordAccepted("bd", result);
	isValid = isValid && assertWordAccepted("cd", result);
	isValid = isValid && assertWordAccepted("dc", result);
	isValid = isValid && assertWordAccepted("ca", result);
	isValid = isValid && assertWordAccepted("", result);

	return isValid;
}
bool AutomatonTests::runAutomatonReverseTests() {
	//Arange
	//RegularExpression firstRegEx("(a+b)*(c+d)+ca");
	FiniteAutomata result("(a+b)*(c+d)+ca");
	//Act
	result.reverse();
	//Assert
	bool isValid = true;
	isValid = isValid && assertWordRejected("ab", result);
	isValid = isValid && assertWordRejected("ccc", result);;
	isValid = isValid && assertWordRejected("ddd", result);;
	isValid = isValid && assertWordRejected("ad", result);
	isValid = isValid && assertWordRejected("bd", result);
	isValid = isValid && assertWordRejected("bc", result);
	isValid = isValid && assertWordRejected("", result);

	isValid = isValid && assertWordAccepted("ac", result);
	isValid = isValid && assertWordAccepted("cabaab", result);
	isValid = isValid && assertWordAccepted("d", result);
	isValid = isValid && assertWordAccepted("da", result);
	isValid = isValid && assertWordAccepted("db", result);
	isValid = isValid && assertWordAccepted("cb", result);
	isValid = isValid && assertWordAccepted("ca", result);
	isValid = isValid && assertWordAccepted("c", result);
	isValid = isValid && assertWordAccepted("dabaabaab", result);

	return isValid;
}
bool AutomatonTests::runAutomatonMinimizationTests() {
	//Arange
	//RegularExpression firstRegEx("(a+b)*(c+d)*+ca");
	FiniteAutomata result("(a+b)*(c+d)*+ca");
	//Act
	result.minimize();
	//Arrange
	bool isValid = true;
	isValid = isValid && assertWordRejected("cdcddcdaba", result);
	isValid = isValid && assertWordRejected("cb", result);
	isValid = isValid && assertWordRejected("db", result);
	isValid = isValid && assertWordRejected("da", result);

	isValid = isValid && assertWordAccepted("abcd", result);
	isValid = isValid && assertWordAccepted("a", result);
	isValid = isValid && assertWordAccepted("b", result);
	isValid = isValid && assertWordAccepted("c", result);
	isValid = isValid && assertWordAccepted("d", result);
	isValid = isValid && assertWordAccepted("ab", result);
	isValid = isValid && assertWordAccepted("ac", result);
	isValid = isValid && assertWordAccepted("ad", result);
	isValid = isValid && assertWordAccepted("ba", result);
	isValid = isValid && assertWordAccepted("bc", result);
	isValid = isValid && assertWordAccepted("bd", result);
	isValid = isValid && assertWordAccepted("cd", result);
	isValid = isValid && assertWordAccepted("dc", result);
	isValid = isValid && assertWordAccepted("ca", result);
	isValid = isValid && assertWordAccepted("", result);
	return isValid;
}
bool AutomatonTests::runAutomatonOperationsTests() {
	std::cout << "Union tests:" << std::endl;
	bool unionTest = runAutomatonUnionTests();
	std::cout << "Concatenation tests:" << std::endl;
	bool concatenationTests = runAutomatonConcatenationTests();
	std::cout << "KleeneStar tests:" << std::endl;
	bool kleeneStarTests = runAutomatonKleeneStarTests();
	std::cout << "Complement tests:" << std::endl;
	bool complementTests = runAutomatonComplementTests();
	std::cout << "Intersection tests:" << std::endl;
	bool intersectionTests = runAutomatonIntersectionTests();
	std::cout << "Difference tests:" << std::endl;
	bool differenceTests = runAutomatonDifferenceTests();
	return unionTest && concatenationTests && kleeneStarTests && complementTests && intersectionTests && differenceTests;
}
bool AutomatonTests::runAutomatonFunctionsTests() {
	std::cout << "Totalization tests:" << std::endl;
	bool totalizationTests = runAutomatonTotalizationTests();
	std::cout << "Determinization tests:" << std::endl;
	bool determinizationTests = runAutomatonDeterminizationTests();
	std::cout << "Reverse tests:" << std::endl;
	bool reverseTests = runAutomatonReverseTests();
	std::cout << "Minimization tests:" << std::endl;
	bool minimizationTests = runAutomatonMinimizationTests();
	std::cout << "Is empty language tests:" << std::endl;
	bool emptyLanguageTests = isEmptyLanguageTests();
	std::cout << "Get RegEx slow tests:" << std::endl;
	bool getRegExSlowTests = runAutomatonGetRegExSlowTests();
	std::cout << "Get RegEx fast tests:" << std::endl;
	bool getRegExFastTests = runAutomatonGetRegExFastTests();
	return totalizationTests && determinizationTests && reverseTests && minimizationTests && emptyLanguageTests && getRegExSlowTests && getRegExFastTests;
}
bool AutomatonTests::runAutomatonTests() {
	std::cout << "Automaton operation tests:" << std::endl;
	bool operationsTests = runAutomatonOperationsTests();
	std::cout << "Automaton functions tests:" << std::endl;
	bool functionsTests = runAutomatonFunctionsTests();
	return operationsTests && functionsTests;
}
bool AutomatonTests::isEmptyLanguageTests() {
	//Arange
	//RegularExpression firstRegEx("a+b");
	FiniteAutomata firstAutomaton("a+b");
	FiniteAutomata secondAutomaton("a+b");
	firstAutomaton.DifferenceWith(secondAutomaton);
	//Act
	bool result = firstAutomaton.isEmptyLanguage();
	bool result2 = secondAutomaton.isEmptyLanguage();
	//Assert
	std::cout << result << std::endl;
	std::cout << !result2 << std::endl;
	return result && !result2;
}
bool AutomatonTests::runAutomatonGetRegExSlowTests() {
	//Arange
	FiniteAutomata automata("(a+b)*abcd+dc");
	automata.minimize();
	//Act
	FiniteAutomata result(automata.getRegExSlow());
	//Assert
	bool isValid = true;
	isValid = isValid && assertWordAccepted("abcd", result);
	isValid = isValid && assertWordAccepted("aabcd", result);
	isValid = isValid && assertWordAccepted("babcd", result);
	isValid = isValid && assertWordAccepted("babababbbbaababcd", result);
	isValid = isValid && assertWordAccepted("aabababbbbaababcd", result);
	isValid = isValid && assertWordAccepted("dc", result);

	isValid = isValid && assertWordRejected("a", result);
	isValid = isValid && assertWordRejected("ab", result);
	isValid = isValid && assertWordRejected("abc", result);
	isValid = isValid && assertWordRejected("b", result);
	isValid = isValid && assertWordRejected("c", result);
	isValid = isValid && assertWordRejected("d", result);
	isValid = isValid && assertWordRejected("bcd", result);
	isValid = isValid && assertWordRejected("", result);
	isValid = isValid && assertWordRejected("ababababbbababc", result);
	isValid = isValid && assertWordRejected("ababababbbababd", result);
	return isValid;
}

bool AutomatonTests::runAutomatonGetRegExFastTests() {
	//Arange
	FiniteAutomata automata("(a+b)*abcd+dc");
	automata.minimize();
	//Act
	FiniteAutomata result(automata.getRegExFast());
	//Assert
	bool isValid = true;
	isValid = isValid && assertWordAccepted("abcd", result);
	isValid = isValid && assertWordAccepted("aabcd", result);
	isValid = isValid && assertWordAccepted("babcd", result);
	isValid = isValid && assertWordAccepted("babababbbbaababcd", result);
	isValid = isValid && assertWordAccepted("aabababbbbaababcd", result);
	isValid = isValid && assertWordAccepted("dc", result);

	isValid = isValid && assertWordRejected("a", result);
	isValid = isValid && assertWordRejected("ab", result);
	isValid = isValid && assertWordRejected("abc", result);
	isValid = isValid && assertWordRejected("b", result);
	isValid = isValid && assertWordRejected("c", result);
	isValid = isValid && assertWordRejected("d", result);
	isValid = isValid && assertWordRejected("bcd", result);
	isValid = isValid && assertWordRejected("", result);
	isValid = isValid && assertWordRejected("ababababbbababc", result);
	isValid = isValid && assertWordRejected("ababababbbababd", result);
	return isValid;
}
