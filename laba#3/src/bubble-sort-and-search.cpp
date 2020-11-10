#include <iostream>
#include <clocale>
#include <ctime>
#include <cstdlib>
#include <cmath>

#include "basic.hpp"
#include "sorts.hpp"
#include "searches.hpp"

#define NUMBER_OF_TESTS 100000

using namespace std;

void fillWithRandom(int *arr, int length) {
  for (int i = 0; i < length; i++) {
    arr[i] = rand() % 4001 - 2000;
  }
}

int main() {
  setlocale(LC_ALL, "rus");
  srand(time(NULL));

  int length;
  cout << "Введите длину массива: ";
  cin >> length;

  if (length < 1) {
    cout << "Некорректная длина массива";
    return 1;
  }

  int *arr = new int[length];

  fillWithRandom(arr, length);

  cout << "Массив случайных чисел от -2000 до 2000 длины " << length << endl;
  printArr(arr, length);

  clock_t start = clock();
  quickInSort(arr, length, [](int a, int b) { return a < b; });
  float bubbleSortTime = (float)(clock() - start) / CLOCKS_PER_SEC;

  cout << "Отсортированый массив" << endl << "На его сортировку было потрачено " << bubbleSortTime << " секунд" << endl;
  printArr(arr, length);

  int element;
  int counter = 0;
  cout << "Введите элемент, индекс которого вы желаете узнать: ";
  cin >> element;

  int linearIndex;
  start = clock();
  for (int i = 0; i < NUMBER_OF_TESTS; i++) {
    // element = rand() % 4001 - 2000;
    linearIndex = findLinear(arr, length, element);
    if (~linearIndex) counter++;
  }
  float linearTime = (float)(clock() - start) / CLOCKS_PER_SEC;
  cout << counter << endl;

  counter = 0;
  int binaryIndex;
  start = clock();
  for (int i = 0; i < NUMBER_OF_TESTS; i++) {
    // element = rand() % 4001 - 2000;
    binaryIndex = findBinary(arr, length, element);
    if (~binaryIndex) counter++;
  }
  float binaryTime = (float)(clock() - start) / CLOCKS_PER_SEC;
  cout << counter << endl;

  if (linearIndex != binaryIndex) {
    cout << "Впечатляюще...";
  } else {
    cout
      << "Индекс этого элемента " << linearIndex << endl
      << "Это было проверено двумя способами: линейным и бинарными" << endl
      << "Это заняло " << linearTime << " секунд для линейного алгоритма поиска" << endl
      << "И " << binaryTime << " секунд для бинарного алгоритма поиска соответственно" << endl
      << "Для поиска было проведено " << NUMBER_OF_TESTS << " тестов";
  }

  delete[] arr;

  return 0;
}
