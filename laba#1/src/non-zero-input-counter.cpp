// � ����� ������� ���� ���������
// ��������� ���������� ��������� ������ ���� ������ ������ ������ 0
// �� ���� ������ ����� ��������� ������� �������������� � 0 ��� ������ � ��� ���������� ����������

#include <iostream>
#include <clocale>

using namespace std;

// ������� �� ������ �������� ����� ����� ��-�� ����������� �� ����������...
// �� � � ������ �� ���� ����� ������� �����...
void cleanInput(char current) {
  while (current != '\n') {
    current = (char)cin.get();
  }
}

int main() {
  setlocale(LC_ALL, "rus");

  char cond;
  int counter = 0;

  cout << "�������� ������ 0. ��� ������ ���� ���� ���� � ������ ����� ����. " <<
    "��������� ������� ���� ����������� ��� ����� �������." << endl;

  while (true) {
    if (cond) {
      cout << "��� �� �� ��� � ���� ������. �������� ��� ���. �� ����������." << endl;
    }

    counter++;
    cond = (char)cin.get();

    if (cond == '0' && (char)cin.get() == '\n') {
      break;
    } else if (cond == '\n') {
      continue;
    }

    fflush(stdin);
  };

  cout << "� ���� ����������. ���������� �������: " << counter << endl;

  return 0;
}
