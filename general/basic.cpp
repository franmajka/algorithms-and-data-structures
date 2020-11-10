#include "basic.hpp"

#include <iostream>

void swapElements(int *arr, int firstPos, int secondPos) {
  int tmp = arr[firstPos];
  arr[firstPos] = arr[secondPos];
  arr[secondPos] = tmp;
}

void printArr(int *arr, int length) {
  for (int i = 0; i < length; i++) {
    std::cout << arr[i] << " ";
  }

  std::cout << std::endl;
}
