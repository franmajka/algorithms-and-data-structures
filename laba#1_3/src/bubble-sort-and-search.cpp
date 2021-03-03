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
  cout << "������� ����� �������: ";
  cin >> length;

  if (length < 1) {
    cout << "������������ ����� �������";
    return 1;
  }

  int *arr = new int[length];

  fillWithRandom(arr, length);

  cout << "������ ��������� ����� �� -2000 �� 2000 ����� " << length << endl;
  printArr(arr, length);

  clock_t start = clock();
  quickInSort(arr, length, [](int a, int b) { return a < b; });
  float bubbleSortTime = (float)(clock() - start) / CLOCKS_PER_SEC;

  cout << "�������������� ������" << endl << "�� ��� ���������� ���� ��������� " << bubbleSortTime << " ������" << endl;
  printArr(arr, length);

  int element;
  int counter = 0;
  cout << "������� �������, ������ �������� �� ������� ������: ";
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
    cout << "�����������...";
  } else {
    cout
      << "������ ����� �������� " << linearIndex << endl
      << "��� ���� ��������� ����� ���������: �������� � ���������" << endl
      << "��� ������ " << linearTime << " ������ ��� ��������� ��������� ������" << endl
      << "� " << binaryTime << " ������ ��� ��������� ��������� ������ ��������������" << endl
      << "��� ������ ���� ��������� " << NUMBER_OF_TESTS << " ������";
  }

  delete[] arr;

  return 0;
}
