#include <set>
#include <vector>
#include <map>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <fstream>

#include "BinarySearchTree.h"
#include "SplayTree.h"
#include "Player.h"
#include "Trie.h"

using namespace std;

bool testBinarySearchTree()
{
    const int iters = 80000;
    const int keysAmount = iters * 2;
    const int itersToRangeQueries = 1000;
    vector<Player> data(keysAmount);
    vector<Player> dataToInsert(iters);
    vector<Player> dataToErase(iters);
    vector<Player> dataToFind(iters);
    vector<pair<Player, Player>> dataToRangeQueries;
    for (int i = 0; i < iters; i++)
    {
        dataToInsert[i] = data[rand() % keysAmount];
        dataToErase[i] = data[rand() % keysAmount];
        dataToFind[i] = data[rand() % keysAmount];
    }
    for (int i = 0; i < itersToRangeQueries; i++)
    {
        Player minData = Player();
        Player maxData = Player();
        if (maxData < minData)
        {
            swap(minData, maxData);
        }
        dataToRangeQueries.push_back({ minData, maxData });
    }
    BinarySearchTree<Player> myTree;
    set<Player> testTree;
    clock_t myStart = clock();
    for (int i = 0; i < iters; i++)
    {
        myTree.insert(dataToInsert[i]);
    }
    int myInsertSize = myTree.size();
    int myTreeHeight = myTree.height();
    int optimalTreeHeight = log2(myInsertSize) + 1;
    for (int i = 0; i < iters; i++)
    {
        myTree.erase(dataToErase[i]);
    }
    int myEraseSize = myInsertSize - myTree.size();
    int myFoundAmount = 0;
    for (int i = 0; i < iters; i++)
    {
        if (myTree.has(dataToFind[i]))
        {
            myFoundAmount++;
        }
    }
    clock_t myEnd = clock();
    float myTime = (float(myEnd - myStart)) / CLOCKS_PER_SEC;
    set<Player> stlTree;
    clock_t stlStart = clock();
    for (int i = 0; i < iters; i++)
    {
        stlTree.insert(dataToInsert[i]);
        
    }
    int stlInsertSize = stlTree.size();
    for (int i = 0; i < iters; i++)
    {
        stlTree.erase(dataToErase[i]);
    }
    int stlEraseSize = stlInsertSize - stlTree.size();
    int stlFoundAmount = 0;
    for (int i = 0; i < iters; i++)
    {
        if (stlTree.find(dataToFind[i]) != stlTree.end())
        {
            stlFoundAmount++;
        }
    }
    clock_t stlEnd = clock();
    float stlTime = (float(stlEnd - stlStart)) / CLOCKS_PER_SEC;
    clock_t myRangeStart = clock();
    int myRangeFoundAmount = 0;
    for (int i = 0; i < itersToRangeQueries; i++)
    {
        myRangeFoundAmount += myTree.findInRange(dataToRangeQueries[i].first,
            dataToRangeQueries[i].second).size();
    }
    clock_t myRangeEnd = clock();
    float myRangeTime = (float(myRangeEnd - myRangeStart)) / CLOCKS_PER_SEC;
    clock_t stlRangeStart = clock();
    int stlRangeFoundAmount = 0;
    for (int i = 0; i < itersToRangeQueries; i++)
    {
        const auto& low = stlTree.lower_bound(dataToRangeQueries[i].first);
        const auto& up = stlTree.upper_bound(dataToRangeQueries[i].second);
        stlRangeFoundAmount += distance(low, up);
    }
    clock_t stlRangeEnd = clock();
    float stlRangeTime = (float(stlRangeEnd - stlRangeStart)) / CLOCKS_PER_SEC;
    cout << "My BinaryTree: height = " << myTreeHeight << ", optimal height = " <<
        optimalTreeHeight << endl;
    cout << "Time: " << myTime << ", size: " << myInsertSize << " - " << myEraseSize << ", found amount : " << myFoundAmount << endl;
    cout << "Range time: " << myRangeTime << ", range found amount: " << myRangeFoundAmount
        << endl << endl;
    cout << "STL Tree:" << endl;
    cout << "Time: " << stlTime << ", size: " << stlInsertSize << " - " << stlEraseSize <<
        ", found amount: " << stlFoundAmount << endl;
    cout << "Range time: " << stlRangeTime << ", range found amount: " <<
        stlRangeFoundAmount << endl << endl;
    if (myInsertSize == stlInsertSize && myEraseSize == stlEraseSize &&
        myFoundAmount == stlFoundAmount && myRangeFoundAmount == stlRangeFoundAmount)
    {
        cout << "The lab is completed" << endl;
        return true;
    }
    cerr << ":(" << endl;
    return false;
}

void testTrie() {
    cout << "Loading words...";

    ifstream fin("words_alpha.txt");
    Trie t(fin);
    fin.close();

    do {
        cout << endl << "Enter prefix to get all possible words including it" << endl;

        string prefix;
        cin >> prefix;

        auto words = t.findByPrefix(prefix);

        if (words.empty()) {
            cout << "There are no words including " << prefix << endl;
        }

        for (const string& word : words) {
            cout << word << " ";
        }

        cout << endl << "Continue? [y/n]" << endl;
        getc(stdin);
    } while (getc(stdin) == 'y');
}

bool testSplayTree()
{
    const int iters = 500000;
    const int keysAmount = iters * 1;
    // generate random keys:
    long* keys = new long[keysAmount];
    long* keysToInsert = new long[iters];
    long* keysToErase = new long[iters];
    long* keysToFind = new long[iters];
    long* narrowRangeFind = new long[iters];
    for (int i = 0; i < keysAmount; i++)
    {
        keys[i] = rand() % iters;
    }
    for (int i = 0; i < iters; i++)
    {
        keysToInsert[i] = keys[rand() % keysAmount];
        keysToErase[i] = keys[rand() % keysAmount];
        keysToFind[i] = keys[rand() % keysAmount];
        narrowRangeFind[i] = keys[rand() % (keysAmount / 1000)];
    }
    // test my map:
    SplayTree<long, Player> myTree;
    float myTotal = 0;
    float tempTime = 0;
    clock_t start = clock();

    for (int i = 0; i < iters; i++)
    {
        myTree.insert({ keysToInsert[i], Player() });
    }
    size_t myInsertSize = myTree.size();

    tempTime = float(clock() - start) / CLOCKS_PER_SEC;
    myTotal += tempTime;
    cout << "MyInsert " << tempTime << endl;

    /*start = clock();
    for (int i = 0; i < iters; i++)
    {
        myTree.erase(keysToErase[i]);
    }
    size_t myEraseSize = myTree.size();

    tempTime = float(clock() - start) / CLOCKS_PER_SEC;
    myTotal += tempTime;
    cout << "MyErase " << tempTime << endl;*/

    start = clock();
    int myFoundAmount = 0;
    for (int i = 0; i < iters; i++)
    {
        if (myTree.find(keysToFind[i]) != myTree.end())
        {
            myFoundAmount++;
        }
    }

    tempTime = float(clock() - start) / CLOCKS_PER_SEC;
    myTotal += tempTime;
    cout << "MyFind " << tempTime << endl;

    start = clock();
    int myNarrowFoundAmount = 0;
    for (int i = 0; i < iters; i++)
    {
        if (myTree.find(narrowRangeFind[i]) != myTree.end())
        {
            myNarrowFoundAmount++;
        }
    }

    tempTime = float(clock() - start) / CLOCKS_PER_SEC;
    myTotal += tempTime;
    cout << "MyNarrowRangeFind " << tempTime << endl << endl;

    // test STL map:
    map<long, Player> stlMap;
    float stlTotal = 0;
    start = clock();
    for (int i = 0; i < iters; i++)
    {
        stlMap.insert({ keysToInsert[i], Player() });
    }

    tempTime = float(clock() - start) / CLOCKS_PER_SEC;
    stlTotal += tempTime;
    cout << "StlInsert " << tempTime << endl;

    size_t stlInsertSize = stlMap.size();

    /*start = clock();
    for (int i = 0; i < iters; i++)
    {
        stlMap.erase(keysToErase[i]);
    }

    tempTime = float(clock() - start) / CLOCKS_PER_SEC;
    stlTotal += tempTime;
    cout << "StlErase " << tempTime << endl;*/

    size_t stlEraseSize = stlMap.size();
    int stlFoundAmount = 0;

    start = clock();
    for (int i = 0; i < iters; i++)
    {
        if (stlMap.find(keysToFind[i]) != stlMap.end())
        {
            stlFoundAmount++;
        }
    }

    tempTime = float(clock() - start) / CLOCKS_PER_SEC;
    stlTotal += tempTime;
    cout << "StlFind " << tempTime << endl;

    start = clock();
    int stlNarrowFoundAmount = 0;
    for (int i = 0; i < iters; i++)
    {
        if (stlMap.find(narrowRangeFind[i]) != stlMap.end())
        {
            stlNarrowFoundAmount++;
        }
    }

    tempTime = float(clock() - start) / CLOCKS_PER_SEC;
    stlTotal += tempTime;
    cout << "StlNarrowRangeFind " << tempTime << endl << endl;

    cout << "My SplayTree:" << endl;
    cout << "Time: " << myTotal << ", size: " << myInsertSize /*<< " - " << myEraseSize*/ <<
        ", found amount: " << myFoundAmount << endl;
    cout << "STL map:" << endl;
    cout << "Time: " << stlTotal << ", size: " << stlInsertSize /*<< " - " << stlEraseSize */
        << ", found amount: " << stlFoundAmount << endl << endl;
    delete[] keys;
    delete[] keysToInsert;
    delete[] keysToErase;
    delete[] keysToFind;
    delete[] narrowRangeFind;
    if (myInsertSize == stlInsertSize /*&& myEraseSize == stlEraseSize*/ && myFoundAmount ==
        stlFoundAmount && myNarrowFoundAmount == stlNarrowFoundAmount)
    {
        cout << "The lab is completed" << endl;
        return true;
    }
    cerr << ":(" << endl;
    return false;
}

int main()
{
    srand(time(NULL));
    //testBinarySearchTree();
    testTrie();
    //testSplayTree();
    /*SplayTree<int, string> splayTree = {
        { 10, "chel" },
        { 8, "lox" },
        { 9, "ti" },
    };

    for (const auto& p : splayTree) {
        cout << p.first.get() << " " << p.second.get() << endl;
    }

    auto it = splayTree.find(8);
    cout << (*it).first.get() << " " << (*it).second.get() << endl;

    (*it).second.get() = "dad";

    splayTree.erase(9);

    for (const auto& p : splayTree) {
        cout << p.first.get() << " " << p.second.get() << endl;
    }*/


    /*BinarySearchTree<int> tree = { 40, 30, 50, 35, 32 };
    tree.print();
    cout << static_cast<int>(tree.height()) << endl;

    tree.erase(40);
    tree.erase(30);
    tree.print();
    cout << static_cast<int>(tree.height()) << endl;*/

    /*for (const int& el : tree.findInRange(2, 12)) {
        cout << el << " ";
    }*/
    /*tree.eraseRange(2, 10);
    tree.print();
    auto p = tree.split(6);

    p.first.print();
    cout << p.first.height() << endl;
    p.second.print();
    cout << p.second.height() << endl;*/

    //BinarySearchTree<int> nTree(BinarySearchTree<int>::merge(p.first, p.second));

    //nTree.print();

    //cout << nTree.height() << endl;

    return 0;
}