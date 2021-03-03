#include <string>
#include <iostream>

#include "StudentOfHogwarts.h"

#define NUMBER_OF_FACULTIES 4

const char FACULTIES[NUMBER_OF_FACULTIES] = {
    'Г',
    'П',
    'К',
    'С'
};

StudentOfHogwarts::StudentOfHogwarts() {
    m_facultyName = FACULTIES[rand() % NUMBER_OF_FACULTIES];
    m_wandType = 65 + (rand() % 26); // От A до Z
    m_epmloymentLikelihood = rand() % 101;
}

std::ostream& operator<< (std::ostream &out, const StudentOfHogwarts &el) {
    out << "Факультет — " << el.m_facultyName
        << ", тип палочки — " << el.m_wandType 
        << ", вероятность трудоустройства — " << el.m_epmloymentLikelihood << "%";

    return out;
}