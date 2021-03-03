#include <iostream>
#include <clocale>
#include <string>
#include <ctime>
#include <cstdlib>

#define ALPHA 2

using namespace std;

struct StudentOfHogwarts {
  string facultyName;
  string wandType;
  int epmloymentLikelihood;
};

template <typename T>
class DynamicArray {
  private:
    T *m_array;
    size_t m_capacity;
    size_t m_length;

  public:
    T& operator[] (const size_t idx) {
      if (m_length <= idx) throw out_of_range("Index is bigger than a size of array");

      return m_array[idx];
    }

    DynamicArray() : m_length(0), m_capacity(1) {
      m_array = new T[m_capacity];
    }

    ~DynamicArray() {
      delete[] m_array;
    }

    void push(T el) {
      if (m_capacity <= m_length) {
        T *tmp = new T[m_capacity *= ALPHA];

        for (size_t i = 0; i < m_length; i++) {
          tmp[i] = m_array[i];
        }

        delete[] m_array;

        m_array = tmp;
      }

      m_array[m_length++] = el;
    }

    T pop() {
      if (!m_length) throw out_of_range("Array is empty");
      return m_array[--m_length];
    }

    void unshift(T el) {
      if (m_capacity <= m_length) {
        T *tmp = new T[m_capacity *= ALPHA];

        for (size_t i = 1; i <= m_length; i++) {
          tmp[i] = m_array[i - 1];
        }

        delete[] m_array;

        m_array = tmp;
      } else {
        for (size_t i = m_length; i ; ) {
          m_array[i] = m_array[--i];
        }
      }

      m_array[0] = el;
      m_length++;
    }

    T shift() {
      if (!m_length) throw out_of_range("Array is empty");

      T tmp = m_array[0];

      for (size_t i = 1; i < m_length; i++) {
        m_array[i - 1] = m_array[i];
      }

      m_length--;

      return tmp;
    }

    size_t getLength() {
      return m_length;
    }

    T getElem(size_t idx) {
      return m_array[idx];
    }

    void print() {
      for (size_t i = 0; i < m_length; i++) {
        cout << i + 1 << ") " << m_array[i] << endl;
      }
    }
};

template <typename T>
class LinkedList {
  private:
    struct Node {
      T value;
      Node *next = NULL;
      Node *prev = NULL;

      Node() : next(NULL), prev(NULL) {}
      Node(T v) : value(v), next(NULL), prev(NULL) {}
    };

    Node *m_head;
    Node *m_tail;
    size_t m_length;

  public:
    LinkedList() : m_length(0), m_head(NULL), m_tail(NULL) {}

    ~LinkedList() {
      for (Node *current = m_head; current != NULL; ) {
        Node *tmp = current;
        current = current->next;

        delete tmp;
      }
    }

    void pushBack(T value) {
      m_length++;

      if (m_tail == NULL) {
        m_tail = new Node(value);
        m_head = m_tail;

        return;
      }

      m_tail->next = new Node(value);
      m_tail->next->prev = m_tail;

      m_tail = m_tail->next;
    }

    void pushFront(T value) {
      m_length++;

      if (m_head == NULL) {
        m_head = new Node(value);
        m_tail = m_head;

        return;
      }

      m_head->prev = new Node(value);
      m_head->prev->next = m_head;

      m_head = m_head->prev;
    }

    T getElem(size_t idx) {
      if (m_length <= idx) throw "Index is bigger than a size of list";

      Node *current = m_head;
      for (; current.next != NULL; current = current.next);

      return current->value;
    }

    T popFront() {
      if (m_head == NULL) {
        throw "List is empty";
      }

      Node *tmp = m_head;
      T value = tmp->value;

      m_head = m_head->next;

      if (m_head != NULL) {
        m_head->prev = NULL;
      } else {
        m_tail = NULL;
      }

      delete tmp;
      return value;
    }

    T popBack() {
      Node *tmp = m_tail;
      T value = tmp->value;

      m_tail = m_tail->prev;
      m_tail->next = NULL;

      delete tmp;
      return value;
    }
};

int main() {
  setlocale(LC_ALL, "rus");
  srand(time(NULL));

  DynamicArray<int> arr;

  for (int i = 0; i < 200; i++) {
    arr.push(rand() % 1000);
  }

  arr.print();

  cout << arr.getLength();

  return 0;
}
