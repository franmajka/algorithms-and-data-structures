#include <string>
#include <iostream>

#include "StudentOfHogwarts.h"

#define NUMBER_OF_FACULTIES 4

const char FACULTIES[NUMBER_OF_FACULTIES] = {
    '�',
    '�',
    '�',
    '�'
};

StudentOfHogwarts::StudentOfHogwarts() {
    m_facultyName = FACULTIES[rand() % NUMBER_OF_FACULTIES];
    m_wandType = 65 + (rand() % 26); // �� A �� Z
    m_epmloymentLikelihood = rand() % 101;
}

std::ostream& operator<< (std::ostream &out, const StudentOfHogwarts &el) {
    out << "��������� � " << el.m_facultyName
        << ", ��� ������� � " << el.m_wandType 
        << ", ����������� ��������������� � " << el.m_epmloymentLikelihood << "%";

    return out;
}