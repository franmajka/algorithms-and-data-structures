#pragma once

#include "Heap.h"

template <class T, class Comparator = std::less<T>>
class PriorityQueue
{
public:
	void push(const T& el);
	T top();
	T pop();
	
	int size();
	bool empty();
private:
	Heap<T, Comparator> heap;
};

template<class T, class Comparator>
void PriorityQueue<T, Comparator>::push(const T& el)
{
	heap.append(el);
}

template<class T, class Comparator>
T PriorityQueue<T, Comparator>::top()
{
	return heap.getTop();
}

template<class T, class Comparator>
T PriorityQueue<T, Comparator>::pop()
{
	return heap.popTop();
}

template<class T, class Comparator>
int PriorityQueue<T, Comparator>::size()
{
	return heap.size();
}

template<class T, class Comparator>
bool PriorityQueue<T, Comparator>::empty()
{
	return !heap.size();
}
