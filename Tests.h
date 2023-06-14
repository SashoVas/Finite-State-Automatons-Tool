#pragma once
#include "AutomatonTests.h"
#include "RegExTests.h"
#include "CollectionsTests.h"

class Tests {
public:
	static bool runAllTests();

};

bool Tests::runAllTests() {
	bool automatonTests = AutomatonTests::runAutomatonTests();
	bool regExTests = RegExTests::runRegularExpressionTests();
	bool collectionTests = CollectionsTests::runCollectionsTests();
	return automatonTests && regExTests && collectionTests;
}
