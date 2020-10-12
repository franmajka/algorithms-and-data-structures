#include <iostream>
#include <cmath>
#include <clocale>

using namespace std;

// По тому что я понял функция sin принмает радианы а не градусы
// не имею представления существует ли в составе стандартных библиотек такая функция но на всякий случай написал свою
float convertToRadians(float angle) {
  return angle * M_PI / 180;
}

// Я не до конца понял нужно ли брать синус от выражения x - y или синус от x от которого отнимается y
float evalExpression(float x, float y) {
  return (abs(sin(convertToRadians(x)) - y) + 2 * x) / sqrt(1 + abs(x * y));
}

int main() {
  setlocale(LC_ALL, "rus");

  cout << "Введите числа x, y через пробел: ";

  float x = 0;
  float y = 0;

  cin >> x >> y;

  cout << evalExpression(x, y) << endl;

  return 0;
}
