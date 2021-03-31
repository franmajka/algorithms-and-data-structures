#include <queue>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <iterator>
#include <vector>
#include <functional>

#include "PriorityQueue.h"
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

    for (auto it = container.end() - 1; ; --it) {
        *it = heap.popTop();
        if (it == container.begin()) break;
    }
}

int main()
{
	srand(time(NULL));

    //int* arr = new int[10];
    vector<int> arr;
    for (int i = 0; i < 10; i++) {
        arr.push_back(rand() % 100);
        cout << arr[i] << " ";
    }
    cout << endl;

    heapSort(arr, greater<int>{});

    for (int i = 0; i < 10; i++) cout << arr[i] << " ";
	return 0;
}
