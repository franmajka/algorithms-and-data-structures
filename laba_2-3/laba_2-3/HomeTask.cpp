#include "HomeTask.h"

#include <iostream>

HomeTask::HomeTask()
{
	interestingness = rand() % 101;
	completeTime = rand() % 101;
	complexity = rand() % 101;
	subjectUsefulness = rand() % 101;
}

#define INTERESTINGNESS_C .5
#define COMPLETE_TIME_C .05
#define COMPLEXITY_C .05
#define SUBJECT_USEFULNESS_C .4

uint8_t HomeTask::getPriority() const
{
	return interestingness * INTERESTINGNESS_C
		+ completeTime * COMPLETE_TIME_C
		+ complexity * COMPLEXITY_C
		+ subjectUsefulness * SUBJECT_USEFULNESS_C;
}

bool HomeTask::operator<(const HomeTask& other) const
{
	return getPriority() < other.getPriority();
}

bool HomeTask::operator==(const HomeTask& other) const
{
	return getPriority() == other.getPriority();
}

bool HomeTask::operator>(const HomeTask& other) const
{
	return !(*this <= other);
}

bool HomeTask::operator<=(const HomeTask& other) const
{
	return *this < other || *this == other;
}

bool HomeTask::operator>=(const HomeTask& other) const
{
	return !(*this < other);
}

bool HomeTask::operator!=(const HomeTask& other) const
{
	return !(*this == other);
}
