#include <iostream>
#include "RegExTests.h"
#include "RegExHandler.h"
bool RegExTests::runRegularExpressionTests() {
	std::cout << "RegEx parse tests:" << std::endl;
	runRegularExpressionGetRegExTests();
	return true;
}
bool RegExTests::runRegularExpressionGetRegExTests() {

	std::cout << ((RegExHandler("a(a+b)*b+b(a+b)*a")).getString() == "(a((a+b))*b+b((a+b))*a)") << std::endl;
	std::cout << ((RegExHandler("a")).getString() == "a") << std::endl;
	std::cout << ((RegExHandler("ab")).getString() == "ab") << std::endl;
	std::cout << ((RegExHandler("ab+ac")).getString() == "(ab+ac)") << std::endl;
	std::cout << ((RegExHandler("(ab+ac)*")).getString() == "((ab+ac))*") << std::endl;
	std::cout << ((RegExHandler("(ab+ac)*+a")).getString() == "(((ab+ac))*+a)") << std::endl;
	std::cout << ((RegExHandler("(ab+ac)*+a+b")).getString() == "(((ab+ac))*+(a+b))") << std::endl;
	std::cout << ((RegExHandler("(ab+ac)*+a+ba")).getString() == "(((ab+ac))*+(a+ba))") << std::endl;
	std::cout << ((RegExHandler("((ab+ac)*+a+ba)c")).getString() == "(((ab+ac))*+(a+ba))c") << std::endl;
	std::cout << ((RegExHandler("((ab+ac)*+a+ba)c+d")).getString() == "((((ab+ac))*+(a+ba))c+d)") << std::endl;
	std::cout << ((RegExHandler("((ab+ac)*+a+ba)c+d+b")).getString() == "((((ab+ac))*+(a+ba))c+(d+b))") << std::endl;
	std::cout << ((RegExHandler("((ab+ac)*+a+ba)c+d+(b)*")).getString() == "((((ab+ac))*+(a+ba))c+(d+(b)*))") << std::endl;
	std::cout << ((RegExHandler("(a)*")).getString() == "(a)*") << std::endl;
	std::cout << ((RegExHandler("(a)*+(b)*")).getString() == "((a)*+(b)*)") << std::endl;
	std::cout << ((RegExHandler("((a)*+(b)*)*")).getString() == "(((a)*+(b)*))*") << std::endl;
	std::cout << ((RegExHandler("((ab)*+(bb)*)*")).getString() == "(((ab)*+(bb)*))*") << std::endl;
	std::cout << ((RegExHandler("abcd")).getString() == "abcd") << std::endl;
	std::cout << ((RegExHandler("(a)*(b)*")).getString() == "(a)*(b)*") << std::endl;
	std::cout << ((RegExHandler("((a)*(b)*)*")).getString() == "((a)*(b)*)*") << std::endl;
	std::cout << ((RegExHandler("(((a)*(b)*)*)*")).getString() == "(((a)*(b)*)*)*") << std::endl;
	std::cout << ((RegExHandler("(((a)*(b)*)*)*+(((a)*(b)*)*)*")).getString() == "((((a)*(b)*)*)*+(((a)*(b)*)*)*)") << std::endl;
	std::cout << ((RegExHandler("((((a)*(b)*)*)*+(((a)*(b)*)*)*)c")).getString() == "((((a)*(b)*)*)*+(((a)*(b)*)*)*)c") << std::endl;
	std::cout << ((RegExHandler("(((a)*(b)*)*)*+(((a)*(b)*)*)*c")).getString() == "((((a)*(b)*)*)*+(((a)*(b)*)*)*c)") << std::endl;
	std::cout << ((RegExHandler("a((((a)*(b)*)*)*+(((a)*(b)*)*)*c)")).getString() == "a((((a)*(b)*)*)*+(((a)*(b)*)*)*c)") << std::endl;
	std::cout << ((RegExHandler("a((((a)*(b)*)*)*+(((a)*(b)*)*)*c)")).getString() == "a((((a)*(b)*)*)*+(((a)*(b)*)*)*c)") << std::endl;
	std::cout << ((RegExHandler("ab(a+c)*")).getString() == "ab((a+c))*") << std::endl;

	return true;
}