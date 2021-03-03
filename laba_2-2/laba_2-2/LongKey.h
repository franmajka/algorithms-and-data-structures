#pragma once

#include <iostream>

class LongKey
{

public:
	LongKey();
	LongKey(size_t);

	size_t getKey() const;

	bool operator== (const LongKey&) const;

private:
	size_t m_key;
};

namespace std {
	template <>
	struct hash<LongKey> {
		size_t operator() (const LongKey& key) const;
	};
}