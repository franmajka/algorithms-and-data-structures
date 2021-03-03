#include <iostream>
#include <cstdlib>
#include <ctime>
#include <clocale>
#include <string>

#include "ControlWork.h"

#include "LongKey.h"
#include "StringKey.h"

#include "HashTableWithChains.h"
#include <unordered_map>

using namespace std;

//bool testHashTable()
//{
//    const int iters = 500000;
//    const int keysAmount = iters * 1;
//    // generate random keys:
//    LongKey* keys = new LongKey[keysAmount];
//    LongKey* keysToInsert = new LongKey[iters];
//    LongKey* keysToErase = new LongKey[iters];
//    LongKey* keysToFind = new LongKey[iters];
//
//    for (int i = 0; i < iters; i++)
//    {
//        keysToInsert[i] = keys[LongKey().getKey() % keysAmount];
//        keysToErase[i] = keys[LongKey().getKey() % keysAmount];
//        keysToFind[i] = keys[LongKey().getKey() % keysAmount];
//    }
//    // test my HashTable:
//    HashTableWithChains<LongKey, ControlWork> hashTable;
//    clock_t myStart = clock();
//    for (int i = 0; i < iters; i++)
//    {
//        hashTable.insert(keysToInsert[i], ControlWork());
//    }
//    size_t myInsertSize = hashTable.size();
//    for (int i = 0; i < iters; i++)
//    {
//        hashTable.erase(keysToErase[i]);
//    }
//    size_t myEraseSize = hashTable.size();
//    int myFoundAmount = 0;
//    for (int i = 0; i < iters; i++)
//    {
//        if (hashTable.find(keysToFind[i]) != NULL)
//        {
//            myFoundAmount++;
//        }
//    }
//    clock_t myEnd = clock();
//    float myTime = (float(myEnd - myStart)) / CLOCKS_PER_SEC;
//    // test STL hash table:
//    unordered_map<LongKey, ControlWork> unorderedMap;
//    clock_t stlStart = clock();
//    for (int i = 0; i < iters; i++)
//    {
//        unorderedMap.insert({ keysToInsert[i], ControlWork() });
//    }
//    size_t stlInsertSize = unorderedMap.size();
//    for (int i = 0; i < iters; i++)
//    {
//        unorderedMap.erase(keysToErase[i].hash());
//    }
//    size_t stlEraseSize = unorderedMap.size();
//    int stlFoundAmount = 0;
//    for (int i = 0; i < iters; i++)
//    {
//        if (unorderedMap.find(keysToFind[i].hash()) != unorderedMap.end())
//        {
//            stlFoundAmount++;
//        }
//    }
//    clock_t stlEnd = clock();
//    float stlTime = (float(stlEnd - stlStart)) / CLOCKS_PER_SEC;
//    cout << "My HashTable:" << endl;
//    cout << "Time: " << myTime << ", size: " << myInsertSize << " - " << myEraseSize <<
//        ", found amount: " << myFoundAmount << endl;
//    cout << "STL unordered_map:" << endl;
//    cout << "Time: " << stlTime << ", size: " << stlInsertSize << " - " << stlEraseSize
//        << ", found amount: " << stlFoundAmount << endl << endl;
//    delete[] keys;
//    delete[] keysToInsert;
//    delete[] keysToErase;
//    delete[] keysToFind;
//    if (myInsertSize == stlInsertSize && myEraseSize == stlEraseSize && myFoundAmount ==
//        stlFoundAmount)
//    {
//        cout << "The lab is completed" << endl;
//        return true;
//    }
//    cerr << ":(" << endl;
//    return false;
//}


int main()
{
    setlocale(LC_ALL, "rus");
    srand(time(NULL));

    HashTableWithChains<StringKey, ControlWork> hashTable;

    StringKey k("c2");
    ControlWork c1, c2;

    cout << c1 << endl;
    cout << c2 << endl;

    /*hashTable[0] = c1;
    cout << "Size " << hashTable.getSize() << endl;
    cout << hashTable[0] << endl;*/

    hashTable.insert(k, c2);
    cout << hashTable["c2"] << endl;

    HashTableWithChains<StringKey, ControlWork> newHashTable = hashTable;
    cout << newHashTable["c2"] << endl;

    hashTable["c1"] = c1;

    hashTable = newHashTable;

    cout << hashTable.find(StringKey("c1"));



    return 0;
}