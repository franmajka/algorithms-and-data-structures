#include "searches.hpp"

int findBinary(int *arr, int length, int element) {
  int start = 0;
  int end = length;
  int mid;

  while (start < end) {
    mid = (start + end) / 2;

    if (arr[mid] < element) {
      start = mid + 1;
    } else {
      end = mid;
    }
  }

  return arr[start] == element ? start : -1;
}

int findLinear(int *arr, int length, int element) {
  int index = -1;
  for (int i = 0; i < length; i++) {
    if (arr[i] == element) {
      index = i;
      break;
    }
  }

  return index;
}
