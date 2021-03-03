#include "StringKey.h"

#include <iostream>
#include <string>

StringKey::StringKey() {
	m_key = "";
	
	for (int i = 0; i < 10; i++) {
		m_key += 'a' + (rand() % ('z' - 'a'));
	}
}

StringKey::StringKey(const char* key) {
	m_key = key;
}

std::string StringKey::getKey() const {
	return m_key;
}

bool StringKey::operator== (const StringKey& strKey) const {
	return m_key == strKey.m_key;
}


// Prime numbers
#define A 54059
#define B 76963
#define C 86969
#define FIRSTH 37

size_t std::hash<StringKey>::operator() (const StringKey& key) const {
	size_t h = FIRSTH;
	for (const size_t& c : key.getKey()) {
		h = (h * A) ^ (c * B);
	}
	return h;
}