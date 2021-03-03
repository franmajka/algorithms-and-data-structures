#include "LongKey.h"

#include <iostream>

LongKey::LongKey() {
	m_key = 0;

	size_t digit = 1;
	for (int i = 0; i < 11; i++, digit *= 10) {
		m_key += size_t(rand() % 10) * digit;
	}

	m_key += (1 + size_t(rand() % 9)) * digit;
}

size_t LongKey::getKey() const {
	return m_key;
}

LongKey::LongKey(size_t key) {
	m_key = key;
}

bool LongKey::operator== (const LongKey& other) const {
	return m_key == other.m_key;
}

size_t std::hash<LongKey>::operator() (const LongKey& key) const {
	return key.getKey();
}