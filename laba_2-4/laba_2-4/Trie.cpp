#include "Trie.h"

#include <string>
#include <unordered_map>
#include <vector>
#include <fstream>

Trie::Trie(std::ifstream& fin)
{
	while (!fin.eof()) {
		std::string tmp;
		fin >> tmp;
		insert(tmp);
	}
}

Trie::Trie(std::initializer_list<std::string> words)
{
	for (const std::string& word : words) {
		insert(word);
	}
}

void Trie::insert(const std::string& word)
{
	auto* table = &m_firstLetters;

	for (auto wordIt = word.begin(); wordIt != word.end();) {
		auto it = table->find(*wordIt);
		if (it != table->end()) {
			table = &it->second.nextChars;
			++wordIt;
			continue;
		}

		table->insert({ *wordIt, Node((wordIt + 1 == word.end())) });
	}
}

std::vector<std::string> Trie::findByPrefix(const std::string& prefix)
{
	std::vector<std::string> vec;
	auto* table = &m_firstLetters;

	for (const char& c : prefix) {
		auto it = table->find(c);
		if (it == table->end()) return vec;

		table = &it->second.nextChars;
	}

	bypass(*table, vec, prefix);

	return vec;
}

void Trie::bypass
(const std::unordered_map<char, typename Trie::Node>& table, std::vector<std::string>& words, const std::string& prefix) const
{
	for (const auto& p : table) {
		if (p.second.isEnd) words.push_back(prefix + p.first);
		bypass(p.second.nextChars, words, prefix + p.first);
	}
}
