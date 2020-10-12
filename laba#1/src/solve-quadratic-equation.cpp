#include <iostream>
#include <cmath>
#include <clocale>

using namespace std;

// ������ ���������� ���������
// ���������� ������ � ������� ������ �����
string solveQuadraticEquation(int a, int b, int c) {
  int discriminant = pow(b, 2) - 4 * a * c;

  if (discriminant > 0) {
    float x1 = (-b - sqrt(discriminant)) / (2 * a);
    float x2 = (-b + sqrt(discriminant)) / (2 * a);

    return "��������� ����� ��� �������\nx1 = " + to_string(x1) + "; x2 = " + to_string(x2);
  } else if (discriminant == 0) {
    return "��������� ����� ���� �������\nx = " + to_string(-b / (2 * a));
  } else {
    return "��������� �� ����� �������...";
  }
}

int main()
{
  setlocale(LC_ALL, "rus");

  cout << "������� ����� a, b � c ����� ������: ";

  int a = 0;
  int b = 0;
  int c = 0;

  cin >> a >> b >> c;

  cout << solveQuadraticEquation(a, b, c) << endl;

  return 0;
}
