#include <iostream>
#include <clocale>
#include <cmath>

using namespace std;

// Принамет первым аргументом указатель на число а от которого берется цифра и вторым индекс цифры начиная с конца
// Модифицирует изначальное число а
// Возвращет цифру
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

  cout << "Введите целое число а: ";
  cin >> a;

  cout << "Введите натуральное число, которое обозначает основание системы счисления числа a: ";
  cin >> fromBase;

  cout << "Введите натуральное число, которое обозначает основание системы счисления, в которую вы желаете конвертировать число a: ";
  cin >> toBase;

  if (fromBase < 2 || toBase < 2 || fromBase > 10 || toBase > 10) {
    cout << "Некоректное основание системы счисления";
    return 1;
  }


  cout << "Число " << a << " в " << fromBase << "-ричной системе счисления равно числу "
    << convertBase(a, fromBase, toBase) << " в " << toBase << "-ричной системе";

  return 0;
}
