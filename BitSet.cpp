#include "BitSet.h"

int BitSet::getTruesCount()const {
	return truesCount;
}
int BitSet::getSize()const {
	return size;
}
const char* BitSet::getRaw()const {
	return data;
}

int BitSet::getBucketsCount()const {
	return (capacity+1) / 8 +1;
}
int BitSet::getBucketIndex(int index)const {
	return index / 8;
}
int BitSet::getBucketPositionMask(int index)const {
	int position = index % 8;
	return 1 << (7 - position);
}
void BitSet::copyFrom(const BitSet& other) {
	capacity = other.capacity;
	size = other.size;
	data = new char[other.getBucketsCount()]{ 0 };
	truesCount = other.truesCount;
	for (int i = 0; i < getBucketsCount(); i++)
	{
		data[i] = other.data[i];
	}
}
void BitSet::moveFrom(BitSet&& other) {
	capacity = other.capacity;
	size = other.size;
	data = other.data;
	other.data = nullptr;
	truesCount = other.truesCount;
}
void BitSet::free() {
	delete[] data;
	data = nullptr;
	size = 0;
	capacity = 0;
	truesCount = 0;
}
BitSet::BitSet() :BitSet(8) {

}
BitSet::BitSet(int size) {
	capacity = size * 2;
	this->size = size;
	data = new char[getBucketsCount()]{ 0 };
	truesCount = 0;
}
BitSet::~BitSet() {
	free();
}
BitSet::BitSet(const BitSet& other) {
	copyFrom(other);
}
BitSet& BitSet::operator=(const BitSet& other) {
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}
BitSet::BitSet(BitSet&& other) {
	moveFrom(std::move(other));
}
BitSet& BitSet::operator=(BitSet&& other) {
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}
	return *this;
}
void BitSet::resize(int newCapacity) {
	int oldBucketsCount = getBucketsCount();
	capacity = newCapacity;

	char* newData = new char[getBucketsCount()]{ 0 };

	for (int i = 0; i < oldBucketsCount; i++)
	{
		newData[i] = data[i];
	}
	delete[] data;
	data = newData;
}
void BitSet::toggle(int index) {
	if (index>=size)
	{
		throw std::invalid_argument("Invalid index!");
	}
	int bucketIndex = getBucketIndex(index);
	if (bucketIndex >= getBucketsCount())
	{
		throw std::invalid_argument("Invalid argument");
	}
	int positionMask = getBucketPositionMask(index);
	if (!(data[bucketIndex]& positionMask))
	{
		truesCount++;
	}
	else
	{
		truesCount--;
	}
	data[bucketIndex] ^= positionMask;
}
void BitSet::add(bool mode) {
	if (size >= capacity)
	{
		resize(capacity * 2);
	}
	size++;
	if (check(size - 1) != mode)
	{
		toggle(size - 1);
	}
}
bool BitSet::check(int index)const {
	int bucketIndex = getBucketIndex(index);
	int positionMask = getBucketPositionMask(index);
	return positionMask & data[bucketIndex];
}
void BitSet::empty() {
	for (int i = 0; i < getBucketsCount(); i++)
	{
		data[i] = 0;
	}
	truesCount = 0;
}