#include <iostream>
#include <clocale>
#include <cmath>

using namespace std;

const int xStart = -3;
const int xEnd = 6;

int func(int x) {
  return pow(x, 3) - 2 * pow(x, 2) + x - 1;
}

int main()
{
  setlocale(LC_ALL, "rus");

  int maxY = func(xStart);

  for (int x = xStart + 1; x <= xEnd; x++) {
    int y = func(x);
    if (maxY < y) {
      maxY = y;
    }
  }

  cout << "Максимальное значение функции на заданом промежутке равно " << maxY;

  return 0;
}
