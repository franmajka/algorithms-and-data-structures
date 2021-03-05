#pragma once

#include <iostream>

#define M 8

template <class K, class V>
class HashTableBase
{
public:
	size_t hash(K key);

	size_t size();

protected:
	struct HashNode {
		K key;
		V value;

		HashNode(const K&, const V&);
		HashNode(const K&);
	};

	size_t m_size = 0;
	size_t m_capacity = M;

	const float unloadFactor = .25;
	const float loadFactor = .75;
};

template <class K, class V>
HashTableBase<K, V>::HashNode::HashNode(const K& akey, const V& avalue) {
	key = akey;
	value = avalue;
}

template <class K, class V>
HashTableBase<K, V>::HashNode::HashNode(const K& akey) {
	key = akey;
}

template <class K, class V>
size_t HashTableBase<K, V>::hash(K key) {
	return std::hash<K>()(key) % m_capacity;
}

template <class K, class V>
size_t HashTableBase<K, V>::size() {
	return m_size;
}