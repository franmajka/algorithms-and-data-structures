#include <queue>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <iterator>
#include <vector>
#include <functional>
#include <clocale>

#include "PriorityQueue.h"
#include "Graph.h"
#include "HomeTask.h"

using namespace std;

template <typename T>
float testPriorityQueueSpeed(T&& priorityQueue)
{
    const int iters = 100000;

    clock_t timeStart = clock();
    for (int i = 0; i < iters; i++)
    {
        int insertDataAmount = rand() % 6 + 5;
        for (int j = 0; j < insertDataAmount; j++)
        {
            priorityQueue.push(HomeTask());
        }

        priorityQueue.top();
        priorityQueue.pop();
    }
    clock_t timeEnd = clock();
    float time = (float(timeEnd - timeStart)) / CLOCKS_PER_SEC;

    return time;
}

bool testPriorityQueue()
{
    srand(time(NULL));

    const int iters = 20000;

    PriorityQueue<HomeTask> myPriorQueue;
    priority_queue<HomeTask> stlPriorQueue;

    bool isDataEqual = true;
    for (int i = 0; i < iters; i++)
    {
        int insertDataAmount = rand() % 6 + 5;
        for (int j = 0; j < insertDataAmount; j++)
        {
            HomeTask randData = HomeTask();
            myPriorQueue.push(randData);
            stlPriorQueue.push(randData);
        }

        if (!(myPriorQueue.top() == stlPriorQueue.top()))
        {
            isDataEqual = false;
            cerr << "Comparing failed on iteration " << i << endl << endl;
            break;
        }

        int removeDataAmount = rand() % insertDataAmount;
        for (int j = 0; j < removeDataAmount; j++)
        {
            myPriorQueue.pop();
            stlPriorQueue.pop();
        }
    }

    int myQueueSize = myPriorQueue.size();
    int stlQueueSize = stlPriorQueue.size();

    float stlTime = testPriorityQueueSpeed<priority_queue<HomeTask>>(priority_queue<HomeTask>());
    float myTime = testPriorityQueueSpeed<PriorityQueue<HomeTask>>(PriorityQueue<HomeTask>());

    cout << "My PriorityQueue:" << endl;
    cout << "Time: " << myTime << ", size: " << myQueueSize << endl;
    cout << "STL priority_queue:" << endl;
    cout << "Time: " << stlTime << ", size: " << stlQueueSize << endl << endl;

    if (isDataEqual && myQueueSize == stlQueueSize)
    {
        cout << "The lab is completed" << endl << endl;
        return true;
    }

    cerr << ":(" << endl << endl;
    return false;
}

template <class T>
void heapSort(T* arr, int length) {
    Heap<T> heap;
    for (int i = 0; i < length; i++) heap.append(arr[i]);

    for (int i = length - 1; i >= 0; i--) arr[i] = heap.popTop();
}

template <
    class Container,
    class Comparator = less<typename Container::value_type>
>
void heapSort(Container& container, Comparator cmp = Comparator{}) {
    if (!container.size()) return;

    Heap<typename Container::value_type, Comparator> heap(container.begin(), container.end());

    for (auto it = prev(container.end()); ; --it) {
        *it = heap.popTop();
        if (it == container.begin()) break;
    }
}

template <class Iterator, class Comparator>
void quickSort(const Iterator& begin, const Iterator& end, Comparator comp) {
    if (distance(begin, end) <= 1) return;

    Iterator pi = prev(end);
    Iterator leftest = begin;

    for (Iterator it = begin; it != pi; ++it) {
        if (comp(*pi, *it)) continue;

        swap(*it, *leftest);
        ++leftest;
    }

    swap(*leftest, *pi);

    quickSort(begin, leftest, comp);
    quickSort(leftest + 1, end, comp);
}

void testSort() {
    const int iters = 1e6;
    vector<int> vec;

    cout << "Number of elements: " << iters << endl << endl;

    for (int i = 0; i < iters; i++) {
        vec.push_back(rand() % iters);
    }

    vector<int> standart = vec;

    clock_t start = clock();
    sort(standart.begin(), standart.end());
    float time = float(clock() - start) / CLOCKS_PER_SEC;

    cout << "std::sort: " << time << "s" << endl << endl;


    vector<int> copy = vec;

    start = clock();
    heapSort(copy);
    time = float(clock() - start) / CLOCKS_PER_SEC;

    cout << "heapSort: " << time << "s" << endl;
    if (standart == copy) cout << "They're absolutely the same" << endl << endl;
    else cout << ":(" << endl << endl;


    copy = vec;

    start = clock();
    quickSort(copy.begin(), copy.end(), less<int>{});
    time = float(clock() - start) / CLOCKS_PER_SEC;

    cout << "quickSort: " << time << "s" << endl;
    if (standart == copy) cout << "They're absolutely the same" << endl << endl;
    else cout << ":(" << endl << endl;
}

void testDijkstra() {
    Graph<int> g = {
        {0, {1, 4}},
        {0, {7, 8}},
        {1, {2, 8}},
        {1, {7, 11}},
        {2, {3, 7}},
        {2, {8, 2}},
        {2, {5, 4}},
        {3, {4, 9}},
        {3, {5, 14}},
        {4, {5, 10}},
        {5, {6, 2}},
        {6, {7, 1}},
        {6, {8, 6}},
        {7, {8, 7}},
    };

    for (const pair<int, int>& p : g.shortestPath(0)) {
        cout << p.first << " — " << p.second << endl;
    }
}

int main()
{
    setlocale(LC_ALL, "rus");
	srand(time(NULL));

    testPriorityQueue();

	return 0;
}
