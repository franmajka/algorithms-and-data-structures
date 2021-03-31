#pragma once

#include "Heap.h"

template <class T>
class PriorityQueue
{
public:
	void push(const T& el);
	T top();
	T pop();
	
	int size();
	bool empty();
private:
	Heap<T> heap;
};

template<class T>
void PriorityQueue<T>::push(const T& el)
{
	heap.append(el);
}

template<class T>
T PriorityQueue<T>::top()
{
	return heap.getTop();
}

template<class T>
T PriorityQueue<T>::pop()
{
	return heap.popTop();
}

template<class T>
int PriorityQueue<T>::size()
{
	return heap.size();
}

template<class T>
bool PriorityQueue<T>::empty()
{
	return !heap.size();
}
