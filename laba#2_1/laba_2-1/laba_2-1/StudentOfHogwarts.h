#pragma once

class StudentOfHogwarts {

private:
	char m_facultyName;
	char m_wandType;
	unsigned short m_epmloymentLikelihood;

public:
	StudentOfHogwarts();
	StudentOfHogwarts(char facultyName, char wandType, unsigned short epmloymentLikelihood) :
		m_facultyName(facultyName), m_wandType(wandType), m_epmloymentLikelihood(epmloymentLikelihood) {}
	
	friend std::ostream& operator<< (std::ostream&, const StudentOfHogwarts&);
};

