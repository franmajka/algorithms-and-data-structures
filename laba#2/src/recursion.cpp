#include <iostream>
#include <clocale>

using namespace std;

// ѕринимает целое число а и натуральное b
int recursivePow(int a, unsigned int b) {
  if (b == 0) {
    return 1;
  }
  return b == 1 ? a : recursivePow(a, b - 1) * a;
}

int main() {
  setlocale(LC_ALL, "rus");

  int a;
  unsigned int b;

  cout << "¬ведите целое число a и натуральное b через пробел: ";
  cin >> a >> b;

  cout << a << "^" << b << " = " << recursivePow(a, b);

  return 0;
}
