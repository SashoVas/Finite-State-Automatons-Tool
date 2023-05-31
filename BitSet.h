#pragma once
#include <iostream>
class BitSet {
	int size = 0;
	int capacity = 0;
	int truesCount = 0;
	char* data=nullptr;
	void copyFrom(const BitSet& other);
	void moveFrom(BitSet&& other);
	void free();
	int getBucketsCount()const;
	int getBucketIndex(int index)const;
	int getBucketPositionMask(int index)const;
	void resize(int newCapacity);
public:
	BitSet();
	BitSet(int size);
	~BitSet();
	BitSet(const BitSet& other);
	BitSet& operator=(const BitSet& other);
	BitSet(BitSet&& other);
	BitSet& operator=(BitSet&& other);

	void toggle(int index);
	void add(bool mode=false);
	bool check(int index)const;
	void empty();

	int getTruesCount()const;
};