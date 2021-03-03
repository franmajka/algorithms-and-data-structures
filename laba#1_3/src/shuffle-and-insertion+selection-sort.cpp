#include <iostream>
#include <ctime>
#include <cstdlib>
#include <clocale>
#include <cmath>

#include "basic.hpp"
#include "sorts.hpp"
#include "shuffle.hpp"

using namespace std;

int getFirstDigit(int n) {
  return n / round(pow(10, (int)log10(n)));
}

bool compare(int a, int b) {
  int firstDigitA = getFirstDigit(a);
  int firstDigitB = getFirstDigit(b);
  if (firstDigitA == firstDigitB) {
    return a < b;
  }
  return firstDigitA < firstDigitB;
}

int main() {
  srand(time(NULL));
  setlocale(LC_ALL, "rus");

  int length;
  cout << "Введите длину массива: ";
  cin >> length;

  if (length < 1) {
    cout << "Некорректная длина массива";
    return 1;
  }

  int *arr = new int[length];
  for (int i = 0; i < length; i++) {
    arr[i] = i + 1;
  }

  cout << "Полученный массив" << endl;
  printArr(arr, length);

  shuffle(arr, length);
  cout << "Перетасованный массив" << endl;
  printArr(arr, length);

  selectionSort(arr, length, compare);
  cout << "Отсортированный массив по возрастанию первой цифры" << endl;
  printArr(arr, length);

  delete[] arr;

  return 0;
}
