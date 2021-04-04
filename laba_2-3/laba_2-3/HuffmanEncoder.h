#pragma once

#include <fstream>
#include <vector>
#include <unordered_map>

#include "PriorityQueue.h"

class HuffmanEncoder
{
public:
	using WeightString = std::pair<std::string, unsigned>;
	using WeightTable = std::unordered_map<char, unsigned>;
	using CodesTable = std::unordered_map<std::string, std::string>;

	struct BinaryTree
	{
		struct Node {
			WeightString value;

			Node* leftChild = NULL;
			Node* rightChild = NULL;

			Node() : leftChild(NULL), rightChild(NULL) {}
			Node(const WeightString& avalue) : Node() { value = avalue; }
		};

		Node* root;

		BinaryTree() : root(NULL) {};

		BinaryTree(const WeightString& avalue) {
			root = new Node(avalue);
		}

		BinaryTree(Node* anode) {
			root = anode;
		}

		friend BinaryTree operator+ (const BinaryTree& l, const BinaryTree& r) {
			Node* node = new Node({ l.root->value.first + r.root->value.first, l.root->value.second + r.root->value.second });
			node->leftChild = l.root;
			node->rightChild = r.root;
			return BinaryTree(node);
		}
	};

	HuffmanEncoder(std::ifstream& fin);

	WeightTable countSymbols();

	std::string tableToBits();
	std::string textToBits();

	void bypass(BinaryTree::Node* node, std::string code = "");
	void writeToBinary(std::ofstream& fout);
	void encode(std::ofstream& fout);
	void printTable();

private:
	std::string m_text;
	CodesTable m_codesTable;
};

namespace std {
	template <>
	struct greater<HuffmanEncoder::BinaryTree> {
		constexpr bool operator() (const HuffmanEncoder::BinaryTree& lhs, const HuffmanEncoder::BinaryTree& rhs) const;
	};
}