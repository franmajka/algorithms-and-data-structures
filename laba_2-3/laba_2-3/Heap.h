#pragma once

#pragma warning(disable : 6386)

#include <iostream>
#include <functional>

template <class T, class Comparator = std::less<T>>
class Heap
{
public:
	using value_type = T;

	Heap();
	Heap(const std::initializer_list<T>& elems);
	template <class Iterator>
	Heap(const Iterator& begin, const Iterator& end);
	~Heap();

	void append(const T& el);
	T popTop();
	T getTop();

	int size();
	void print();

private:
	void resize();

	int validIdx(int idx) const;

	int getParentIdx(int idx) const;
	int getLeftIdx(int idx) const;
	int getRightIdx(int idx) const;

	void siftUp(int idx);
	void siftDown(int idx);

	T* m_arr;
	int m_size;
	int m_capacity;
};

template <class T, class Comparator>
Heap<T, Comparator>::Heap()
{
	m_size = 0;
	m_capacity = 1;
	m_arr = new T[m_capacity];
}

template <class T, class Comparator>
Heap<T, Comparator>::Heap(const std::initializer_list<T>& elems)
{
	m_size = 0;
	m_capacity = 1;
	m_arr = new T[m_capacity];

	for (const T& el : elems) {
		append(el);
	}
}

template <class T, class Comparator>
Heap<T, Comparator>::~Heap()
{
	delete[] m_arr;
}

template <class T, class Comparator>
void Heap<T, Comparator>::append(const T& el)
{
	int idx = m_size++;
	m_arr[idx] = el;
	siftUp(idx);

	if (m_size >= m_capacity) resize();
}

template <class T, class Comparator>
T Heap<T, Comparator>::popTop()
{
	if (!m_size) throw "Heap is empty";

	std::swap(m_arr[0], m_arr[--m_size]);
	siftDown(0);

	return m_arr[m_size];
}

template <class T, class Comparator>
T Heap<T, Comparator>::getTop()
{
	return m_arr[0];
}

template <class T, class Comparator>
int Heap<T, Comparator>::size()
{
	return m_size;
}

template <class T, class Comparator>
void Heap<T, Comparator>::print()
{
	for (int i = 0; i < m_size; i++) {
		std::cout << m_arr[i] << " ";
	}
	std::cout << std::endl;
}

template <class T, class Comparator>
void Heap<T, Comparator>::resize()
{
	T* copy = m_arr;
	
	m_capacity = 2 * m_capacity + 1;
	m_arr = new T[m_capacity];

	for (int i = 0; i < m_size; i++) {
		m_arr[i] = copy[i];
	}

	delete[] copy;
}

template <class T, class Comparator>
int Heap<T, Comparator>::validIdx(int idx) const
{
	return m_size <= idx || idx < 0 ? -1 : idx;
}

template <class T, class Comparator>
int Heap<T, Comparator>::getParentIdx(int idx) const
{
	int parentIdx = (idx - 1) / 2;
	return validIdx(parentIdx);
}

template <class T, class Comparator>
int Heap<T, Comparator>::getLeftIdx(int idx) const
{
	int leftIdx = idx * 2 + 1;
	return validIdx(leftIdx);
}

template <class T, class Comparator>
int Heap<T, Comparator>::getRightIdx(int idx) const
{
	int rightIdx = idx * 2 + 2;
	return validIdx(rightIdx);
}

template <class T, class Comparator>
void Heap<T, Comparator>::siftUp(int idx)
{
	idx = validIdx(idx);
	int parentIdx = getParentIdx(idx);

	while (~parentIdx && !Comparator{}(m_arr[idx], m_arr[parentIdx])) {
		std::swap(m_arr[idx], m_arr[parentIdx]);
		idx = parentIdx;
		parentIdx = getParentIdx(idx);
	}
}

template <class T, class Comparator>
void Heap<T, Comparator>::siftDown(int idx)
{
	if (!~validIdx(idx)) return;
	int leftIdx = getLeftIdx(idx);
	int rightIdx = getRightIdx(idx);
	int biggerIdx;

	while ((~leftIdx && Comparator{}(m_arr[idx], m_arr[leftIdx])) || (~rightIdx && Comparator{}(m_arr[idx], m_arr[rightIdx]))) {
		if (~leftIdx && ~rightIdx) {
			if (Comparator{}(m_arr[leftIdx], m_arr[rightIdx])) {
				biggerIdx = rightIdx;
			}
			else {
				biggerIdx = leftIdx;
			}
		}
		else if (~leftIdx) {
			biggerIdx = leftIdx;
		}
		else {
			biggerIdx = rightIdx;
		}

		std::swap(m_arr[idx], m_arr[biggerIdx]);
		idx = biggerIdx;
		leftIdx = getLeftIdx(idx);
		rightIdx = getRightIdx(idx);
	}
}

template<class T, class Comparator>
template <class Iterator>
Heap<T, Comparator>::Heap(const Iterator& begin, const Iterator& end)
{
	m_size = end - begin;
	m_capacity = m_size + 1;
	m_arr = new T[m_capacity];

	int i = 0;
	for (Iterator it = begin; it != end; ++it, ++i) {
		m_arr[i] = *it;
	}

	for (i = m_size / 2 - 1; i >= 0; --i) {
		siftDown(i);
	}
}
