#pragma once
#include "FiniteAutomata.h"
#include "BitSet.h"
#include "RegExParser.h"
class Tests {
public:
	static bool runAllTests();

	static bool runRegularExpressionTests();
	static bool runRegularExpressionGetRegExTests();

	static bool runAutomatonTests();

	static bool runAutomatonOperationsTests();
	static bool runAutomatonUnionTests();
	static bool runAutomatonConcatenationTests();
	static bool runAutomatonKleeneStarTests();
	static bool runAutomatonComplementTests();
	static bool runAutomatonIntersectionTests();
	static bool runAutomatonDifferenceTests();

	static bool runAutomatonFunctionsTests();
	static bool runAutomatonTotalizationTests();
	static bool runAutomatonDeterminizationTests();
	static bool runAutomatonMinimizationTests();
	static bool runAutomatonReverseTests();
	static bool isEmptyLanguageTests();
	static bool runAutomatonGetRegExTests();

	static bool runCollectionsTests();
	static bool runBitSetCheckAndToggleTests();
	static bool runBitSetAddAndResizeTests();
};

bool Tests::runRegularExpressionTests() {
	std::cout << "RegEx parse tests:" << std::endl;
	runRegularExpressionGetRegExTests();
	return true;
}
bool Tests::runRegularExpressionGetRegExTests() {
	
	std::cout << ((*RegExParser::buildRegExFromString("a(a+b)*b+b(a+b)*a")).getString() == "(a((a+b))*b+b((a+b))*a)") << std::endl;
	std::cout << ((*RegExParser::buildRegExFromString("a")).getString() == "a") << std::endl;
	std::cout << ((*RegExParser::buildRegExFromString("ab")).getString() == "ab") << std::endl;
	std::cout << ((*RegExParser::buildRegExFromString("ab+ac")).getString() == "(ab+ac)") << std::endl;
	std::cout << ((*RegExParser::buildRegExFromString("(ab+ac)*")).getString() == "((ab+ac))*") << std::endl;
	std::cout << ((*RegExParser::buildRegExFromString("(ab+ac)*+a")).getString() == "(((ab+ac))*+a)") << std::endl;
	std::cout << ((*RegExParser::buildRegExFromString("(ab+ac)*+a+b")).getString() == "(((ab+ac))*+(a+b))") << std::endl;
	std::cout << ((*RegExParser::buildRegExFromString("(ab+ac)*+a+ba")).getString() == "(((ab+ac))*+(a+ba))") << std::endl;
	std::cout << ((*RegExParser::buildRegExFromString("((ab+ac)*+a+ba)c")).getString() == "(((ab+ac))*+(a+ba))c") << std::endl;
	std::cout << ((*RegExParser::buildRegExFromString("((ab+ac)*+a+ba)c+d")).getString() == "((((ab+ac))*+(a+ba))c+d)") << std::endl;
	std::cout << ((*RegExParser::buildRegExFromString("((ab+ac)*+a+ba)c+d+b")).getString() == "((((ab+ac))*+(a+ba))c+(d+b))") << std::endl;
	std::cout << ((*RegExParser::buildRegExFromString("((ab+ac)*+a+ba)c+d+(b)*")).getString() == "((((ab+ac))*+(a+ba))c+(d+(b)*))") << std::endl;
	std::cout << ((*RegExParser::buildRegExFromString("(a)*")).getString() == "(a)*") << std::endl;
	std::cout << ((*RegExParser::buildRegExFromString("(a)*+(b)*")).getString() == "((a)*+(b)*)") << std::endl;
	std::cout << ((*RegExParser::buildRegExFromString("((a)*+(b)*)*")).getString() == "(((a)*+(b)*))*") << std::endl;
	std::cout << ((*RegExParser::buildRegExFromString("((ab)*+(bb)*)*")).getString() == "(((ab)*+(bb)*))*") << std::endl;
	std::cout << ((*RegExParser::buildRegExFromString("abcd")).getString() == "abcd") << std::endl;
	std::cout << ((*RegExParser::buildRegExFromString("(a)*(b)*")).getString() == "(a)*(b)*") << std::endl;
	std::cout << ((*RegExParser::buildRegExFromString("((a)*(b)*)*")).getString() == "((a)*(b)*)*") << std::endl;
	std::cout << ((*RegExParser::buildRegExFromString("(((a)*(b)*)*)*")).getString() == "(((a)*(b)*)*)*") << std::endl;
	std::cout << ((*RegExParser::buildRegExFromString("(((a)*(b)*)*)*+(((a)*(b)*)*)*")).getString() == "((((a)*(b)*)*)*+(((a)*(b)*)*)*)") << std::endl;
	std::cout << ((*RegExParser::buildRegExFromString("((((a)*(b)*)*)*+(((a)*(b)*)*)*)c")).getString() == "((((a)*(b)*)*)*+(((a)*(b)*)*)*)c") << std::endl;
	std::cout << ((*RegExParser::buildRegExFromString("(((a)*(b)*)*)*+(((a)*(b)*)*)*c")).getString() == "((((a)*(b)*)*)*+(((a)*(b)*)*)*c)") << std::endl;
	std::cout << ((*RegExParser::buildRegExFromString("a((((a)*(b)*)*)*+(((a)*(b)*)*)*c)")).getString() == "a((((a)*(b)*)*)*+(((a)*(b)*)*)*c)") << std::endl;
	std::cout << ((*RegExParser::buildRegExFromString("a((((a)*(b)*)*)*+(((a)*(b)*)*)*c)")).getString() == "a((((a)*(b)*)*)*+(((a)*(b)*)*)*c)") << std::endl;
	std::cout << ((*RegExParser::buildRegExFromString("ab(a+c)*")).getString() == "ab((a+c))*") << std::endl;

	return true;
}
bool Tests::runAutomatonUnionTests() {
	//Arange
	//RegularExpression firstRegEx("(a)*b(b)*");
	//RegularExpression secondRegEx("(c)*d");
	FiniteAutomata firstAutomaton("(a)*b(b)*");
	FiniteAutomata secondAutomaton("(c)*d");
	//Act
	FiniteAutomata result = FiniteAutomata::Union(firstAutomaton,secondAutomaton);
	//Assert
	std::cout << !(result.accept("a") )<< std::endl;
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
bool Tests::runAutomatonConcatenationTests() {
	//Arange
	//RegularExpression firstRegEx("(a+b)*");
	//RegularExpression secondRegEx("(c+d)*");
	FiniteAutomata firstAutomaton("(a+b)*");
	FiniteAutomata secondAutomaton("(c+d)*");
	//Act
	FiniteAutomata result = FiniteAutomata::Concatenation(firstAutomaton,secondAutomaton);
	//Assert
	std::cout << !result.accept("aabacabab")<<std::endl;
	std::cout << !result.accept("adb")<<std::endl;
	std::cout << !result.accept("acb")<<std::endl;
	std::cout << !result.accept("db")<<std::endl;
	std::cout << !result.accept("cb")<<std::endl;
	std::cout << !result.accept("ca")<<std::endl;
	std::cout << !result.accept("da")<<std::endl;

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
bool Tests::runAutomatonKleeneStarTests() {
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
bool Tests::runAutomatonComplementTests() {
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
bool Tests::runAutomatonIntersectionTests() {
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
bool Tests::runAutomatonDifferenceTests() {
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
bool Tests::runAutomatonTotalizationTests() {
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
bool Tests::runAutomatonDeterminizationTests() {
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
bool Tests::runAutomatonReverseTests() {
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
bool Tests::runAutomatonMinimizationTests() {
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
bool Tests::runAutomatonOperationsTests() {
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
bool Tests::runAutomatonFunctionsTests() {
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
bool Tests::runAutomatonTests() {
	std::cout << "Automaton operation tests:" << std::endl;
	runAutomatonOperationsTests();
	std::cout << "Automaton functions tests:" << std::endl;
	runAutomatonFunctionsTests();
	return true;
}
bool Tests::runAllTests() {
	std::cout << "Collection tests:" << std::endl;
	runCollectionsTests();
	std::cout << "RegEx tests:" << std::endl;
	runRegularExpressionTests();
	std::cout << "Automaton tests:" << std::endl;
	runAutomatonTests();
	return true;
}
bool Tests::isEmptyLanguageTests() {
	//Arange
	//RegularExpression firstRegEx("a+b");
	FiniteAutomata firstAutomaton("a+b");
	FiniteAutomata secondAutomaton("a+b");
	firstAutomaton.DifferenceWith(secondAutomaton);
	//Act
	bool result=firstAutomaton.isEmptyLanguage();
	bool result2= secondAutomaton.isEmptyLanguage();
	//Assert
	std::cout << result << std::endl;
	std::cout << !result2 << std::endl;
	return true;
}
bool Tests::runCollectionsTests() {
	std::cout << "BitSet tests:" << std::endl;
	std::cout << "BitSet toggle and check Tests:" << std::endl;
	runBitSetCheckAndToggleTests();
	std::cout << "BitSet add and resize Tests:" << std::endl;
	runBitSetAddAndResizeTests();
	return true;
}
bool Tests::runBitSetCheckAndToggleTests()
{
	//Arange
	BitSet bitSet(64);
	//Act
	for (int i = 0; i < 64; i+=2)
	{
		bitSet.toggle(i);
	}
	//Assert
	for (int i = 0; i < 64; i++)
	{
		if (i%2==bitSet.check(i))
		{
			std::cout << 0 << std::endl;
			return false;
		}
	}
	std::cout << 1 << std::endl;
	return true;
}
bool Tests::runBitSetAddAndResizeTests() {
	//Arange
	BitSet bitSet(2);
	//Act
	for (int i = 0; i < 1000; i++)
	{
		bitSet.add(i % 2);
	}
	//Assert
	for (int i = 2; i < 1000; i++)
	{
		if (bitSet.check(i)!=i%2)
		{
			std::cout << 0 << std::endl;
			return false;
		}
	}
	std::cout << 1 << std::endl;
	return true;
}
bool Tests::runAutomatonGetRegExTests() {
	//Arange
	FiniteAutomata automata("(a+b)*abcd+dc");
	automata.minimize();
	//Act
	RegEx* regEx = automata.getRegEx();
	FiniteAutomata result(regEx->getString());
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
	delete regEx;
	return true;
}
