#include <iostream>
#include <clocale>
#include <string>

#define SIZE_OF_QUEUE 5

using namespace std;

enum QueueErrors {
  QUEUE_UNDERFLOW,
  QUEUE_OVERFLOW,
};

struct Product {
  string name;
  float price;
  int expirationDate;
};

ostream& operator<< (ostream &out, const Product &product) {
  out << "Название: " << product.name << endl << "Цена: " << product.price
    << endl << "Срок годности: " << product.expirationDate;

  return out;
}

template <typename T>
struct Queue {
  T arr[SIZE_OF_QUEUE];
  int size = SIZE_OF_QUEUE;
  int head = -1;
  int tail = -1;
};

template <typename T>
bool isEmpty(Queue<T> *queue) {
  return queue->head == -1;
}

template <typename T>
int getSize(Queue<T> *queue) {
  if (isEmpty(queue)) return 0;

  if (queue->tail < queue->head) {
    return queue->size - queue->head + queue->tail + 1;
  }

  return queue->tail - queue->head + 1;
}

template <typename T>
T front(Queue<T> *queue) {
  if (isEmpty(queue)) {
    throw QUEUE_UNDERFLOW;
  }

  return queue->arr[queue->head];
}

template <typename T>
void push(Queue<T> *queue, T el) {
  if ((queue->tail + 1) % queue->size == queue->head) {
    throw QUEUE_OVERFLOW;
  }

  queue->tail = (queue->tail + 1) % queue->size;
  queue->arr[queue->tail] = el;

  if (isEmpty(queue)) queue->head++;
}

template <typename T>
T pop(Queue<T> *queue) {
  if (isEmpty(queue)) {
    throw QUEUE_UNDERFLOW;
  }

  if (queue->head == queue->tail) {
    T tmp = queue->arr[queue->head];

    queue->head = -1;
    queue->tail = -1;

    return tmp;
  }

  T tmp = queue->arr[queue->head];
  queue->head = (queue->head + 1) % queue->size;

  return tmp;
}

template <typename T>
T last(Queue<T> *queue) {
  if (isEmpty(queue)) {
    throw QUEUE_UNDERFLOW;
  }

  return queue->arr[queue->tail];
}


int main() {
  setlocale(LC_ALL, "rus");

  Queue<Product> tape;

  try {
    push(&tape, Product {"Масло 100г", 20, 20});
    cout << "Добавлен продукт:" << endl << last(&tape) << endl << endl;

    push(&tape, Product {"Гречка 1кг", 19.99, 365});
    cout << "Добавлен продукт:" << endl << last(&tape) << endl << endl;

    push(&tape, Product {"Хлеб", 18.99, 14});
    cout << "Добавлен продукт:" << endl << last(&tape) << endl << endl;

    push(&tape, Product {"Рис длинный 1кг", 23.99, 365});
    cout << "Добавлен продукт:" << endl << last(&tape) << endl << endl;
  } catch (QueueErrors e) {
    if (e != QUEUE_OVERFLOW) throw e;

    cout << "Очередь переполнена" << endl << endl;
  }

  Product tmp = pop(&tape);
  tmp.price *= .75;
  push(&tape, tmp);

  try {
    push(&tape, Product {"Бананы 1кг", 100, 14});
    cout << "Добавлен продукт:" << endl << last(&tape) << endl << endl;

    push(&tape, Product {"Апельсины 10кг", 600, 14});
    cout << "Добавлен продукт:" << endl << last(&tape) << endl << endl;

    push(&tape, Product {"Лимон 100г", 14, 14});
    cout << "Добавлен продукт:" << endl << last(&tape) << endl << endl;
  } catch (QueueErrors e) {
    if (e != QUEUE_OVERFLOW) throw e;

    cout << "Очередь переполнена" << endl << endl;
  }

  try {
    for (int i = 0; i < 3; i++) {
      cout << "Удален продукт:" << endl << pop(&tape) << endl << endl;
    }
  } catch (QueueErrors e) {
    if (e != QUEUE_UNDERFLOW) throw e;

    cout << "Очередь пустая" << endl << endl;
  }

  try {
    for (int i = 0; i < 4; i++) {
      cout << "Удален продукт:" << endl << pop(&tape) << endl << endl;
    }
  } catch (QueueErrors e) {
    if (e != QUEUE_UNDERFLOW) throw e;

    cout << "Очередь пустая" << endl << endl;
  }


  return 0;
}
