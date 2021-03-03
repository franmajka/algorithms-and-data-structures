#include <iostream>
#include <cmath>
#include <clocale>

using namespace std;

// �� ���� ��� � ����� ������� sin �������� ������� � �� �������
// �� ���� ������������� ���������� �� � ������� ����������� ��������� ����� ������� �� �� ������ ������ ������� ����
float convertToRadians(float angle) {
  return angle * M_PI / 180;
}

// � �� �� ����� ����� ����� �� ����� ����� �� ��������� x - y ��� ����� �� x �� �������� ���������� y
float evalExpression(float x, float y) {
  return (abs(sin(convertToRadians(x)) - y) + 2 * x) / sqrt(1 + abs(x * y));
}

int main() {
  setlocale(LC_ALL, "rus");

  cout << "������� ����� x, y ����� ������: ";

  float x = 0;
  float y = 0;

  cin >> x >> y;

  cout << evalExpression(x, y) << endl;

  return 0;
}
