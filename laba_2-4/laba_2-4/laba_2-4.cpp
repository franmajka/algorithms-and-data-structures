#include <set>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <fstream>

#include "BinarySearchTree.h"
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

int main()
{
    srand(time(NULL));
    //testBinarySearchTree();
    testTrie();

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