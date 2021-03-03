#pragma once

#include <string>

class StringKey
{
public:
	StringKey();
	StringKey(const char*);

	std::string getKey() const;

	bool operator== (const StringKey&) const;

private:
	std::string m_key;
};

namespace std {
	template <>
	struct hash<StringKey> {
		size_t operator() (const StringKey& key) const;
	};
}
