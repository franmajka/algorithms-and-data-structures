#include <iostream>
#include <clocale>
#include <ctime>
#include <cstdlib>

#include "basic.hpp"
#include "shuffle.hpp"
#include "sorts.hpp"

#define NUMBER_OF_TESTS 1
#define LENGTH 20000

using namespace std;

void bench(int *arr, int length, const char *name, void (*sort)(int*, int, bool (*)(int, int))) {
  double averageSortTime = 0;
  clock_t start;
  for(int _ = 0; _ < NUMBER_OF_TESTS; _++) {
    shuffle(arr, length);
    start = clock();
    sort(arr, length, [](int a, int b) { return a < b; });
    averageSortTime += (double)(clock() - start);
  }
  averageSortTime /= CLOCKS_PER_SEC * NUMBER_OF_TESTS;

  cout << name << " Ч " << averageSortTime << " с." << endl;
}

int main() {
  setlocale(LC_ALL, "rus");

  int arr[LENGTH];
  for (int i = 0; i < LENGTH; i++) {
    arr[i] = i + 1;
  }

  bench(arr, LENGTH, "Bubble sort", bubbleSort);
  bench(arr, LENGTH, "Shaker sort", shakerSort);
  bench(arr, LENGTH, "Insertion sort", insertionSort);
  bench(arr, LENGTH, "Selection sort", selectionSort);
  bench(arr, LENGTH, "Quick sort", quickInSort);

  cout << "ƒлина массива Ч " << LENGTH << endl << " оличество тестов Ч " << NUMBER_OF_TESTS << endl;

  return 0;
}
