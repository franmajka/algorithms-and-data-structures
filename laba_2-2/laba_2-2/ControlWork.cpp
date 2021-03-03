#include "ControlWork.h"

#include <iostream>
#include <string>

#define N 9

const std::string SUBJECTS[N] = {
	"Матан",
	"Линал",
	"АСД",
	"Прога",
	"История",
	"Риторика",
	"ФП",
	"Физика",
	"ДМ",
};

ControlWork::ControlWork() {
	m_subject = SUBJECTS[rand() % N];
	m_numberOfTasks = rand() % 20;
	m_probabilityOfWriteOff = rand() % 101;
}

ControlWork::ControlWork(std::string subject, short numberOfTasks, short probabilityOfWriteOff) {
	m_subject = subject;
	m_numberOfTasks = numberOfTasks;
	m_probabilityOfWriteOff = probabilityOfWriteOff;
}

std::ostream& operator<< (std::ostream &out, ControlWork &controlWork) {
	out << "Контрольная робота с предмета " << controlWork.m_subject
		<< " на " << controlWork.m_numberOfTasks << " заданий."
		<< " Вероятность списать — " << controlWork.m_probabilityOfWriteOff << "%.";
	return out;
}