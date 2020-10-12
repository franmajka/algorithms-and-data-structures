#include <iostream>
#include <clocale>
#include <cstdlib>
#include <time.h>

using namespace std;

const int SEQUENCE_ARRAY_LENGTH = 40;
const int NUMBERS_POOL_LENGTH = 5;

void countEntries(int arr[], int arrayLength) {
  int entries[NUMBERS_POOL_LENGTH];

  for (int i = 0; i < NUMBERS_POOL_LENGTH; i++) {
    entries[i] = 0;
  }

  for (int i = 0; i < arrayLength; i++) {
    entries[arr[i]]++;
  }

  for (int i = 0; i < NUMBERS_POOL_LENGTH; i++) {
    cout << "Выборка содержит " << entries[i] << " чисел " << i << endl;
  }
}

int main() {
  setlocale(LC_ALL, "rus");

  srand(time(NULL));

  int seq[SEQUENCE_ARRAY_LENGTH];
  for (int i = 0; i < SEQUENCE_ARRAY_LENGTH; i++) {
    seq[i] = rand() % NUMBERS_POOL_LENGTH;
  }

  countEntries(seq, SEQUENCE_ARRAY_LENGTH);
  return 0;
}
