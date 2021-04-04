#pragma once

#include <unordered_map>
#include <string>
#include <fstream>
#include <bitset>

struct pairhash {
public:
	template <typename T, typename U>
	std::size_t operator()(const std::pair<T, U>& x) const
	{
		return std::hash<T>()(x.first) ^ std::hash<U>()(x.second);
	}
};

class HuffmanDecoder
{
public:
	using bPair = std::pair<std::bitset<64>, uint8_t>;
	using CodesTable = std::unordered_map<bPair, char, pairhash>;

	bPair readBits(const uint8_t& quantity);

	HuffmanDecoder(const std::string& fname) : m_fin(fname, std::ios::binary) {}
	~HuffmanDecoder() { m_fin.close(); }

	void decode(std::ofstream& fout);

	void printTable();

private:
	std::ifstream m_fin;
	CodesTable m_codesTable;

	char byteBuffer = 0;
	uint8_t bitsLeft = 0;
};

