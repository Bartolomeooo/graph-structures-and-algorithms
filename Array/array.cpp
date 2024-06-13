#include <random>
#include <algorithm>
#include "array.h"

// Constructor
template <typename T>
array<T>::array(int size) {
    data_ = new T[size];
    size_ = size;
}

// Copying constructor
template <typename T>
array<T>::array(const array& other) {
    data_ = new T[other.size_];
    size_ = other.size_;
    for (int i = 0; i < size_; i++) {
        data_[i] = other.data_[i];
    }
}

// Assignment operator
template <typename T>
array<T>& array<T>::operator=(const array& other) {
    if (this == &other) {
        return *this; // Handle self-assignment
    }

    // Allocate new data before deleting old data
    T* newData = new T[other.size_];
    for (int i = 0; i < other.size_; i++) {
        newData[i] = other.data_[i];
    }

    // Delete the old data and assign new data
    data_ = newData;
    size_ = other.size_;

    return *this;
}

// Method of access
template <typename T>
T& array<T>::operator[](int index) const {
    return data_[index];
}

// Method of access
template <typename T>
T& array<T>::operator[](int index) {
    return data_[index];
}

// Push back an element to the last position
template <typename T>
void array<T>::PushBack(const T& value) {
    T* newData = new T[size_ + 1];
    for (int i = 0; i < size_; i++) {
        newData[i] = data_[i];
    }
    newData[size_] = value;
    delete[] data_;
    data_ = newData;
    size_++;
}

// Pop back the last element
template <typename T>
void array<T>::PopBack() {
    if (size_ > 0) {
        size_--;
        T* newData = new T[size_];
        for (int i = 0; i < size_; i++) {
            newData[i] = data_[i];
        }
        delete[] data_;
        data_ = newData;
    }
}

// Return the size of the array
template <typename T>
int array<T>::size() const {
    return size_;
}

// Check if the array is empty
template <typename T>
bool array<T>::IsEmpty() const {
    return size_ == 0;
}

// Resize the array
template <typename T>
void array<T>::resize(int newSize) {
    if (newSize < 0) {
        std::cerr << "Error: New size cannot be negative." << std::endl;
        return;
    }
    delete[] data_;
    data_ = new T[newSize];
    size_ = newSize;
}