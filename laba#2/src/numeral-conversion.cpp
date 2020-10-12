#include <iostream>
#include <clocale>
#include <cmath>
#include <string>

using namespace std;

const int NUMS_ARRAY_LENGTH = 36;
const char NUMS_ARRAY[36] = {
  '0', '1', '2', '3', '4', '5', '6', '7', '8',
  '9', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h',
  'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q',
  'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
};

int getValueOfNumeral(char num) {
  for (int i = 0; i < NUMS_ARRAY_LENGTH; i++) {
    if (NUMS_ARRAY[i] == num) {
      return i;
    }
  }

  // ��� ��� ��-�������� �������� �� ���������...
  return 0;
}

string reverse(string str) {
  string reversed = "";
  for (int i = str.length() - 1; i >= 0; i--) {
    reversed += str[i];
  }
  return reversed;
}

string convertBase(string a, unsigned short int fromBase, unsigned short int toBase) {
  if (fromBase == toBase) {
    return a;
  }

  // ������������ � ����������
  a = reverse(a);
  unsigned int aDecimial = 0;
  for (int i = 0; i < a.length(); i++) {
    aDecimial += getValueOfNumeral(a[i]) * pow(fromBase, i);
  }

  string converted = "";
  while (aDecimial) {
    converted += NUMS_ARRAY[aDecimial % toBase];
    aDecimial /= toBase;
  }

  return reverse(converted);
}

int main() {
  setlocale(LC_ALL, "rus");

  string a;
  unsigned short int fromBase;
  unsigned short int toBase;

  cout << "������� ����� ����� �: ";
  cin >> a;

  cout << "������� ����������� �����, ������� ���������� ��������� ������� ��������� ����� a: ";
  cin >> fromBase;

  cout << "������� ����������� �����, ������� ���������� ��������� ������� ���������, � ������� �� ������� �������������� ����� a: ";
  cin >> toBase;

  if (fromBase == 0 || toBase == 0 || fromBase > NUMS_ARRAY_LENGTH || toBase > NUMS_ARRAY_LENGTH) {
    cout << "����������� ��������� ������� ���������";
    return 1;
  }

  cout << "����� " << a << " � " << fromBase << "-������ ������� ��������� ����� ����� " <<
    convertBase(a, fromBase, toBase) << " � " << toBase << "-������ �������";

  return 0;
}
