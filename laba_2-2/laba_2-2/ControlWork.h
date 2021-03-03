#pragma once

#include <string>

class ControlWork
{
public:
	ControlWork();
	ControlWork(std::string, short, short);

	friend std::ostream& operator<< (std::ostream&, ControlWork&);

private:
	std::string m_subject;
	short m_numberOfTasks;
	short m_probabilityOfWriteOff;
};

