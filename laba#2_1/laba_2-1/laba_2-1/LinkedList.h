#pragma once
#include <iostream>


template <class T>
class LinkedList {

private:
    struct Node {
        T value;
        Node* next = NULL;
        Node* prev = NULL;

        Node(T v) : value(v), next(NULL), prev(NULL) {}
    };

    Node* getNode(int);

    Node* m_head;
    Node* m_tail;
    size_t m_length;

public:

    class Iterator {
        friend class LinkedList;
    private:
        Node* p;

        Iterator(Node* p) : p(p) {}
    public:
        Iterator(const Iterator& it) : p(it.p) {}

        bool operator!= (Iterator&) const;
        bool operator== (Iterator&) const;

        T& operator* () const;
        Iterator operator++ ();
        Iterator operator-- ();
    };

    LinkedList() : m_length(0), m_head(NULL), m_tail(NULL) {}
    LinkedList(std::initializer_list<T> values);
    LinkedList(LinkedList<T>&);
    ~LinkedList();

    T& operator[] (int);

    Iterator begin();
    Iterator end();

    void pushBack(T);
    T popBack();

    void pushFront(T);
    T popFront();

    void insert(T, size_t);
    T pop(size_t);

    T getElem(int);
    size_t getLength();
    void print();
};

template <class T>
bool LinkedList<T>::Iterator::operator!= (LinkedList<T>::Iterator &it) const {
    return p != it.p;
}

template <class T>
bool LinkedList<T>::Iterator::operator== (LinkedList<T>::Iterator& it) const {
    return p == it.p;
}


template <class T>
T& LinkedList<T>::Iterator::operator* () const {
    return p->value;
}

template <class T>
typename LinkedList<T>::Iterator LinkedList<T>::Iterator::operator++ () {
    p = p ? p->next : NULL;
    return *this;
}

template <class T>
typename LinkedList<T>::Iterator LinkedList<T>::Iterator::operator-- () {
    p = p ? p->prev : NULL;
    return *this;
}


template <class T>
LinkedList<T>::LinkedList(std::initializer_list<T> values) {
    for (const T &i : values) {
        this->pushBack(i);
    }
}

template <class T>
LinkedList<T>::LinkedList(LinkedList<T>& lst) {
    for (const int& i : lst) this->pushBack(i);
}

template <class T>
LinkedList<T>::~LinkedList() {
    for (Node* current = m_head; current != NULL; ) {
        Node* tmp = current;
        current = current->next;

        delete tmp;
    }
}

template <class T>
typename LinkedList<T>::Iterator LinkedList<T>::begin() {
    return LinkedList<T>::Iterator(m_head);
}

template <class T>
typename LinkedList<T>::Iterator LinkedList<T>::end() {
    return LinkedList<T>::Iterator(NULL);
}


template <class T>
void LinkedList<T>::pushBack(T value) {
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

template <class T>
T LinkedList<T>::popBack() {
    if (m_tail == NULL) throw "List is empty";
    
    m_length--;

    Node* tmp = m_tail;
    T value = tmp->value;

    m_tail = m_tail->prev;

    if (m_tail != NULL) {
        m_tail->next = NULL;
    } else {
        m_head = m_tail;
    }

    delete tmp;
    return value;
}


template <class T>
void LinkedList<T>::pushFront(T value) {
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

template <class T>
T LinkedList<T>::popFront() {
    if (m_head == NULL) throw "List is empty";

    m_length--;

    Node* tmp = m_head;
    T value = tmp->value;

    m_head = m_head->next;

    if (m_head != NULL) {
        m_head->prev = NULL;
    }
    else {
        m_tail = NULL;
    }

    delete tmp;
    return value;
}


template <class T>
void LinkedList<T>::insert(T value, size_t idx) {
    if (idx > m_length) throw "Index is bigger than a size of list";

    m_length++;

    Node* prev = NULL;
    Node* next = m_head;
    for (size_t i = 0; i < idx; i++) {
        prev = next;
        next = next->next;
    }

    Node* tmp = new Node(value);

    if (prev != NULL) {
        prev->next = tmp;
        tmp->prev = prev;
    }
    else {
        m_head = tmp;
    }

    if (next != NULL) {
        next->prev = tmp;
        tmp->next = next;
    }
    else {
        m_tail = tmp;
    }
}

template <class T>
T LinkedList<T>::pop(size_t idx) {
    Node* tmp = getNode(idx);
    T value = tmp->value;

    m_length--;

    if (tmp->prev) {
        tmp->prev->next = tmp->next;
    }
    else {
        m_head = tmp->next;
    }

    if (tmp->next) {
        tmp->next->prev = tmp->prev;
    }
    else {
        m_tail = tmp->prev;
    }

    delete tmp;
    return value;
}


template <class T>
typename LinkedList<T>::Node* LinkedList<T>::getNode(int idx) {
    idx = idx >= 0 ? idx : m_length + idx;
    if (m_length <= idx || idx < 0) throw "Index out of range of list";

    Node* current;

    if (idx < m_length / 2) {
        current = m_head;
        for (int i = 0; i < idx; i++) {
            current = current->next;
        }
    }
    else {
        current = m_tail;
        for (int i = m_length - 1; i > idx; i--) {
            current = current->prev;
        }
    }

    return current;
}

template <class T>
T& LinkedList<T>::operator[] (int idx) {
    return getNode(idx)->value;
}


template <class T>
T LinkedList<T>::getElem(int idx) {
    return getNode(idx)->value;
}

template <class T>
size_t LinkedList<T>::getLength() {
    return m_length;
}

template <class T>
void LinkedList<T>::print() {
    if (!m_length) {
        std::cout << "Список пуст" << std::endl;
        return;
    }

    size_t counter = 1;
    for (Node* current = m_head; current != NULL; current = current->next, counter++) {
        std::cout << counter << ") " << current->value << std::endl;
    }
}