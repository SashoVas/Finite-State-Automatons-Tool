#pragma once
#include "RegExHandler.h"
#include "MyString.h"
class RegExTests {
private:
	static bool assertRegExToStringEquals(const RegExHandler& regEx,const MyString& value);
public:
	static bool runRegularExpressionTests();
	static bool runRegularExpressionGetRegExTests();
};
