#include <iostream>
#include <clocale>
#include <cstdlib>
#include <ctime>

#include "StudentOfHogwarts.h"
#include "DynamicArray.h"
#include "LinkedList.h"

using namespace std;

int main()
{
    setlocale(LC_ALL, "rus");
    srand(time(NULL));

    DynamicArray<StudentOfHogwarts> arr;
    LinkedList<StudentOfHogwarts> lst;

    float totalDynamicArrayTime = 0;
    float totalLinkedListTime = 0;

    // Добавление 50 000 элементов в конец

    clock_t start = clock();
    for (int i = 0; i < 5e4; i++) {
        arr.push(StudentOfHogwarts());
    }
    float testDynamicArrayTime = (float(clock() - start)) / CLOCKS_PER_SEC;
    totalDynamicArrayTime += testDynamicArrayTime;

    start = clock();
    for (int i = 0; i < 5e4; i++) {
        lst.pushBack(StudentOfHogwarts());
    }
    float testLinkedListTime = (float(clock() - start)) / CLOCKS_PER_SEC;
    totalLinkedListTime += testLinkedListTime;

    cout << "Добавление 50 000 элементов в конец" << endl
        << "Динамический массив — " << testDynamicArrayTime << " секунд" << endl
        << "Связанный список — " << testLinkedListTime << " секунд" << endl << endl;
    
    // Добавление 10 000 элементов в начало

    start = clock();
    for (int i = 0; i < 1e4; i++) {
        arr.unshift(StudentOfHogwarts());
    }
    testDynamicArrayTime = (float(clock() - start)) / CLOCKS_PER_SEC;
    totalDynamicArrayTime += testDynamicArrayTime;

    start = clock();
    for (int i = 0; i < 1e4; i++) {
        lst.pushFront(StudentOfHogwarts());
    }
    testLinkedListTime = (float(clock() - start)) / CLOCKS_PER_SEC;
    totalLinkedListTime += testLinkedListTime;

    cout << "Добавление 10 000 элементов в начало" << endl
        << "Динамический массив — " << testDynamicArrayTime << " секунд" << endl
        << "Связанный список — " << testLinkedListTime << " секунд" << endl << endl;

    // Считывание 20 000 случайных значений

    start = clock();
    for (int i = 0; i < 2e4; i++) {
        arr.getElem(rand() % arr.getLength());
    }
    testDynamicArrayTime = (float(clock() - start)) / CLOCKS_PER_SEC;
    totalDynamicArrayTime += testDynamicArrayTime;

    start = clock();
    for (int i = 0; i < 2e4; i++) {
        lst.getElem(rand() % arr.getLength());
    }
    testLinkedListTime = (float(clock() - start)) / CLOCKS_PER_SEC;
    totalLinkedListTime += testLinkedListTime;

    cout << "Считывание 20 000 случайных значений" << endl
        << "Динамический массив — " << testDynamicArrayTime << " секунд" << endl
        << "Связанный список — " << testLinkedListTime << " секунд" << endl << endl;

    // Удаление 5 000 элементов с начала

    start = clock();
    for (int i = 0; i < 5e3; i++) {
        arr.shift();
    }
    testDynamicArrayTime = (float(clock() - start)) / CLOCKS_PER_SEC;
    totalDynamicArrayTime += testDynamicArrayTime;

    start = clock();
    for (int i = 0; i < 5e3; i++) {
        lst.popFront();
    }
    testLinkedListTime = (float(clock() - start)) / CLOCKS_PER_SEC;
    totalLinkedListTime += testLinkedListTime;

    cout << "Удаление 5 000 элементов с начала" << endl
        << "Динамический массив — " << testDynamicArrayTime << " секунд" << endl
        << "Связанный список — " << testLinkedListTime << " секунд" << endl << endl;

    // Удаление 5 000 элементов с конца

    start = clock();
    for (int i = 0; i < 5e3; i++) {
        arr.pop();
    }
    testDynamicArrayTime = (float(clock() - start)) / CLOCKS_PER_SEC;
    totalDynamicArrayTime += testDynamicArrayTime;

    start = clock();
    for (int i = 0; i < 5e3; i++) {
        lst.popBack();
    }
    testLinkedListTime = (float(clock() - start)) / CLOCKS_PER_SEC;
    totalLinkedListTime += testLinkedListTime;

    cout << "Удаление 5 000 элементов с конца" << endl
        << "Динамический массив — " << testDynamicArrayTime << " секунд" << endl
        << "Связанный список — " << testLinkedListTime << " секунд" << endl << endl;

    cout << "Полное время" << endl
        << "Динамический массив — " << totalDynamicArrayTime << " секунд" << endl
        << "Связанный список — " << totalLinkedListTime << " секунд" << endl << endl;

    system("PAUSE");
    return 0;
}