#include "Tests.h"

bool Tests::runAllTests() {
	bool automatonTests = AutomatonTests::runAutomatonTests();
	bool regExTests = RegExTests::runRegularExpressionTests();
	bool collectionTests = CollectionsTests::runCollectionsTests();
	return automatonTests && regExTests && collectionTests;
}
