#pragma once
template<typename T>
class SharedPointer {
	int* referencesCount = nullptr;
	T* ptr = nullptr;
	void moveFrom(SharedPointer&& other);
	void copyFrom(const SharedPointer& other);
	void free();
public:
	~SharedPointer();
	SharedPointer() = default;
	SharedPointer(T* pointer);
	SharedPointer(const SharedPointer& other);
	SharedPointer(SharedPointer&& other);
	SharedPointer<T> operator=(const SharedPointer& other);
	SharedPointer<T> operator=(SharedPointer&& other);

	const T& operator*()const;
	T& operator*();
};
template<typename T>
void SharedPointer<T>::moveFrom(SharedPointer&& other) {
	referencesCount = other.referencesCount;
	other.referencesCount = nullptr;
	ptr = other.ptr;
	other.ptr = nullptr;
}
template<typename T>
void SharedPointer<T>::copyFrom(const SharedPointer& other) {
	ptr = other.ptr;
	referencesCount = other.referencesCount;
	(*referencesCount)++;
}
template<typename T>
void SharedPointer<T>::free() {
	if (!(referencesCount == nullptr && ptr == nullptr))
	{
		if ((*referencesCount) == 1)
		{
			delete referencesCount;
			delete ptr;
		}
		else
		{
			(*referencesCount)--;
		}
	}
}
template<typename T>
SharedPointer<T>::~SharedPointer() {
	free();
}
template<typename T>
SharedPointer<T>::SharedPointer(T* pointer) {
	ptr = pointer;
	referencesCount = new int(1);
}
template<typename T>
SharedPointer<T>::SharedPointer(const SharedPointer& other) {
	copyFrom(other);
}
template<typename T>
SharedPointer<T>::SharedPointer(SharedPointer&& other) {
	moveFrom(std::move(other));
}
template<typename T>
SharedPointer<T> SharedPointer<T>::operator=(const SharedPointer& other) {
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}
template<typename T>
SharedPointer<T> SharedPointer<T>::operator=(SharedPointer&& other) {
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}
	return *this;

}
template<typename T>
const T& SharedPointer<T>::operator*()const {
	return *ptr;
}
template<typename T>
T& SharedPointer<T>::operator*() {
	return *ptr;
}