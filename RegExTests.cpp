#include <iostream>
#include "RegExTests.h"

bool RegExTests::assertRegExToStringEquals(const RegExHandler& regEx, const MyString& value) {
	bool result = regEx.getString() == value;
	std::cout << result << std::endl;
	return result;
}

bool RegExTests::runRegularExpressionTests() {
	std::cout << "RegEx parse tests:" << std::endl;
	return runRegularExpressionGetRegExTests();
}
bool RegExTests::runRegularExpressionGetRegExTests() {
	bool isValid = true;
	isValid = isValid && assertRegExToStringEquals(RegExHandler("a(a+b)*b+b(a+b)*a"), "(a((a+b))*b+b((a+b))*a)");
	isValid = isValid && assertRegExToStringEquals(RegExHandler("a"), "a");
	isValid = isValid && assertRegExToStringEquals(RegExHandler("ab"), "ab");
	isValid = isValid && assertRegExToStringEquals(RegExHandler("ab+ac"), "(ab+ac)");
	isValid = isValid && assertRegExToStringEquals(RegExHandler("(ab+ac)*"), "((ab+ac))*");
	isValid = isValid && assertRegExToStringEquals(RegExHandler("(ab+ac)*+a"), "(((ab+ac))*+a)");
	isValid = isValid && assertRegExToStringEquals(RegExHandler("(ab+ac)*+a+b"), "(((ab+ac))*+(a+b))");
	isValid = isValid && assertRegExToStringEquals(RegExHandler("(ab+ac)*+a+ba"), "(((ab+ac))*+(a+ba))");
	isValid = isValid && assertRegExToStringEquals(RegExHandler("((ab+ac)*+a+ba)c"), "(((ab+ac))*+(a+ba))c");
	isValid = isValid && assertRegExToStringEquals(RegExHandler("((ab+ac)*+a+ba)c+d"), "((((ab+ac))*+(a+ba))c+d)");
	isValid = isValid && assertRegExToStringEquals(RegExHandler("((ab+ac)*+a+ba)c+d+b"), "((((ab+ac))*+(a+ba))c+(d+b))");
	isValid = isValid && assertRegExToStringEquals(RegExHandler("((ab+ac)*+a+ba)c+d+(b)*"), "((((ab+ac))*+(a+ba))c+(d+(b)*))");
	isValid = isValid && assertRegExToStringEquals(RegExHandler("(a)*"), "(a)*");
	isValid = isValid && assertRegExToStringEquals(RegExHandler("(a)*+(b)*"), "((a)*+(b)*)");
	isValid = isValid && assertRegExToStringEquals(RegExHandler("((a)*+(b)*)*"), "(((a)*+(b)*))*");
	isValid = isValid && assertRegExToStringEquals(RegExHandler("((ab)*+(bb)*)*"), "(((ab)*+(bb)*))*");
	isValid = isValid && assertRegExToStringEquals(RegExHandler("abcd"), "abcd");
	isValid = isValid && assertRegExToStringEquals(RegExHandler("(a)*(b)*"), "(a)*(b)*");
	isValid = isValid && assertRegExToStringEquals(RegExHandler("((a)*(b)*)*"), "((a)*(b)*)*");
	isValid = isValid && assertRegExToStringEquals(RegExHandler("(((a)*(b)*)*)*"), "(((a)*(b)*)*)*");
	isValid = isValid && assertRegExToStringEquals(RegExHandler("(((a)*(b)*)*)*+(((a)*(b)*)*)*"), "((((a)*(b)*)*)*+(((a)*(b)*)*)*)");
	isValid = isValid && assertRegExToStringEquals(RegExHandler("((((a)*(b)*)*)*+(((a)*(b)*)*)*)c"), "((((a)*(b)*)*)*+(((a)*(b)*)*)*)c");
	isValid = isValid && assertRegExToStringEquals(RegExHandler("(((a)*(b)*)*)*+(((a)*(b)*)*)*c"), "((((a)*(b)*)*)*+(((a)*(b)*)*)*c)");
	isValid = isValid && assertRegExToStringEquals(RegExHandler("a((((a)*(b)*)*)*+(((a)*(b)*)*)*c)"), "a((((a)*(b)*)*)*+(((a)*(b)*)*)*c)");
	isValid = isValid && assertRegExToStringEquals(RegExHandler("a((((a)*(b)*)*)*+(((a)*(b)*)*)*c)"), "a((((a)*(b)*)*)*+(((a)*(b)*)*)*c)");
	isValid = isValid && assertRegExToStringEquals(RegExHandler("ab(a+c)*"), "ab((a+c))*");

	return isValid;
}