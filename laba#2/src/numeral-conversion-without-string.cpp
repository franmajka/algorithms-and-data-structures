#include <iostream>
#include <clocale>
#include <cmath>

using namespace std;

// �������� ������ ���������� ��������� �� ����� � �� �������� ������� ����� � ������ ������ ����� ������� � �����
// ������������ ����������� ����� �
// ��������� �����
int popDigit(int &a, int index) {
  int power = round(pow(10, index));
  int digit = a % power;
  a -= digit;

  digit *= 10. / power;

  return digit;
}

int convertToDecimal(int a, int fromBase) {
  int i = 0;
  int converted = 0;
  int digit;

  while (a) {
    digit = popDigit(a, i + 1);
    converted += digit * round(pow(fromBase, i));

    i++;
  }

  return converted;
}

int convertBase(int a, int fromBase, int toBase) {
  if (fromBase == toBase) {
    return a;
  }

  int converted = 0;
  int i = 0;

  while (a) {
    converted += (a % toBase) * round(pow(fromBase, i));
    a /= toBase;

    i++;
  }

  return converted;
}

int main() {
  setlocale(LC_ALL, "rus");

  int a;
  unsigned short int fromBase;
  unsigned short int toBase;

  cout << "������� ����� ����� �: ";
  cin >> a;

  cout << "������� ����������� �����, ������� ���������� ��������� ������� ��������� ����� a: ";
  cin >> fromBase;

  cout << "������� ����������� �����, ������� ���������� ��������� ������� ���������, � ������� �� ������� �������������� ����� a: ";
  cin >> toBase;

  if (fromBase < 2 || toBase < 2 || fromBase > 10 || toBase > 10) {
    cout << "����������� ��������� ������� ���������";
    return 1;
  }


  cout << "����� " << a << " � " << fromBase << "-������ ������� ��������� ����� ����� "
    << convertBase(a, fromBase, toBase) << " � " << toBase << "-������ �������";

  return 0;
}
