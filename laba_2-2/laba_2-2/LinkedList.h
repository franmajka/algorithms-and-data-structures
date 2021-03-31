#pragma once
#include <iostream>
#include <type_traits>


template <class T>
class LinkedList {
public:
    using value_type = T;
    
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

    template <bool Const = false>
    class Iterator {
        friend class LinkedList<T>;

    public:
        using value_type = T;
        using pointer = std::conditional_t<Const, const Node*, Node*>;
        using reference = std::conditional_t<Const, const T&, T&>;

    private:
        pointer p;

        Iterator(pointer p) : p(p) {}
    public:
        Iterator(const Iterator& it) : p(it.p) {}

        bool operator!= (Iterator<Const>&) const;
        bool operator== (Iterator<Const>&) const;

        template <bool _Const = Const>
        std::enable_if_t<_Const, reference> operator* () const;
        template <bool _Const = Const>
        std::enable_if_t<!_Const, reference> operator* ();

        Iterator<Const>& operator++ ();
        Iterator<Const>& operator-- ();
    };

    LinkedList() : m_length(0), m_head(NULL), m_tail(NULL) {}
    LinkedList(std::initializer_list<T> values);
    LinkedList(const LinkedList<T>&);
    ~LinkedList();

    friend LinkedList<T> operator+ (const T& el, LinkedList<T> lst) {
        lst.pushFront(el);
        return lst;
    }

    friend LinkedList<T> operator+ (LinkedList<T> lst, const T& el) {
        lst.pushBack(el);
        return lst;
    }

    friend LinkedList<T> operator+ (LinkedList<T> left, const LinkedList<T>& right) {
        for (const T& el : right) {
            left.pushBack(el);
        }
        return left;
    }

    LinkedList<T>& operator= (const LinkedList<T>& lst);
    LinkedList<T>& operator+= (const T& el);
    LinkedList<T>& operator+= (const LinkedList<T>& lst);

    T& operator[] (int);
    const T& operator[] (int) const;

    Iterator<false> begin();
    Iterator<false> end();

    Iterator<true> begin() const;
    Iterator<true> end() const;

    void sort(bool (*compare)(const T& left, const T& right));

    void pushBack(T value);
    T popBack();

    void pushFront(T value);
    T popFront();

    void insert(T value, size_t idx);
    T pop(size_t idx);

    T getElem(int idx);
    size_t size();
    void print();

    void clear();
};

template <class T> template <bool Const>
bool LinkedList<T>::Iterator<Const>::operator!= (LinkedList<T>::Iterator<Const> &it) const {
    return p != it.p;
}

template <class T> template <bool Const>
bool LinkedList<T>::Iterator<Const>::operator== (LinkedList<T>::Iterator<Const>& it) const {
    return p == it.p;
}


template <class T> template <bool Const> template <bool _Const>
std::enable_if_t<_Const, typename LinkedList<T>::Iterator<Const>::reference> LinkedList<T>::Iterator<Const>::operator* () const {
    return p->value;
}

template <class T> template <bool Const> template <bool _Const>
std::enable_if_t<!_Const, typename LinkedList<T>::Iterator<Const>::reference> LinkedList<T>::Iterator<Const>::operator* ()
{
    return p->value;
}


template <class T> template <bool Const>
LinkedList<T>::Iterator<Const>& LinkedList<T>::Iterator<Const>::operator++ () {
    p = p ? p->next : NULL;
    return *this;
}

template <class T> template <bool Const>
LinkedList<T>::Iterator<Const>& LinkedList<T>::Iterator<Const>::operator-- () {
    p = p ? p->prev : NULL;
    return *this;
}


template <class T>
LinkedList<T>::LinkedList(std::initializer_list<T> values) {
    m_length = 0;
    m_head = NULL;
    m_tail = NULL;

    for (const T& i : values) pushBack(i);
}

template <class T>
LinkedList<T>::LinkedList(const LinkedList<T>& lst) {
    m_length = 0;
    m_head = NULL;
    m_tail = NULL;

    for (const T& i : lst) pushBack(i);
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
LinkedList<T>::Iterator<false> LinkedList<T>::begin() {
    return Iterator<false>(m_head);
}

template <class T>
LinkedList<T>::Iterator<false> LinkedList<T>::end() {
    return Iterator<false>(NULL);
}

template <class T>
LinkedList<T>::Iterator<true> LinkedList<T>::begin() const {
    return Iterator<true>(m_head);
}

template <class T>
LinkedList<T>::Iterator<true> LinkedList<T>::end() const {
    return Iterator<true>(NULL);
}


template <class T>
void LinkedList<T>::sort(bool (*compare)(const T& left, const T& right)) {
    if (size() < 2) return;

    LinkedList<T> left, right;
    T pivot = popFront();

    while (size()) {
        T el = popFront();

        if (compare(el, pivot)) {
            left.pushBack(el);
        }
        else {
            right.pushBack(el);
        }
    }

    left.sort(compare);
    right.sort(compare);

    *this = left + pivot + right;
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
const T& LinkedList<T>::operator[] (int idx) const {
    return getNode(idx)->value;
}


template <class T>
T LinkedList<T>::getElem(int idx) {
    return getNode(idx)->value;
}

template <class T>
size_t LinkedList<T>::size() {
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

template <class T>
void LinkedList<T>::clear()
{
    while (size()) popFront();
}


template<class T>
LinkedList<T>& LinkedList<T>::operator= (const LinkedList<T>& lst)
{
    if (this == &lst) return *this;

    clear();
    for (const T& el : lst) {
        pushBack(el);
    }

    return *this;
}

template<class T>
LinkedList<T>& LinkedList<T>::operator+= (const T& el)
{
    pushBack(el);
    return *this;
}

template<class T>
LinkedList<T>& LinkedList<T>::operator+= (const LinkedList<T>& lst)
{
    for (const T& el : lst) {
        pushBack(el);
    }

    return *this;
}
