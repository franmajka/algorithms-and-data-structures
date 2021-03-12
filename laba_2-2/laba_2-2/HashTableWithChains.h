#pragma once

#include "HashTableBase.h"

#include "LinkedList.h"

#define ALPHA 2

template <class K, class V>
class HashTableWithChains : public HashTableBase<K, V>
{
	using HashNode = typename HashTableBase<K, V>::HashNode;
public:

	HashTableWithChains();
	HashTableWithChains(const HashTableWithChains&);
	~HashTableWithChains();

	V* find(const K& key);

	void insert(const K& key, const V& value);
	void erase(const K& key);

	void clear();

	V& operator[] (const K& key);
	template <class T>
	V& operator[] (const T& key);

	const V& operator[] (const K& key) const;
	template <class T>
	const V& operator[] (const T& key) const;

	HashTableWithChains<K, V>& operator= (const HashTableWithChains<K, V>&);
	const HashTableWithChains<K, V>& operator= (const HashTableWithChains<K, V>&) const;
private:
	
	void rehash(bool isLoaded);

	LinkedList<HashNode> *m_bucketsArray;
};


template <class K, class V>
HashTableWithChains<K, V>::HashTableWithChains() {
	m_bucketsArray = new LinkedList<HashNode>[HashTableBase<K, V>::m_capacity];
}

template <class K, class V>
HashTableWithChains<K, V>::HashTableWithChains(const HashTableWithChains& other) {
	m_bucketsArray = new LinkedList<HashNode>[HashTableBase<K, V>::m_capacity];

	for (size_t i = 0; i < other.m_capacity; i++) {
		for (HashTableWithChains<K, V>::HashNode& hashNode : other.m_bucketsArray[i]) {
			insert(hashNode.key, hashNode.value);
		}
	}
}

template <class K, class V>
HashTableWithChains<K, V>::~HashTableWithChains() {
	delete[] m_bucketsArray;
}


template <class K, class V>
void HashTableWithChains<K, V>::rehash(bool isLoaded) {
	LinkedList<HashNode>* originalBucketsArray = m_bucketsArray;
	size_t originalCapacity = HashTableBase<K, V>::m_capacity;

	HashTableBase<K, V>::m_size = 0;
	HashTableBase<K, V>::m_capacity = isLoaded ? 
		HashTableBase<K, V>::m_capacity * ALPHA : 
		HashTableBase<K, V>::m_capacity / ALPHA;
	m_bucketsArray = new LinkedList<HashNode>[HashTableBase<K, V>::m_capacity];

	for (size_t i = 0; i < originalCapacity; i++) {
		for (HashNode& hashNode : originalBucketsArray[i]) {
			insert(hashNode.key, hashNode.value);
		}
	}

	delete[] originalBucketsArray;
}


template <class K, class V>
V* HashTableWithChains<K, V>::find(const K& key) {
	size_t idx = HashTableBase<K,V>::hash(key);
	for (HashNode& hashNode : m_bucketsArray[idx]) {
		if (hashNode.key == key) return &hashNode.value;
	}

	return NULL;
}

template <class K, class V>
V& HashTableWithChains<K, V>::operator[] (const K& key) {
	V* ptr = find(key);

	if (ptr != NULL) return *ptr;

	size_t idx = HashTableBase<K, V>::hash(key);

	m_bucketsArray[idx].pushBack(HashNode(key));
	HashTableBase<K, V>::m_size++;
	return m_bucketsArray[idx][-1].value;
}

template <class K, class V> template <class T>
V& HashTableWithChains<K, V>::operator[] (const T& key) {
	return (*this)[K(key)];
}

template <class K, class V>
const V& HashTableWithChains<K, V>::operator[] (const K& key) const {
	V* ptr = find(key);

	if (ptr != NULL) return *ptr;

	throw "There is no such key in the hash table";
}

template <class K, class V> template <class T> 
const V& HashTableWithChains<K, V>::operator[] (const T& key) const {
	return (*this)[K(key)];
}


template <class K, class V>
HashTableWithChains<K, V>& HashTableWithChains<K, V>::operator= (const HashTableWithChains<K, V>& other) {
	clear();

	for (size_t i = 0; i < other.m_capacity; i++) {
		for (HashTableWithChains<K, V>::HashNode& hashNode : other.m_bucketsArray[i]) {
			insert(hashNode.key, hashNode.value);
		}
	}

	return *this;
}

template <class K, class V>
const HashTableWithChains<K, V>& HashTableWithChains<K, V>::operator= (const HashTableWithChains<K, V>&) const {
	throw "You're trying to change const variable";
}


template <class K, class V>
void HashTableWithChains<K, V>::insert(const K& key, const V& value) {
	V* inTableValue = find(key);
	if (inTableValue != NULL) {
		*inTableValue = value;
		return;
	}

	size_t idx = HashTableBase<K, V>::hash(key);
	m_bucketsArray[idx].pushBack(HashNode(key, value));
	
	if (float(++HashTableBase<K, V>::m_size) / HashTableBase<K, V>::m_capacity >= HashTableBase<K, V>::loadFactor) 
		rehash(true);
}

template <class K, class V>
void HashTableWithChains<K, V>::erase(const K& key) {
	size_t idx = HashTableBase<K, V>::hash(key);
	size_t i = 0;
	for (HashNode& hashNode : m_bucketsArray[idx]) {
		if (!(hashNode.key == key)) {
			i++;
			continue;
		}

		m_bucketsArray[idx].pop(i);

		if (float(--HashTableBase<K, V>::m_size) / HashTableBase<K, V>::m_capacity <= HashTableBase<K, V>::unloadFactor)
			rehash(false);
		return;
	}
}

template <class K, class V>
void HashTableWithChains<K, V>::clear() {
	LinkedList<HashNode>* tmp = m_bucketsArray;
	m_bucketsArray = new LinkedList<HashNode>[HashTableBase<K, V>::m_capacity];

	delete[] tmp;
}