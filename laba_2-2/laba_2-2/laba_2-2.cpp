#include <iostream>
#include <cstdlib>
#include <ctime>
#include <clocale>
#include <string>
#include <fstream>
#include <regex>

#include "ControlWork.h"

#include "LongKey.h"
#include "StringKey.h"

#include "HashTableWithChains.h"
#include "HashTableWithOpenAddressing.h"
#include <unordered_map>

using namespace std;

bool testHashTable()
{
    const int iters = 500000;
    const int keysAmount = iters * 1;
    // generate random keys:
    LongKey* keys = new LongKey[keysAmount];
    LongKey* keysToInsert = new LongKey[iters];
    LongKey* keysToErase = new LongKey[iters];
    LongKey* keysToFind = new LongKey[iters];

    for (int i = 0; i < iters; i++)
    {
        keysToInsert[i] = keys[LongKey().getKey() % keysAmount];
        keysToErase[i] = keys[LongKey().getKey() % keysAmount];
        keysToFind[i] = keys[LongKey().getKey() % keysAmount];
    }
    // test my HashTable:
    HashTableWithChains<LongKey, ControlWork> hashTable;

    float myTotal = 0;
    float tempTime = 0;
    clock_t start = clock();

    for (int i = 0; i < iters; i++)
    {
        hashTable.insert(keysToInsert[i], ControlWork());
    }
    size_t myInsertSize = hashTable.size();

    tempTime = float(clock() - start) / CLOCKS_PER_SEC;
    myTotal += tempTime;
    cout << "MyInsert " << tempTime << endl;

    start = clock();
    for (int i = 0; i < iters; i++)
    {
        hashTable.erase(keysToErase[i]);
    }
    size_t myEraseSize = hashTable.size();

    tempTime = float(clock() - start) / CLOCKS_PER_SEC;
    myTotal += tempTime;
    cout << "MyErase " << tempTime << endl;

    start = clock();
    int myFoundAmount = 0;
    for (int i = 0; i < iters; i++)
    {
        if (hashTable.find(keysToFind[i]) != NULL)
        {
            myFoundAmount++;
        }
    }

    tempTime = float(clock() - start) / CLOCKS_PER_SEC;
    myTotal += tempTime;
    cout << "MyFind " << tempTime << endl << endl;

    // test STL hash table:
    unordered_map<LongKey, ControlWork> unorderedMap;
    float stlTotal = 0;
    start = clock();
    for (int i = 0; i < iters; i++)
    {
        unorderedMap.insert({ keysToInsert[i], ControlWork() });
    }

    tempTime = float(clock() - start) / CLOCKS_PER_SEC;
    stlTotal += tempTime;
    cout << "StlInsert " << tempTime << endl;

    size_t stlInsertSize = unorderedMap.size();

    start = clock();
    for (int i = 0; i < iters; i++)
    {
        unorderedMap.erase(keysToErase[i]);
    }

    tempTime = float(clock() - start) / CLOCKS_PER_SEC;
    stlTotal += tempTime;
    cout << "StlErase " << tempTime << endl;

    size_t stlEraseSize = unorderedMap.size();
    int stlFoundAmount = 0;

    start = clock();
    for (int i = 0; i < iters; i++)
    {
        if (unorderedMap.find(keysToFind[i]) != unorderedMap.end())
        {
            stlFoundAmount++;
        }
    }
    
    tempTime = float(clock() - start) / CLOCKS_PER_SEC;
    stlTotal += tempTime;
    cout << "StlFind " << tempTime << endl << endl;

    cout << "My HashTable:" << endl;
    cout << "Time: " << myTotal << ", size: " << myInsertSize << " - " << myEraseSize <<
        ", found amount: " << myFoundAmount << endl;
    cout << "STL unordered_map:" << endl;
    cout << "Time: " << stlTotal << ", size: " << stlInsertSize << " - " << stlEraseSize
        << ", found amount: " << stlFoundAmount << endl << endl;
    delete[] keys;
    delete[] keysToInsert;
    delete[] keysToErase;
    delete[] keysToFind;
    if (myInsertSize == stlInsertSize && myEraseSize == stlEraseSize && myFoundAmount ==
        stlFoundAmount)
    {
        cout << "The lab is completed" << endl;
        return true;
    }
    cerr << ":(" << endl;
    return false;
}

void countWords(string filenameIn = "in.txt", string filenameOut = "out.txt") {
    HashTableWithOpenAddressing<string, int> hashTable;
    LinkedList<pair<string, int>> lst;

    ifstream fin(filenameIn);
    regex wordRegex(R"((\w|[+’'À-ßà-ÿ¨¸])*)");

    while (!fin.eof()) {
        string tmp;
        smatch sm;

        fin >> tmp;

        regex_search(tmp, sm, wordRegex);

        string word = sm.str();
        if (word == "") continue;

        transform(word.begin(), word.end(), word.begin(), [](unsigned char c) { return std::tolower(c); });

        int* found = hashTable.find(word);
        if (found != NULL) {
            hashTable.insert(word, *found + 1);
        }
        else {
            hashTable.insert(word, 1);
        }
    }

    fin.close();
    
    ofstream fout(filenameOut);

    for (pair<string, int> p : hashTable) {
        lst.pushBack(p);
    }

    lst.sort([](const pair<string, int>& l, const pair<string, int>& r) { return l.second > r.second; });

    for (const pair<string, int>& p : lst) {
        fout << p.first << ": " << p.second << endl;
    }

    fout.close();
}


int main()
{
    setlocale(LC_ALL, "rus");
    srand(time(NULL));

    testHashTable();
    //countWords();

    /*LinkedList<int> lst = { 2, 3, 4 };
    LinkedList<int> lst2 = { 6, 7, 8 };

    lst += 1 + LinkedList<int>{ 1, 2 };

    lst.print();*/

    return 0;
}
