#include "basic.hpp"

void bubbleSort(int *arr, int length, bool (*compare)(int, int)) {
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

void shakerSort(int *arr, int length, bool (*compare)(int, int)) {
  bool sorted;
  int start = 0;
  int end = length;

  do {
    sorted = true;

    for (int i = start; i < end; i++) {
      if (compare(arr[i], arr[i + 1])) continue;

      sorted = false;
      swapElements(arr, i, i + 1);
    }

    if (sorted) break;

    end--;

    for (int i = end - 1; i > start; i--) {
      if (compare(arr[i - 1], arr[i])) continue;

      sorted = false;
      swapElements(arr, i - 1, i);
    }

    start++;

  } while(!sorted);
}

void selectionSort(int *arr, int length, bool (*compare)(int, int)) {
  int maxPos;

  for (int i = 0; i < length - 1; i++) {
    maxPos = i;
    for (int j = i + 1; j < length; j++) {
      if (compare(arr[maxPos], arr[j])) continue;

      maxPos = j;
    }

    if (maxPos != i) swapElements(arr, i, maxPos);
  }
}

void insertionSort(int *arr, int length, bool (*compare)(int, int)) {
  for (int i = 1; i < length; i++) {
    for (int j = i - 1; j >= 0; j--) {
      if (compare(arr[j], arr[j + 1])) break;
      swapElements(arr, j + 1, j);
    }
  }
}

void quickSort(int *arr, bool (*compare)(int, int), int start, int end) {
  if (end - start <= 1) return;

  int pi = start;

  for (int i = start + 1; i < end; i++) {
    if (compare(arr[pi], arr[i])) continue;

    for (int j = i; j > pi; j--) {
      swapElements(arr, j, j - 1);
    }
    pi++;
  }

  quickSort(arr, compare, start, pi);
  quickSort(arr, compare, pi + 1, end);
}

void quickInSort(int *arr, int length, bool (*compare)(int, int)) {
  quickSort(arr, compare, 0, length);
}
