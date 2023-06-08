#include"AutomatonTests.h"
#include "FiniteAutomata.h"
#include "RegExHandler.h"
bool AutomatonTests::runAutomatonUnionTests() {
	//Arange
	//RegularExpression firstRegEx("(a)*b(b)*");
	//RegularExpression secondRegEx("(c)*d");
	FiniteAutomata firstAutomaton("(a)*b(b)*");
	FiniteAutomata secondAutomaton("(c)*d");
	//Act
	FiniteAutomata result = FiniteAutomata::Union(firstAutomaton, secondAutomaton);
	//Assert
	std::cout << !(result.accept("a")) << std::endl;
	std::cout << !(result.accept("bbbbbbba")) << std::endl;
	std::cout << !(result.accept("dddddddd")) << std::endl;
	std::cout << !(result.accept("ac")) << std::endl;
	std::cout << !(result.accept("ad")) << std::endl;
	std::cout << !(result.accept("ca")) << std::endl;
	std::cout << !(result.accept("cb")) << std::endl;
	std::cout << !result.accept("ccccccc") << std::endl;
	std::cout << !result.accept("") << std::endl;

	std::cout << result.accept("ab") << std::endl;
	std::cout << result.accept("b") << std::endl;
	std::cout << result.accept("aaaaab") << std::endl;
	std::cout << result.accept("aaaaabbbbbbb") << std::endl;
	std::cout << result.accept("cd") << std::endl;
	std::cout << result.accept("d") << std::endl;
	std::cout << result.accept("cccccccd") << std::endl;
	return true;
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
	std::cout << !result.accept("aabacabab") << std::endl;
	std::cout << !result.accept("adb") << std::endl;
	std::cout << !result.accept("acb") << std::endl;
	std::cout << !result.accept("db") << std::endl;
	std::cout << !result.accept("cb") << std::endl;
	std::cout << !result.accept("ca") << std::endl;
	std::cout << !result.accept("da") << std::endl;

	std::cout << result.accept("abaabaabacdddcccd") << std::endl;
	std::cout << result.accept("a") << std::endl;
	std::cout << result.accept("ab") << std::endl;
	std::cout << result.accept("ac") << std::endl;
	std::cout << result.accept("ad") << std::endl;
	std::cout << result.accept("b") << std::endl;
	std::cout << result.accept("ba") << std::endl;
	std::cout << result.accept("bc") << std::endl;
	std::cout << result.accept("bd") << std::endl;
	std::cout << result.accept("c") << std::endl;
	std::cout << result.accept("cd") << std::endl;
	std::cout << result.accept("d") << std::endl;
	std::cout << result.accept("dc") << std::endl;
	std::cout << result.accept("") << std::endl;
	return true;
}
bool AutomatonTests::runAutomatonKleeneStarTests() {
	//Arange
	//RegularExpression firstRegEx("a+b");
	FiniteAutomata firstAutomaton("a+b");
	//Act
	FiniteAutomata result = FiniteAutomata::KleeneStar(firstAutomaton);
	//Assert
	std::cout << result.accept("ab") << std::endl;
	std::cout << result.accept("ba") << std::endl;
	std::cout << result.accept("bababaabbaaabbba") << std::endl;
	std::cout << result.accept("abaaabbbbaaba") << std::endl;
	std::cout << result.accept("") << std::endl;
	return true;
}
bool AutomatonTests::runAutomatonComplementTests() {
	//Arange
	//RegularExpression firstRegEx("(a+b)*(c+d)+ca");
	FiniteAutomata result("(a+b)*(c+d)+ca");
	//Act
	result.Complement();
	//Assert
	std::cout << result.accept("a") << std::endl;
	std::cout << result.accept("b") << std::endl;
	std::cout << result.accept("ab") << std::endl;
	std::cout << result.accept("ccc") << std::endl;
	std::cout << result.accept("ddd") << std::endl;
	std::cout << result.accept("acac") << std::endl;
	std::cout << result.accept("abab") << std::endl;
	std::cout << result.accept("adad") << std::endl;
	std::cout << result.accept("bdbd") << std::endl;
	std::cout << result.accept("baba") << std::endl;
	std::cout << result.accept("bcbc") << std::endl;
	std::cout << result.accept("") << std::endl;

	std::cout << !result.accept("abc") << std::endl;
	std::cout << !result.accept("ac") << std::endl;
	std::cout << !result.accept("ad") << std::endl;
	std::cout << !result.accept("bd") << std::endl;
	std::cout << !result.accept("bc") << std::endl;
	std::cout << !result.accept("ca") << std::endl;

	return true;
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
	std::cout << result.accept("babc") << std::endl;
	std::cout << result.accept("babccc") << std::endl;

	std::cout << !result.accept("ababc") << std::endl;
	std::cout << !result.accept("ababcababc") << std::endl;
	std::cout << !result.accept("abab") << std::endl;
	std::cout << !result.accept("aaaaaaabab") << std::endl;
	std::cout << !result.accept("aaaaaaababc") << std::endl;
	std::cout << !result.accept("abababab") << std::endl;
	std::cout << !result.accept("bab") << std::endl;
	std::cout << !result.accept("baaaaab") << std::endl;
	std::cout << !result.accept("baaaaabc") << std::endl;
	std::cout << !result.accept("baaaaabcccc") << std::endl;
	std::cout << !result.accept("babbab") << std::endl;
	std::cout << !result.accept("") << std::endl;

	return true;
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
	std::cout << result.accept("aaaaaabbaaabbaaabbaa") << std::endl;
	std::cout << result.accept("bab") << std::endl;
	std::cout << result.accept("bbaabbabbaaabbabbaabbaaa") << std::endl;
	std::cout << result.accept("aaaaaaaaaaaa") << std::endl;
	std::cout << result.accept("bbbbbbb") << std::endl;
	std::cout << result.accept("a") << std::endl;
	std::cout << result.accept("b") << std::endl;
	std::cout << result.accept("ba") << std::endl;
	std::cout << result.accept("ab") << std::endl;
	std::cout << result.accept("") << std::endl;

	std::cout << !result.accept("aba") << std::endl;
	std::cout << !result.accept("babab") << std::endl;
	std::cout << !result.accept("baba") << std::endl;
	std::cout << !result.accept("abab") << std::endl;
	std::cout << !result.accept("aaaaaabaaaaaaaaaaa") << std::endl;
	std::cout << !result.accept("abaaaabbabaababababaaba") << std::endl;
	std::cout << !result.accept("bbbbbbbbababbbbbbbbbbbb") << std::endl;
	std::cout << !result.accept("abaabaaaababbbaaba") << std::endl;
	std::cout << !result.accept("bbabaabbbaabaababa") << std::endl;
	return true;
}
bool AutomatonTests::runAutomatonTotalizationTests() {
	//Arange
	//RegularExpression firstRegEx("(a+b)*cd");
	FiniteAutomata result("(a+b)*cd");
	//Act
	result.makeTotal();
	//Assert
	std::cout << !result.accept("a") << std::endl;
	std::cout << !result.accept("b") << std::endl;
	std::cout << !result.accept("ab") << std::endl;
	std::cout << !result.accept("ababababab") << std::endl;
	std::cout << !result.accept("abababababcc") << std::endl;
	std::cout << !result.accept("c") << std::endl;
	std::cout << !result.accept("d") << std::endl;
	std::cout << !result.accept("abd") << std::endl;
	std::cout << !result.accept("abc") << std::endl;
	std::cout << !result.accept("") << std::endl;

	std::cout << result.accept("cd") << std::endl;
	std::cout << result.accept("acd") << std::endl;
	std::cout << result.accept("bcd") << std::endl;
	std::cout << result.accept("babbaaababcd") << std::endl;
	std::cout << result.accept("ababbaaababcd") << std::endl;
	return true;
}
bool AutomatonTests::runAutomatonDeterminizationTests() {
	//Arange
	//RegularExpression firstRegEx("(a+b)*(c+d)*+ca");
	FiniteAutomata result("(a+b)*(c+d)*+ca");
	//Act
	result.makeDeterministic();
	//Arrange
	std::cout << !result.accept("cdcddcdaba") << std::endl;
	std::cout << !result.accept("cb") << std::endl;
	std::cout << !result.accept("db") << std::endl;
	std::cout << !result.accept("da") << std::endl;

	std::cout << result.accept("abcd") << std::endl;
	std::cout << result.accept("a") << std::endl;
	std::cout << result.accept("b") << std::endl;
	std::cout << result.accept("c") << std::endl;
	std::cout << result.accept("d") << std::endl;
	std::cout << result.accept("ab") << std::endl;
	std::cout << result.accept("ac") << std::endl;
	std::cout << result.accept("ad") << std::endl;
	std::cout << result.accept("ba") << std::endl;
	std::cout << result.accept("bc") << std::endl;
	std::cout << result.accept("bd") << std::endl;
	std::cout << result.accept("cd") << std::endl;
	std::cout << result.accept("dc") << std::endl;
	std::cout << result.accept("ca") << std::endl;
	std::cout << result.accept("") << std::endl;

	return true;
}
bool AutomatonTests::runAutomatonReverseTests() {
	//Arange
	//RegularExpression firstRegEx("(a+b)*(c+d)+ca");
	FiniteAutomata result("(a+b)*(c+d)+ca");
	//Act
	result.reverse();
	//Assert
	std::cout << !result.accept("ab") << std::endl;
	std::cout << !result.accept("ccc") << std::endl;
	std::cout << !result.accept("ddd") << std::endl;
	std::cout << !result.accept("ad") << std::endl;
	std::cout << !result.accept("bd") << std::endl;
	std::cout << !result.accept("bc") << std::endl;
	std::cout << !result.accept("") << std::endl;

	std::cout << result.accept("ac") << std::endl;
	std::cout << result.accept("cabaab") << std::endl;
	std::cout << result.accept("d") << std::endl;
	std::cout << result.accept("da") << std::endl;
	std::cout << result.accept("db") << std::endl;
	std::cout << result.accept("cb") << std::endl;
	std::cout << result.accept("ca") << std::endl;
	std::cout << result.accept("c") << std::endl;
	std::cout << result.accept("dabaabaab") << std::endl;

	return true;
}
bool AutomatonTests::runAutomatonMinimizationTests() {
	//Arange
	//RegularExpression firstRegEx("(a+b)*(c+d)*+ca");
	FiniteAutomata result("(a+b)*(c+d)*+ca");
	//Act
	result.minimize();
	//Arrange
	std::cout << !result.accept("cdcddcdaba") << std::endl;
	std::cout << !result.accept("cb") << std::endl;
	std::cout << !result.accept("db") << std::endl;
	std::cout << !result.accept("da") << std::endl;

	std::cout << result.accept("abcd") << std::endl;
	std::cout << result.accept("a") << std::endl;
	std::cout << result.accept("b") << std::endl;
	std::cout << result.accept("c") << std::endl;
	std::cout << result.accept("d") << std::endl;
	std::cout << result.accept("ab") << std::endl;
	std::cout << result.accept("ac") << std::endl;
	std::cout << result.accept("ad") << std::endl;
	std::cout << result.accept("ba") << std::endl;
	std::cout << result.accept("bc") << std::endl;
	std::cout << result.accept("bd") << std::endl;
	std::cout << result.accept("cd") << std::endl;
	std::cout << result.accept("dc") << std::endl;
	std::cout << result.accept("ca") << std::endl;
	std::cout << result.accept("") << std::endl;
	return true;
}
bool AutomatonTests::runAutomatonOperationsTests() {
	std::cout << "Union tests:" << std::endl;
	runAutomatonUnionTests();
	std::cout << "Concatenation tests:" << std::endl;
	runAutomatonConcatenationTests();
	std::cout << "KleeneStar tests:" << std::endl;
	runAutomatonKleeneStarTests();
	std::cout << "Complement tests:" << std::endl;
	runAutomatonComplementTests();
	std::cout << "Intersection tests:" << std::endl;
	runAutomatonIntersectionTests();
	std::cout << "Difference tests:" << std::endl;
	runAutomatonDifferenceTests();
	return true;
}
bool AutomatonTests::runAutomatonFunctionsTests() {
	std::cout << "Totalization tests:" << std::endl;
	runAutomatonTotalizationTests();
	std::cout << "Determinization tests:" << std::endl;
	runAutomatonDeterminizationTests();
	std::cout << "Reverse tests:" << std::endl;
	runAutomatonReverseTests();
	std::cout << "Minimization tests:" << std::endl;
	runAutomatonMinimizationTests();
	std::cout << "Is empty language tests:" << std::endl;
	isEmptyLanguageTests();
	std::cout << "Get RegEx tests:" << std::endl;
	runAutomatonGetRegExTests();
	return true;
}
bool AutomatonTests::runAutomatonTests() {
	std::cout << "Automaton operation tests:" << std::endl;
	runAutomatonOperationsTests();
	std::cout << "Automaton functions tests:" << std::endl;
	runAutomatonFunctionsTests();
	return true;
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
	return true;
}
bool AutomatonTests::runAutomatonGetRegExTests() {
	//Arange
	FiniteAutomata automata("(a+b)*abcd+dc");
	automata.minimize();
	//Act
	//RegExHandler regEx = automata.getRegEx();
	FiniteAutomata result(automata.getRegEx());
	//Assert

	std::cout << result.accept("abcd") << std::endl;
	std::cout << result.accept("aabcd") << std::endl;
	std::cout << result.accept("babcd") << std::endl;
	std::cout << result.accept("babababbbbaababcd") << std::endl;
	std::cout << result.accept("aabababbbbaababcd") << std::endl;
	std::cout << result.accept("dc") << std::endl;

	std::cout << !result.accept("a") << std::endl;
	std::cout << !result.accept("ab") << std::endl;
	std::cout << !result.accept("abc") << std::endl;
	std::cout << !result.accept("b") << std::endl;
	std::cout << !result.accept("c") << std::endl;
	std::cout << !result.accept("d") << std::endl;
	std::cout << !result.accept("bcd") << std::endl;
	std::cout << !result.accept("") << std::endl;
	std::cout << !result.accept("ababababbbababc") << std::endl;
	std::cout << !result.accept("ababababbbababd") << std::endl;
	return true;
}
