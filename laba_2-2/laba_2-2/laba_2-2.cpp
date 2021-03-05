#include <iostream>
#include <cstdlib>
#include <ctime>
#include <clocale>
#include <string>

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
    HashTableWithOpenAddressing<LongKey, ControlWork> hashTable;

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
    clock_t stlStart = clock();
    for (int i = 0; i < iters; i++)
    {
        unorderedMap.insert({ keysToInsert[i], ControlWork() });
    }
    size_t stlInsertSize = unorderedMap.size();
    for (int i = 0; i < iters; i++)
    {
        unorderedMap.erase(keysToErase[i]);
    }
    size_t stlEraseSize = unorderedMap.size();
    int stlFoundAmount = 0;
    for (int i = 0; i < iters; i++)
    {
        if (unorderedMap.find(keysToFind[i]) != unorderedMap.end())
        {
            stlFoundAmount++;
        }
    }
    clock_t stlEnd = clock();
    float stlTime = (float(stlEnd - stlStart)) / CLOCKS_PER_SEC;
    cout << "My HashTable:" << endl;
    cout << "Time: " << myTotal << ", size: " << myInsertSize << " - " << myEraseSize <<
        ", found amount: " << myFoundAmount << endl;
    cout << "STL unordered_map:" << endl;
    cout << "Time: " << stlTime << ", size: " << stlInsertSize << " - " << stlEraseSize
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


int main()
{
    setlocale(LC_ALL, "rus");
    srand(time(NULL));

    testHashTable();

    /*HashTableWithOpenAddressing<string, ControlWork> hashTable;

    ControlWork c1, c2;

    cout << c1 << endl;
    cout << c2 << endl;

    hashTable.insert("c1", c1);
    cout << hashTable["c1"] << endl;
    hashTable["c1"] = c2;

    cout << hashTable["c1"] << endl;*/

    return 0;
}
