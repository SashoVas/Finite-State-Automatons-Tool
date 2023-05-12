#pragma once
#include "RegularExpression.h"
class Tests {
public:
	static bool runRegularExpressionTests();
	static bool runRegularExpressionGetRegExTests();
};

bool Tests::runRegularExpressionTests() {
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