#include <cstdlib>
#include <ctime>
#include <iostream>

#define N 5

using namespace std;

template <typename T>
struct SquareMatrix {
  T **arr;
  int size;

  SquareMatrix(int size_) {
    size = size_;
    arr = new T*[size];
    for (int i = 0; i < size; i++) {
      arr[i] = new T[size];
      for (int j = 0; j < size; j++) {
        arr[i][j] = rand() % 101;
      }
    }
  }

  ~SquareMatrix() {
    for (int i = 0; i < size; i++) {
      delete[] arr[i];
    }

    delete[] arr;
  }

  void print() {
    printf("\n");

    for (int i = 0; i < size; i++) {
      for (int j = 0; j < size; j++) {
        printf("%3d\t", arr[i][j]);
      }
      printf("\n");
    }

    printf("\n");
  }
};


int main() {
  srand(time(NULL));

  SquareMatrix<int> *matr = new SquareMatrix<int>(N);

  matr->print();

  int sum = 0;
  for (int k = 0; k < matr->size; k++) {
    int max = matr->arr[0][0];

    for (int i = 0; i < matr->size; i++) {
      for (int j = 0; j <= k; j++) {
        if (max < matr->arr[i][j]) {
          max = matr->arr[i][j];
        }
      }
    }

    sum += max;
  }

  cout << sum;

  delete matr;

  return 0;
}
