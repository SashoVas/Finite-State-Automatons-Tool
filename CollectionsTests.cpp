#include "CollectionsTests.h"
#include "BitSet.h"

bool CollectionsTests::runCollectionsTests() {
	std::cout << "BitSet tests:" << std::endl;
	std::cout << "BitSet toggle and check Tests:" << std::endl;
	bool checkTests = runBitSetCheckAndToggleTests();
	std::cout << "BitSet add and resize Tests:" << std::endl;
	bool resizeTests = runBitSetAddAndResizeTests();
	return checkTests && resizeTests;
}
bool CollectionsTests::runBitSetCheckAndToggleTests()
{
	//Arange
	BitSet bitSet(64);
	//Act
	for (int i = 0; i < 64; i += 2)
	{
		bitSet.toggle(i);
	}
	//Assert
	for (int i = 0; i < 64; i++)
	{
		if (i % 2 == bitSet.check(i))
		{
			std::cout << 0 << std::endl;
			return false;
		}
	}
	std::cout << 1 << std::endl;
	return true;
}
bool CollectionsTests::runBitSetAddAndResizeTests() {
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
		if (bitSet.check(i) != i % 2)
		{
			std::cout << 0 << std::endl;
			return false;
		}
	}
	std::cout << 1 << std::endl;
	return true;
}