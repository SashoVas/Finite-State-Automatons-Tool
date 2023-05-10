#pragma once
template <class T>
class CustomCollection {
	int size = 0;
	int capacity = 0;
	T* elements=nullptr;

	void copyFrom(const CustomCollection& other);
	void free();
	void moveFrom(CustomCollection&& other);

	void resize(int capacity);
public:
	CustomCollection();
	CustomCollection(const CustomCollection& other);
	CustomCollection(int capacity);
	~CustomCollection();

	CustomCollection<T>& operator=(const CustomCollection& other);

	CustomCollection(CustomCollection&& other);
	CustomCollection<T>& operator=(CustomCollection&& other);

	T& operator[](size_t index);
	const T& operator[](size_t index) const;
	bool operator==(const CustomCollection& other)const;

	int getSize()const;
	int find(const T& other)const;

	void add(const T& element);
	void remove();
	void empty();
};

template <class T>
void CustomCollection<T>::copyFrom(const CustomCollection& other) {
	T* newData = new T[other.capacity];
	for (int i = 0; i < other.size; i++)
	{
		newData[i] = other.elements[i];
	}
	size = other.size;
	capacity = other.capacity;
	delete[] elements;
	elements = newData;
}

template <class T>
void CustomCollection<T>::free() {
	delete[] elements;
	elements = nullptr;
	size = 0;
	capacity = 0;
}

template <class T>
void CustomCollection<T>::moveFrom(CustomCollection&& other) {
	size = other.size;
	capacity = other.capacity;
	elements = other.elements;
	other.elements = nullptr;
}

template <class T>
CustomCollection<T>::CustomCollection(const CustomCollection& other) {
	copyFrom(other);
}

template <class T>
CustomCollection<T>::CustomCollection(int capacity) {
	elements = new T[capacity];
	this->capacity = capacity;
	size = 0;
}

template <class T>
CustomCollection<T>::CustomCollection():CustomCollection(8) {
}

template <class T>
CustomCollection<T>::~CustomCollection() {
	free();
}

template <class T>
CustomCollection<T>& CustomCollection<T>::operator=(const CustomCollection& other) {
	if (this!= &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

template <class T>
CustomCollection<T>::CustomCollection(CustomCollection&& other) {
	moveFrom(std::move(other));
}

template <class T>
CustomCollection<T>& CustomCollection<T>::operator=(CustomCollection&& other){
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}
	return *this;
}

template <class T>
T& CustomCollection<T>::operator[](size_t index) {
	return elements[index];
}

template <class T>
const T& CustomCollection<T>::operator[](size_t index) const {
	return elements[index];
}

template <class T>
void CustomCollection<T>::resize(int capacity) {
	T* newData = new T[capacity];

	for (int i = 0; i < size; i++)
	{
		newData[i] = elements[i];
	}
	delete[] elements;
	elements = newData;
	this->capacity = capacity;
}

template <class T>
void CustomCollection<T>::add(const T& element) {
	if (size>=capacity)
	{
		resize(capacity*2);
	}
	elements[size++] = element;
}

template <class T>
void CustomCollection<T>::remove() {
	size--;
	if (size*4<capacity)
	{
		resize(capacity/2);
	}
}

template <class T>
void CustomCollection<T>::empty() {
	size = 0;
	resize(8);
}

template <class T>
int CustomCollection<T>::getSize()const {
	return size;
}

template <class T>
int CustomCollection<T>::find(const T& other)const {
	for (int i = 0; i < size; i++)
	{
		if (elements[i] == other)
			return i;
	}
	return -1;
}

template <class T>
bool CustomCollection<T>::operator==(const CustomCollection& other)const {
	if (size!=other.getSize())
	{
		return false;
	}
	for (int i = 0; i < size; i++)
	{
		if (other.find(elements[i])==-1)
		{
			return false;
		}
	}
	for (int i = 0; i < other.getSize(); i++)
	{
		if (find(other[i])==-1)
		{
			return false;
		}
	}
	return true;
}
