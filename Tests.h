#pragma once
#include "RegularExpression.h"
#include "FiniteAutomata.h"
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

	static bool runAutomatonFunctionsTests();
	static bool runAutomatonTotalizationTests();
	static bool runAutomatonDeterminizationTests();
	static bool runAutomatonMinimizationTests();
	static bool runAutomatonReverseTests();

};

bool Tests::runRegularExpressionTests() {
	std::cout << "RegEx parse tests:" << std::endl;
	runRegularExpressionGetRegExTests();
	return true;
}
bool Tests::runRegularExpressionGetRegExTests() {
	
	std::cout<< (RegularExpression("a(a+b)*b+b(a+b)*a").getRegEx() == "(a((a+b))*b+b((a+b))*a)") << std::endl;
	std::cout<< (RegularExpression("a").getRegEx() == "a") << std::endl;
	std::cout<< (RegularExpression("ab").getRegEx() == "ab") << std::endl;
	std::cout<< (RegularExpression("ab+ac").getRegEx() == "(ab+ac)") << std::endl;
	std::cout<< (RegularExpression("(ab+ac)*").getRegEx() == "((ab+ac))*") << std::endl;
	std::cout<< (RegularExpression("(ab+ac)*+a").getRegEx() == "(((ab+ac))*+a)") << std::endl;
	std::cout<< (RegularExpression("(ab+ac)*+a+b").getRegEx() == "(((ab+ac))*+(a+b))") << std::endl;
	std::cout<< (RegularExpression("(ab+ac)*+a+ba").getRegEx() == "(((ab+ac))*+(a+ba))") << std::endl;
	std::cout<< (RegularExpression("((ab+ac)*+a+ba)c").getRegEx() == "(((ab+ac))*+(a+ba))c") << std::endl;
	std::cout<< (RegularExpression("((ab+ac)*+a+ba)c+d").getRegEx() == "((((ab+ac))*+(a+ba))c+d)") << std::endl;
	std::cout<< (RegularExpression("((ab+ac)*+a+ba)c+d+b").getRegEx() == "((((ab+ac))*+(a+ba))c+(d+b))") << std::endl;
	std::cout<< (RegularExpression("((ab+ac)*+a+ba)c+d+(b)*").getRegEx() == "((((ab+ac))*+(a+ba))c+(d+(b)*))") << std::endl;
	std::cout<< (RegularExpression("(a)*").getRegEx() == "(a)*") << std::endl;
	std::cout<< (RegularExpression("(a)*+(b)*").getRegEx() == "((a)*+(b)*)") << std::endl;
	std::cout<< (RegularExpression("((a)*+(b)*)*").getRegEx() == "(((a)*+(b)*))*") << std::endl;
	std::cout<< (RegularExpression("((ab)*+(bb)*)*").getRegEx() == "(((ab)*+(bb)*))*") << std::endl;
	std::cout<< (RegularExpression("abcd").getRegEx() == "abcd") << std::endl;
	std::cout<< (RegularExpression("(a)*(b)*").getRegEx() == "(a)*(b)*") << std::endl;
	std::cout<< (RegularExpression("((a)*(b)*)*").getRegEx() == "((a)*(b)*)*") << std::endl;
	std::cout<< (RegularExpression("(((a)*(b)*)*)*").getRegEx() == "(((a)*(b)*)*)*") << std::endl;
	std::cout<< (RegularExpression("(((a)*(b)*)*)*+(((a)*(b)*)*)*").getRegEx() == "((((a)*(b)*)*)*+(((a)*(b)*)*)*)") << std::endl;
	std::cout<< (RegularExpression("((((a)*(b)*)*)*+(((a)*(b)*)*)*)c").getRegEx() == "((((a)*(b)*)*)*+(((a)*(b)*)*)*)c") << std::endl;
	std::cout<< (RegularExpression("(((a)*(b)*)*)*+(((a)*(b)*)*)*c").getRegEx() == "((((a)*(b)*)*)*+(((a)*(b)*)*)*c)") << std::endl;
	std::cout<< (RegularExpression("a((((a)*(b)*)*)*+(((a)*(b)*)*)*c)").getRegEx() == "a((((a)*(b)*)*)*+(((a)*(b)*)*)*c)") << std::endl;
	std::cout<< (RegularExpression("a((((a)*(b)*)*)*+(((a)*(b)*)*)*c)").getRegEx() == "a((((a)*(b)*)*)*+(((a)*(b)*)*)*c)") << std::endl;
	std::cout<< (RegularExpression("ab(a+c)*").getRegEx() == "ab((a+c))*") << std::endl;

	//MyString inputs[64] = { "a(a+b)*b+b(a+b)*a","a","ab","ab+ac","(ab+ac)*","(ab+ac)*+a","(ab+ac)*+a+b","(ab+ac)*+a+ba","((ab+ac)*+a+ba)c"
	//,"((ab+ac)*+a+ba)c+d","((ab+ac)*+a+ba)c+d+b","((ab+ac)*+a+ba)c+d+(b)*","(a)*","(a)*+(b)*","((a)*+(b)*)*","((ab)*+(bb)*)*","abcd","(a)*(b)*"
	//,"((a)*(b)*)*","(((a)*(b)*)*)*","(((a)*(b)*)*)*+(((a)*(b)*)*)*","((((a)*(b)*)*)*+(((a)*(b)*)*)*)c","(((a)*(b)*)*)*+(((a)*(b)*)*)*c","a((((a)*(b)*)*)*+(((a)*(b)*)*)*c)","ab(a+c)*" };

	//MyString outputs[64] = { "(a((a+b))*b+b((a+b))*a)" ,"a","ab", "(ab+ac)","((ab+ac))*","(((ab+ac))*+a)","(((ab+ac))*+(a+b))"
	//	,"(((ab+ac))*+(a+ba))","(((ab+ac))*+(a+ba))c","((((ab+ac))*+(a+ba))c+d)","((((ab+ac))*+(a+ba))c+(d+b))","((((ab+ac))*+(a+ba))c+(d+(b)*))"
	//,"(a)*","((a)*+(b)*)","(((a)*+(b)*))*","(((ab)*+(bb)*))*","abcd","(a)*(b)*","((a)*(b)*)*","(((a)*(b)*)*)*","((((a)*(b)*)*)*+(((a)*(b)*)*)*)"
	//	,"((((a)*(b)*)*)*+(((a)*(b)*)*)*)c","((((a)*(b)*)*)*+(((a)*(b)*)*)*c)","a((((a)*(b)*)*)*+(((a)*(b)*)*)*c)","ab((a+c))*" };

	//for (int i = 0; i < 23; i++)
	//{
	//	std::cout << (RegularExpression(inputs[i]).getRegEx() == outputs[i])<<std::endl;
	//}
	return true;
}
bool Tests::runAutomatonUnionTests() {
	//Arange
	RegularExpression firstRegEx("(a)*b(b)*");
	RegularExpression secondRegEx("(c)*d");
	FiniteAutomata firstAutomaton(firstRegEx);
	FiniteAutomata secondAutomaton(secondRegEx);
	//Act
	FiniteAutomata result = Union(firstAutomaton,secondAutomaton);
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
	RegularExpression firstRegEx("(a+b)*");
	RegularExpression secondRegEx("(c+d)*");
	FiniteAutomata firstAutomaton(firstRegEx);
	FiniteAutomata secondAutomaton(secondRegEx);
	//Act
	FiniteAutomata result = Concatenation(firstAutomaton,secondAutomaton);
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
	RegularExpression firstRegEx("a+b");
	FiniteAutomata firstAutomaton(firstRegEx);
	//Act
	FiniteAutomata result = KleeneStar(firstAutomaton);
	//Assert
	std::cout << result.accept("ab") << std::endl;
	std::cout << result.accept("ba") << std::endl;
	std::cout << result.accept("bababaabbaaabbba") << std::endl;
	std::cout << result.accept("abaaabbbbaaba") << std::endl;
	std::cout << result.accept("") << std::endl;
	return true;
}
bool Tests::runAutomatonTotalizationTests() {
	//Arange
	RegularExpression firstRegEx("(a+b)*cd");
	FiniteAutomata result(firstRegEx);
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
	RegularExpression firstRegEx("(a+b)*(c+d)*+ca");
	FiniteAutomata result(firstRegEx);
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
	RegularExpression firstRegEx("(a+b)*(c+d)+ca");
	FiniteAutomata result(firstRegEx); 
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
	RegularExpression firstRegEx("(a+b)*(c+d)*+ca");
	FiniteAutomata result(firstRegEx);
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
	std::cout << "RegEx tests:" << std::endl;
	runRegularExpressionTests();
	std::cout << "Automaton tests:" << std::endl;
	runAutomatonTests();
	return true;
}