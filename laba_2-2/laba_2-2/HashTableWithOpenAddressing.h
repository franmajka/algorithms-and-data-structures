#pragma once

#include "HashTableBase.h"

#include <iostream>

#define ALPHA 2

// aka (sqrt(5) - 1) / 2
#define A 0.618033988

template <class K, class V>
class HashTableWithOpenAddressing : public HashTableBase<K, V>
{
private: 
	struct HashNode : public HashTableBase<K, V>::HashNode {
		bool isDeleted = false;

		HashNode(const K& key, const V& value) : HashTableBase<K, V>::HashNode(key, value) {}
		HashNode(const K& key) : HashTableBase<K, V>::HashNode(key) {}
	};

public:
	template <bool Const = false>
	class Iterator {
		friend class HashTableWithOpenAddressing<K, V>;
		
	public:
		using pointer = std::conditional_t<Const, const HashNode**, HashNode**>;
		using reference = std::conditional_t<Const, const std::pair<K, V>, std::pair<K, V>>;

	private:
		pointer p;
		int countdown;

		Iterator(pointer ap, int acountdown);
	public:
		Iterator(const Iterator& it) : p(it.p), countdown(it.countdown) {}

		bool operator!= (const Iterator&) const;
		bool operator== (const Iterator&) const;

		template <bool _Const = Const>
		std::enable_if_t <_Const, reference> operator* () const;
		template <bool _Const = Const>
		std::enable_if_t<!_Const, reference> operator* ();

		Iterator<Const>& operator++ ();
	};

	HashTableWithOpenAddressing();
	HashTableWithOpenAddressing(const HashTableWithOpenAddressing&);
	~HashTableWithOpenAddressing();

	Iterator<true> begin() const;
	Iterator<true> end() const;

	Iterator<false> begin();
	Iterator<false> end();

	V* find(const K& key);

	size_t hashSecondary(const K& key);

	void insert(const K& key, const V& value);
	void erase(const K& key);

	void clear();

	V& operator[] (const K& key);
	template <class T>
	V& operator[] (const T& key);

	const V& operator[] (const K& key) const;
	template <class T>
	const V& operator[] (const T& key) const;

	HashTableWithOpenAddressing<K, V>& operator= (const HashTableWithOpenAddressing<K, V>&);
	const HashTableWithOpenAddressing<K, V>& operator= (const HashTableWithOpenAddressing<K, V>&) const;
private:
	void rehash(bool isLoaded);

	HashNode **m_bucketsArray;
};


template <class K, class V>
HashTableWithOpenAddressing<K, V>::HashTableWithOpenAddressing() {
	m_bucketsArray = new HashNode * [HashTableBase<K, V>::m_capacity];
	for (size_t i = 0; i < HashTableBase<K, V>::m_capacity; i++) m_bucketsArray[i] = NULL;
}

template <class K, class V>
HashTableWithOpenAddressing<K, V>::HashTableWithOpenAddressing(const HashTableWithOpenAddressing& other) {
	m_bucketsArray = new HashNode * [HashTableBase<K, V>::m_capacity];
	for (size_t i = 0; i < HashTableBase<K, V>::m_capacity; i++) m_bucketsArray[i] = NULL;

	for (size_t i = 0; i < other.HashTableBase<K, V>::m_capacity; i++) {
		if (other.m_bucketsArray[i] == NULL || other.m_bucketsArray[i]->isDeleted) continue;
		insert(other.m_bucketsArray[i]->key, other.m_bucketsArray[i]->value);
	}
}

template <class K, class V>
HashTableWithOpenAddressing<K, V>::~HashTableWithOpenAddressing() {
	for (size_t i = 0; i < HashTableBase<K, V>::m_capacity; i++) {
		if (m_bucketsArray[i] != NULL) delete m_bucketsArray[i];
	}
	delete[] m_bucketsArray;
}


// returns odd hash
template <class K, class V>
size_t HashTableWithOpenAddressing<K, V>::hashSecondary(const K& key) {
	return 2 * size_t(HashTableBase<K, V>::m_capacity * fmod(std::hash<K>()(key) * A, 1)) + 1;
}


template <class K, class V>
void HashTableWithOpenAddressing<K, V>::rehash(bool isLoaded) {
	HashNode **originalBucketsArray = m_bucketsArray;
	size_t originalCapacity = HashTableBase<K, V>::m_capacity;

	HashTableBase<K, V>::m_size = 0;
	HashTableBase<K, V>::m_capacity = isLoaded ?
		HashTableBase<K, V>::m_capacity * ALPHA :
		HashTableBase<K, V>::m_capacity / ALPHA;

	m_bucketsArray = new HashNode*[HashTableBase<K, V>::m_capacity];
	for (size_t i = 0; i < HashTableBase<K, V>::m_capacity; i++) m_bucketsArray[i] = NULL;

	for (size_t i = 0; i < originalCapacity; i++) {
		if (originalBucketsArray[i] != NULL && !originalBucketsArray[i]->isDeleted) {
			insert(originalBucketsArray[i]->key, originalBucketsArray[i]->value);
			delete originalBucketsArray[i];
		}
	}

	delete[] originalBucketsArray;
}


template <class K, class V>
V* HashTableWithOpenAddressing<K, V>::find(const K& key) {
	size_t firstIdx = HashTableBase<K, V>::hash(key);
	size_t shift = hashSecondary(key);

	for (
		size_t i = 0, idx = firstIdx;
		i < HashTableBase<K, V>::m_capacity;
		i++, idx = (idx + shift) % HashTableBase<K, V>::m_capacity
	) {
		if (m_bucketsArray[idx] == NULL) return NULL;
		if (!(m_bucketsArray[idx]->key == key) || m_bucketsArray[idx]->isDeleted) continue;

		return &m_bucketsArray[idx]->value;
	}

	return NULL;
}

template <class K, class V>
void HashTableWithOpenAddressing<K, V>::insert(const K& key, const V& value) {
	size_t firstIdx = HashTableBase<K, V>::hash(key);
	size_t shift = hashSecondary(key);

	for (
		size_t i = 0, idx = firstIdx;
		i < HashTableBase<K, V>::m_capacity;
		i++, idx = (idx + shift) % HashTableBase<K, V>::m_capacity
	) {
		if (m_bucketsArray[idx] == NULL) {
			m_bucketsArray[idx] = new HashNode(key, value);

			if (float(++HashTableBase<K, V>::m_size) / HashTableBase<K, V>::m_capacity >= HashTableBase<K, V>::loadFactor) rehash(true);

			return;
		}
		else if (m_bucketsArray[idx]->key == key) {
			m_bucketsArray[idx]->value = value;

			return;
		}
		else if (m_bucketsArray[idx]->isDeleted) {
			m_bucketsArray[idx]->key = key;
			m_bucketsArray[idx]->value = value;
			m_bucketsArray[idx]->isDeleted = false;

			if (float(++HashTableBase<K, V>::m_size) / HashTableBase<K, V>::m_capacity >= HashTableBase<K, V>::loadFactor) rehash(true);

			return;
		}
	}
}

template <class K, class V>
void HashTableWithOpenAddressing<K, V>::erase(const K& key) {
	size_t firstIdx = HashTableBase<K, V>::hash(key);
	size_t shift = hashSecondary(key);

	for (
		size_t i = 0, idx = firstIdx;
		i < HashTableBase<K, V>::m_capacity;
		i++, idx = (idx + shift) % HashTableBase<K, V>::m_capacity
	) {
		if (m_bucketsArray[idx] == NULL) return;
		if (!(m_bucketsArray[idx]->key == key) || m_bucketsArray[idx]->isDeleted) continue;

		m_bucketsArray[idx]->isDeleted = true;

		if (float(--HashTableBase<K, V>::m_size) / HashTableBase<K, V>::m_capacity <= HashTableBase<K, V>::unloadFactor) rehash(false);

		return;
	}
}


template <class K, class V>
void HashTableWithOpenAddressing<K, V>::clear() {
	HashNode** tmp = m_bucketsArray;
	m_bucketsArray = new HashNode * [HashTableBase<K, V>::m_capacity];

	for (size_t i = 0; i < HashTableBase<K, V>::m_capacity; i++) {
		delete tmp[i];
		m_bucketsArray[i] = NULL;
	}

	delete[] tmp;
}


template <class K, class V>
V& HashTableWithOpenAddressing<K, V>::operator[] (const K& key) {
	V* ptr = find(key);

	if (ptr != NULL) return *ptr;

	throw "There is no such key in the hash table";
}

template <class K, class V> template <class T>
V& HashTableWithOpenAddressing<K, V>::operator[] (const T& key) {
	return (*this)[K(key)];
}

template <class K, class V>
const V& HashTableWithOpenAddressing<K, V>::operator[] (const K& key) const {
	return (*this)[key];
}

template <class K, class V> template <class T>
const V& HashTableWithOpenAddressing<K, V>::operator[] (const T& key) const {
	return (*this)[K(key)];
}


template <class K, class V>
HashTableWithOpenAddressing<K, V>& HashTableWithOpenAddressing<K, V>::operator= (const HashTableWithOpenAddressing<K, V>& other) {
	clear();

	for (size_t i = 0; i < other.HashTableBase<K, V>::m_capacity; i++) {
		if (other.m_bucketsArray[i] == NULL || other.m_bucketsArray[i]->isDeleted) continue;
		insert(other.m_bucketsArray[i]->key, other.m_bucketsArray[i]->value);
	}

	return *this;
}

template <class K, class V>
const HashTableWithOpenAddressing<K, V>& HashTableWithOpenAddressing<K, V>::operator= (const HashTableWithOpenAddressing<K, V>& other) const {
	throw "You're trying to change const variable";
}


template <class K, class V> template <bool Const>
HashTableWithOpenAddressing<K, V>::Iterator<Const>::Iterator (HashTableWithOpenAddressing<K, V>::Iterator<Const>::pointer ap, int acountdown) {
	p = ap;
	countdown = acountdown;

	if (countdown && *p == NULL) {
		++(*this);
	}
}

template <class K, class V> template <bool Const>
bool HashTableWithOpenAddressing<K, V>::Iterator<Const>::operator!= (const HashTableWithOpenAddressing<K, V>::Iterator<Const>& other) const {
	return p != other.p;
}

template <class K, class V> template <bool Const>
bool HashTableWithOpenAddressing<K, V>::Iterator<Const>::operator== (const HashTableWithOpenAddressing<K, V>::Iterator<Const>& other) const {
	return p == other.p;
}

template <class K, class V> template <bool Const> template <bool _Const>
std::enable_if_t <_Const, typename HashTableWithOpenAddressing<K, V>::Iterator<Const>::reference> 
HashTableWithOpenAddressing<K, V>::Iterator<Const>::operator* () const {
	return std::make_pair((*p)->key, (*p)->value);
}

template <class K, class V> template <bool Const> template <bool _Const>
std::enable_if_t <!_Const, typename HashTableWithOpenAddressing<K, V>::Iterator<Const>::reference>
HashTableWithOpenAddressing<K, V>::Iterator<Const>::operator* () {
	return std::make_pair((*p)->key, (*p)->value);
}

template <class K, class V> template <bool Const>
HashTableWithOpenAddressing<K, V>::Iterator<Const>& HashTableWithOpenAddressing<K, V>::Iterator<Const>::operator++ () {
	do {
		++p;
		--countdown;
	} while (countdown && (*p == NULL || (*p)->isDeleted));

	return *this;
}

template <class K, class V>
HashTableWithOpenAddressing<K, V>::Iterator<true> HashTableWithOpenAddressing<K, V>::begin() const {
	return HashTableWithOpenAddressing<K, V>::Iterator<true>(m_bucketsArray, HashTableBase<K, V>::m_capacity);
}

template <class K, class V>
HashTableWithOpenAddressing<K, V>::Iterator<true> HashTableWithOpenAddressing<K, V>::end() const {
	return HashTableWithOpenAddressing<K, V>::Iterator<true>(m_bucketsArray + HashTableBase<K, V>::m_capacity, 0);
}

template <class K, class V>
HashTableWithOpenAddressing<K, V>::Iterator<false> HashTableWithOpenAddressing<K, V>::begin() {
	return HashTableWithOpenAddressing<K, V>::Iterator<false>(m_bucketsArray, HashTableBase<K, V>::m_capacity);
}

template <class K, class V>
HashTableWithOpenAddressing<K, V>::Iterator<false> HashTableWithOpenAddressing<K, V>::end() {
	return HashTableWithOpenAddressing<K, V>::Iterator<false>(m_bucketsArray + HashTableBase<K, V>::m_capacity, 0);
}