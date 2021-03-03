#pragma once

#include <iostream>

#define ALPHA 2

template <class T>
class DynamicArray {

private:
    T* m_array;
    size_t m_capacity;
    size_t m_length;

public:
    DynamicArray() : m_length(0), m_capacity(1), m_array(new T[1]) {}
    ~DynamicArray();

    T& operator[] (int);

    void push(T);
    T pop();

    void unshift(T);
    T shift();

    size_t getLength();
    T getElem(size_t);

    void print();
};

template <class T>
DynamicArray<T>::~DynamicArray() {
    delete[] m_array;
}


template <class T>
T& DynamicArray<T>::operator[] (int idx) {
    if (m_length <= (idx >= 0 ? idx : -(idx + 1))) throw "Index out of range of array";

    return idx >= 0 ? m_array[idx] : m_array[m_length + idx];
}


template <class T>
void DynamicArray<T>::push(T el) {
    if (m_capacity <= m_length) {
        T* tmp = new T[m_capacity *= ALPHA];

        for (size_t i = 0; i < m_length; i++) {
            tmp[i] = m_array[i];
        }

        delete[] m_array;

        m_array = tmp;
    }

    m_array[m_length++] = el;
}

template <class T>
T DynamicArray<T>::pop() {
    if (!m_length) throw "Array is empty";
    return m_array[--m_length];
}


template <class T>
void DynamicArray<T>::unshift(T el) {
    if (m_capacity <= m_length) {
        T* tmp = new T[m_capacity *= ALPHA];

        for (size_t i = 1; i <= m_length; i++) {
            tmp[i] = m_array[i - 1];
        }

        delete[] m_array;

        m_array = tmp;
    }
    else {
        for (size_t i = m_length; i; ) {
            m_array[i] = m_array[--i];
        }
    }

    m_array[0] = el;
    m_length++;
}

template <class T>
T DynamicArray<T>::shift() {
    if (!m_length) throw "Array is empty";

    T tmp = m_array[0];

    for (size_t i = 0; i < m_length;) {
        m_array[i] = m_array[++i];
    }

    m_length--;

    return tmp;
}


template <class T>
size_t DynamicArray<T>::getLength() {
    return m_length;
}

template <class T>
T DynamicArray<T>::getElem(size_t idx) {
    return m_array[idx];
}

template <class T>
void DynamicArray<T>::print() {
    if (!m_length) {
        std::cout << "Динамический массив пуст" << std::endl;
        return;
    }

    for (size_t i = 0; i < m_length; i++) {
        std::cout << i + 1 << ") " << m_array[i] << std::endl;
    }
}