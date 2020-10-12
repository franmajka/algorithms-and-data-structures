// В целом задумка была следующая
// Прерывать выполнение программы только если введен единый символ 0
// Во всех других фолси значениях которые конвертируются в 0 при записи в инт продолжать выполнение

#include <iostream>
#include <clocale>

using namespace std;

// Костыль тк нельзя очистить буфер ввода из-за ограничения на библиотеки...
// Ну и я просто не смог найти решения лучше...
void cleanInput(char current) {
  while (current != '\n') {
    current = (char)cin.get();
  }
}

int main() {
  setlocale(LC_ALL, "rus");

  char cond;
  int counter = 0;

  cout << "Попробуй ввести 0. Это должен быть один ноль и ничего кроме него. " <<
    "Посмотрим сколько тебе понадобится для этого попыток." << endl;

  while (true) {
    if (cond) {
      cout << "Это не то что я хочу видеть. Попробуй ещё раз. Ты справишься." << endl;
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

  cout << "У тебя получилось. Количество попыток: " << counter << endl;

  return 0;
}
