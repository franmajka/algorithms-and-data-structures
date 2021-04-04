#include "HuffmanEncoder.h"

#include <iostream>
#include <fstream>
#include <string>
#include <bitset>

#include "PriorityQueue.h"

#define BYTE_LENGTH 8

using namespace std;

HuffmanEncoder::HuffmanEncoder(std::ifstream& fin)
{
	string tmp;
	while (true) {
		getline(fin, tmp);
		m_text += tmp;

		if (fin.eof()) {
			break;
		}
		else {
			m_text += '\n';
		}
	}
}

HuffmanEncoder::WeightTable HuffmanEncoder::countSymbols()
{
	WeightTable weightTable;

	for (const char& c : m_text) {
		auto it = weightTable.find(c);
		if (it != weightTable.end()) {
			it->second += 1;
		}
		else {
			weightTable.insert({ c, 1 });
		}
	}

	return weightTable;
}

std::string HuffmanEncoder::tableToBits()
{
	string bits = "";
	uint8_t tableSize = m_codesTable.size();
	bits += bitset<8>(tableSize).to_string();

	for (const auto& p : m_codesTable) {
		bits += bitset<8>(p.first.front()).to_string();
		bits += bitset<8>(uint8_t(p.second.size())).to_string();
		bits += p.second;
	}

	return bits;
}

std::string HuffmanEncoder::textToBits()
{
	string bits = "";
	bits += bitset<64>(uint64_t(m_text.size())).to_string();

	for (const char& c : m_text) {
		bits += m_codesTable[string(1, c)];
	}

	return bits;
}

void HuffmanEncoder::bypass(BinaryTree::Node* node, std::string code)
{
	if (!node) return;

	if (!(node->leftChild || node->rightChild)) {
		m_codesTable.insert({ node->value.first, code });
	}

	if (node->leftChild) {
		bypass(node->leftChild, code + "0");
	}

	if (node->rightChild) {
		bypass(node->rightChild, code + "1");
	}
}

void HuffmanEncoder::writeToBinary(std::ofstream& fout)
{
	string bits = tableToBits() + textToBits();

	size_t bytesLength = ceil(float(bits.size()) / BYTE_LENGTH);
	size_t bitsLength = BYTE_LENGTH * bytesLength;

	char* bytes = new char[bytesLength];
	memset(bytes, 0, bytesLength);

	char* bytePtr = bytes;

	auto it = bits.begin();
	for (size_t counter = 0; counter < bitsLength;) {
		if (it != bits.end()) {
			*bytePtr |= *it == '1';

			++it;
		}

		if (!(++counter % BYTE_LENGTH)) {
			++bytePtr;
		}
		else *bytePtr <<= 1;
	}

	fout.write(bytes, bytesLength);

	delete[] bytes;
}

constexpr bool std::greater<HuffmanEncoder::BinaryTree>::operator()
(const HuffmanEncoder::BinaryTree& lhs, const HuffmanEncoder::BinaryTree& rhs) const
{
	return lhs.root->value.second > rhs.root->value.second;
}

void HuffmanEncoder::encode(std::ofstream& fout)
{
	PriorityQueue<BinaryTree, greater<HuffmanEncoder::BinaryTree>> pq;
	for (const auto& p : countSymbols()) {
		pq.push(BinaryTree({ string(1, p.first), p.second }));
	}

	while (pq.size() > 1) {
		pq.push(pq.pop() + pq.pop());
	}

	bypass(pq.pop().root);

	writeToBinary(fout);
}

void HuffmanEncoder::printTable()
{
	for (const auto& p : m_codesTable) {
		cout << p.first << " — " << p.second << endl;
	}
}
