#include <iostream>
#include <clocale>
#include <ctime>
#include <cstdlib>

using namespace std;

void fillWithRandom(int *arr, int &length) {
  for (int i = 0; i < length; i++) {
    arr[i] = rand() % 4001 - 2000;
  }
}

void printArr(int *arr, int &length) {
  for (int i = 0; i < length; i++) {
    cout << arr[i] << " ";
  }

  cout << endl;
}

void swapElements(int *arr, int firstPos, int secondPos) {
  int tmp = arr[firstPos];
  arr[firstPos] = arr[secondPos];
  arr[secondPos] = tmp;
}

void bubbleSort(int *arr, int &length, bool (*compare)(int, int)) {
  bool sorted;
  int counter = 1;
  do {
    sorted = true;
    for (int i = 0; i < length - counter; i++) {
      if (compare(arr[i], arr[i + 1])) continue;

      sorted = false;
      swapElements(arr, i, i + 1);
    }

    counter++;
  } while (!sorted && length - counter > 0);
}

bool compare(int a, int b) {
  return a < b;
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
  printArr(arr, length);

  bubbleSort(arr, length, compare);
  printArr(arr, length);

  delete[] arr;

  return 0;
}
