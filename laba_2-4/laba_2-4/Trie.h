#pragma once

#include <unordered_map>
#include <vector>
#include <string>
#include <fstream>

class Trie {
private:
    struct Node;
public:
    Trie() {}
    Trie(std::ifstream& fin);
    Trie(std::initializer_list<std::string> words);

    void insert(const std::string& word);

    std::vector<std::string> findByPrefix(const std::string& prefix);

private:
    struct Node {
        bool isEnd;
        std::unordered_map<char, Node> nextChars;

        Node(bool aisEnd) : isEnd(aisEnd) {}
        Node() : Node(false) {}
    };

    static void bypass(const std::unordered_map<char, Node>& table, std::vector<std::string>& words, const std::string& prefix);

    std::unordered_map<char, Node> m_firstLetters;
};

