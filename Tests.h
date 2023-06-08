#pragma once
#include "AutomatonTests.h"
#include "RegExTests.h"
#include "CollectionsTests.h"

class Tests {
public:
	static bool runAllTests();

};

bool Tests::runAllTests() {
	AutomatonTests::runAutomatonTests();
	RegExTests::runRegularExpressionTests();
	CollectionsTests::runCollectionsTests();
	return true;
}
