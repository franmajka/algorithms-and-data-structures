#include <iostream>
#include <string>
#include <cstdlib>

#define STACK_SIZE 6

#define NUMBER_WIDTH 3
#define TITLE_WIDTH 40
#define NUMBER_OF_PAGES_WIDTH 10
#define AUTHOR_WIDTH 30

using namespace std;

enum Errors {
  BAD_FORMAT,
  STACK_UNDERFLOW,
  STACK_OVERFLOW,
};

enum Actions {
  EXIT = -1,
  STACK_ACTIONS,
  BOOK_ACTIONS,
  ADDING_BOOK,
};

template <typename T>
struct ArrayWithLength {
  T *arr;
  size_t length;

  ArrayWithLength(size_t length_) {
    length = length_;
    arr = new T[length_];
  }

  ~ArrayWithLength() {
    delete[] arr;
  }
};

template <typename T>
void realloc(ArrayWithLength<T> *arrS, int change) {
  int length = change < 0 ? arrS->length + change : arrS->length;
  if (length < 0) throw out_of_range("����� ����� ������� ������ 0");

  T *newStrArr = new T[arrS->length + change];

  for (int i = 0; i < length; i++) {
    newStrArr[i] = arrS->arr[i];
  }

  delete[] arrS->arr;
  arrS->arr = newStrArr;
  arrS->length += change;
}

// ������� ������� ������ � �����
void strTrim(string &str, char c = ' ') {
  while (str[0] == c) {
    str.erase(0, 1);
  }

  size_t length = str.length();
  while (length && str[length - 1] == c) {
    str.erase(length - 1, length);
    length = str.length();
  }
}

// ��������� ������ � ���������
// ���������� ������ � ������, ��������� �� ��������, �� ������� ���� �������� ����������� ������ ������������
ArrayWithLength<string>* strSplit(string str, string delimiter = " ") {
  ArrayWithLength<string> *arrS = new ArrayWithLength<string>(1);
  size_t pos;
  string tmp;

  while ((pos = str.find(delimiter)) != string::npos) {
    tmp = str.substr(0, pos);
    str.erase(0, pos + delimiter.length());
    arrS->arr[arrS->length - 1] = tmp;
    realloc(arrS, 1);
  }

  arrS->arr[arrS->length - 1] = str;
  return arrS;
}

struct Book {
  string title;
  int numberOfPages;
  string author;

  // ��������� ������ � ������� "� | �� | �"
  // � ������ ����� ��������� ������ �������� BAD_FORMAT
  Book(string input) {
    ArrayWithLength<string> *arrS = strSplit(input, "|");

    if (arrS->length != 3) {
      delete arrS;
      throw BAD_FORMAT;
    }

    for (size_t i = 0; i < arrS->length; i++) {
      strTrim(arrS->arr[i], ' ');
    }

    title = arrS->arr[0];

    try {
      numberOfPages = stoi(arrS->arr[1]);

      if (numberOfPages <= 0) throw out_of_range("�� ������������� �������� �������");

    } catch (...) {
      delete arrS;
      throw BAD_FORMAT;
    }

    author = arrS->arr[2];

    delete arrS;
  }

  ~Book() {
    // �� ����������� ��� ��� �������...
    // �� ���� ��������� ��������� ����������� � � ������� �� ������� �� ������� ������ ���-��
  }
};

void printBook(Book *book) {
  cout << "��������: " << book->title << endl << "���������� �������: " << book->numberOfPages << endl << "�����: " << book->author << endl;
}

template <typename T>
struct Stack {
  T **arr;
  size_t size;
  int topIndex = -1;

  Stack() {
    size = STACK_SIZE;
    arr = new T*[STACK_SIZE];
  }

  Stack(size_t size_) {
    size = size_;
    arr = new T*[size_];
  }

  ~Stack() {
    for (int i = 0; i <= topIndex; i++) {
      delete arr[i];
    }

    delete[] arr;
  }
};

template <typename T>
bool isEmpty(Stack<T> *stack) {
  return stack->topIndex == -1;
}

template <typename T>
size_t getSize(Stack<T> *stack) {
  return stack->topIndex + 1;
}

template <typename T>
T* getTop(Stack<T> *stack) {
  if (isEmpty(stack)) {
    throw STACK_UNDERFLOW;
  }

  return stack->arr[stack->topIndex];
}

// ���������� �������, ��� ��� ������, � ������ ���� ��� �������� � ����������� ������ � ��������� �������.
// ��������� �������� topIndex �� 1.
template <typename T>
T* pop(Stack<T> *stack) {
  if (isEmpty(stack)) {
    throw STACK_UNDERFLOW;
  }

  T *el = stack->arr[stack->topIndex];
  stack->arr[stack->topIndex] = NULL;
  stack->topIndex--;

  return el;
}

// ���������� ������ ������������ �������� � ������ ���� ��� ������� �������� ����� ����������� ������
// ����������� �������� topIndex �� 1
template <typename T>
int push(Stack<T> *stack, T *el) {
  if (stack->topIndex >= (int)stack->size - 1) {
    throw STACK_OVERFLOW;
  }

  stack->arr[++stack->topIndex] = el;
  return stack->topIndex;
}

// ��������� ������ �� ����� n ����������� ���������� ������ n ���
string operator *(const string &str, const size_t &times) {
  string res = "";
  for (size_t i = 0; i < times; i++) {
    res += str;
  }

  return res;
}

// ������������ ����� � �������
string operator +(const string &str, const char &c) {
  return str + string(1, c);
}

string operator +(const char &c, const string &str) {
  return string(1, c) + str;
}

// �������� ������ �� ������������ ����� � ������� � �������. ����������� �� ������� ����.
// ���� ������ ������ ������������ ����� �� �������� �
void outputFormatted(string str, size_t maxChars) {
  cout.width(maxChars);

  if (str.length() > maxChars) {
    str = str.substr(0, maxChars - 3) + "...";
  }

  cout << right << str;
}

void printTable(Stack<Book> *stack) {
  if (isEmpty(stack)) {
    cout << "������ ���� ������..." << endl;
    return;
  }

  const string TABLE_PARTS = "�|";
  const string SPACE = " ";

  string blankLine = TABLE_PARTS[1] + SPACE * (1 + NUMBER_WIDTH + 1) + TABLE_PARTS[1] + SPACE * (1 + TITLE_WIDTH + 1)
    + TABLE_PARTS[1] + SPACE * (1 + NUMBER_OF_PAGES_WIDTH + 1) + TABLE_PARTS[1] + SPACE * (1 + AUTHOR_WIDTH + 1) + TABLE_PARTS[1] + '\n';
  string dividingLine = string(1, TABLE_PARTS[0]) * (2 + NUMBER_WIDTH + 3 + TITLE_WIDTH + 3 + NUMBER_OF_PAGES_WIDTH + 3 + AUTHOR_WIDTH + 2) + '\n';

  cout << dividingLine << blankLine;

  cout << TABLE_PARTS[1] << SPACE;
  outputFormatted(string("�"), NUMBER_WIDTH);
  cout << SPACE << TABLE_PARTS[1] << SPACE;
  outputFormatted(string("��������"), TITLE_WIDTH);
  cout << SPACE << TABLE_PARTS[1] << SPACE;
  outputFormatted(string("�-�� ���"), NUMBER_OF_PAGES_WIDTH);
  cout << SPACE << TABLE_PARTS[1] << SPACE;
  outputFormatted(string("�����"), AUTHOR_WIDTH);
  cout << SPACE << TABLE_PARTS[1] << endl;

  cout << blankLine << dividingLine;

  for (int i = getSize(stack) - 1; i >= 0; i--) {
    cout << blankLine;

    cout << TABLE_PARTS[1] << SPACE;
    outputFormatted(to_string(getSize(stack) - i), NUMBER_WIDTH);
    cout << SPACE << TABLE_PARTS[1] << SPACE;
    outputFormatted(stack->arr[i]->title, TITLE_WIDTH);
    cout << SPACE << TABLE_PARTS[1] << SPACE;
    outputFormatted(to_string(stack->arr[i]->numberOfPages), NUMBER_OF_PAGES_WIDTH);
    cout << SPACE << TABLE_PARTS[1] << SPACE;
    outputFormatted(stack->arr[i]->author, AUTHOR_WIDTH);
    cout << SPACE << TABLE_PARTS[1] << endl;

    cout << blankLine << dividingLine;
  }
}

void clearInput() {
  cin.clear();
  while ((char)cin.get() != '\n');
}

int inputDigit() {
  char c = cin.get();
  if ((int)c > 47 && (int)c < 58 && (char)cin.get() == '\n') {
    return c - '0';
  }

  clearInput();
  return -1;
}

void stackActionsLoop(Stack<Book> *stack) {
  bool stop = false;
  int currentAction = STACK_ACTIONS;
  Book *currentBook = NULL;

  while (!stop) {
    switch (currentAction) {
      case STACK_ACTIONS:
        cout << "������� �����. �������� ��������:" << endl << "1. ������� �������" << endl
          << "2. ����� �����" << endl << "3. �������� �����" << endl << "4. �����" << endl << endl;

        switch (inputDigit()) {
          // 1. ������� �������
          case 1:
            cout << endl;
            printTable(stack);
            break;

          // 2. ����� �����
          case 2:
            try {
              currentBook = pop(stack);
            } catch (Errors &e) {
              if (e == STACK_UNDERFLOW){
                cout << endl << "������ ���� ������..." << endl;
              }

              break;
            }

            currentAction = BOOK_ACTIONS;
            break;

          // 3. �������� �����
          case 3:
            currentAction = ADDING_BOOK;
            break;

          // 4. �����
          case 4:
            currentAction = EXIT;
            break;

        default:
          cout << endl << "������������ ����" << endl;
        }
        break;

      case BOOK_ACTIONS:
        cout << "� ����� ����� �����. �������� ��������:" << endl << "1. ���������" << endl
          << "2. �������� �����" << endl << "3. ������� �����" << endl << "4. ��������� �����" << endl << endl;

        switch (inputDigit()) {

          // 1. ���������
          case 1:
            cout << endl;
            printBook(currentBook);
            break;

          // 2. �������� �����
          case 2:
            cout << endl << "������� �����, ������� �������� �� �������� ��� �� ������ ��������. ��������:" << endl
              << "1. ��������" << endl << "2. ���������� �������" << endl << "3. �����" << endl << endl;

            switch (inputDigit()) {
              // 1. �������� ��������
              case 1:
                cout << endl << "������� ����� �������� �����. �������: " << currentBook->title << endl;
                getline(cin, currentBook->title);

                cout << endl << "�� �������� �������� �����.";

                break;

              // 3. �������� ������
              case 3:
                cout << endl << "������� ��� ������ ������ �����. �������: " << currentBook->author << endl;
                getline(cin, currentBook->author);

                cout << endl << "�� �������� ������ �����.";

                break;

              // 2. �������� ���������� �������
              // 2 � 3 ����� � ���� �������� ������� ��� ���� ����� ����� ���� �������� ����� ���� �� default ��� ������������ �����
              case 2: {
                int originalNumberOfPages = currentBook->numberOfPages;
                cout << endl << "������� ����� ���������� ������� �����. �������: " << originalNumberOfPages << endl;
                cin >> currentBook->numberOfPages;

                clearInput();

                if (currentBook->numberOfPages > 0) {
                  cout << endl << "�� �������� ���������� �������";
                  break;
                }

                currentBook->numberOfPages = originalNumberOfPages;
              }

              default:
                cout << endl << "������������ ����";
            }
            cout << endl;
            break;

          // 3. ������� �����
          case 3:
            push(stack, currentBook);
            currentBook = NULL;
            currentAction = STACK_ACTIONS;
            break;

          // 4. ��������� �����
          case 4:
            delete currentBook;
            currentBook = NULL;
            currentAction = STACK_ACTIONS;
            break;

          default:
            cout << endl << "������������ ����" << endl;
        }

        break;

      case ADDING_BOOK: {
        string input;
        cout << "������� ��������, ���������� ������� � ������ � ������� \"� | �� | �\"" << endl;
        getline(cin, input);

        Book *tmpBook;
        try {
          tmpBook = new Book(input);
          push(stack, tmpBook);

          cout << endl << "����� ���������" << endl;
        } catch (Errors &e) {
          switch (e) {
            case BAD_FORMAT:
              cout << endl << "������������ ����" << endl;
              break;

            case STACK_OVERFLOW:
              delete tmpBook;
              cout << endl << "������ �����������" << endl;
              break;
          }
        }

        currentAction = STACK_ACTIONS;
        break;
      }

      case EXIT:
        stop = true;
        break;

      default:
        cout << "�� ��..." << endl;
        stop = true;
    }

    cout << endl;
  }
}

int main() {
  system("chcp 1251");

  size_t size;
  bool cond;
  Stack<Book> *stack;

  do {
    cond = false;

    try {
      cout << "������� ������ ������ ����: ";
      cin >> size;
      clearInput();

      if (!size) throw bad_array_new_length();

      stack = new Stack<Book>(size);
    } catch (bad_array_new_length) {
      cond = true;
      cout << "������������ ������ ������" << endl;
    }

    cout << endl;

  } while (cond);

  stackActionsLoop(stack);

  delete stack;

  return 0;
}
