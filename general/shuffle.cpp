#include "shuffle.hpp"

#include "basic.hpp"
#include <cstdlib>

void shuffle(int *arr, int length) {
  for (int i = length - 1; i > 0; i--) {
    swapElements(arr, i, rand() % i);
  }
}
