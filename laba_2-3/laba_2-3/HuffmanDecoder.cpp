#include "HuffmanDecoder.h"

#include <iostream>
#include <fstream>
#include <unordered_map>
#include <string>
#include <bitset>

#define BYTE_LENGTH 8

HuffmanDecoder::bPair HuffmanDecoder::readBits(const uint8_t& quantity)
{
	std::bitset<64> bits;

	for (uint8_t i = 0; i < quantity; i++) {
		if (!bitsLeft) {
			m_fin.read((char*)&byteBuffer, 1);
			bitsLeft = BYTE_LENGTH;
		}

		bool leadingBit = byteBuffer & 128;
		byteBuffer <<= 1;
		bitsLeft--;

		bits <<= 1;
		bits |= leadingBit;
	}

	return { bits, quantity };
}

void HuffmanDecoder::decode(std::ofstream& fout)
{
	m_codesTable.clear();

	uint8_t tableSize;
	m_fin.read((char*)&tableSize, sizeof(tableSize));

	for (uint8_t i = 0; i < tableSize; i++) {
		char c = readBits(BYTE_LENGTH).first.to_ulong();
		uint8_t codeLength = readBits(BYTE_LENGTH).first.to_ulong();
		m_codesTable.insert({ readBits(codeLength), c });
	}

	uint64_t textSize = readBits(64).first.to_ullong();

	for (uint64_t i = 0; i < textSize; i++) {
		bPair bits;
		bits.second = 0;

		while (m_codesTable.find(bits) == m_codesTable.end()) {
			bPair newBit = readBits(1);
			bits.first <<= 1;
			bits.first |= newBit.first;
			bits.second += 1;
		}

		fout << m_codesTable[bits];
	}
}

void HuffmanDecoder::printTable()
{
	for (const auto& p : m_codesTable) {
		std::cout << p.first.first << " — " << p.second << std::endl;
	}
}