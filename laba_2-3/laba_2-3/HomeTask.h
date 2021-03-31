#pragma once

using uint8_t = unsigned char;

struct HomeTask
{
	uint8_t interestingness;
	uint8_t completeTime;
	uint8_t complexity;
	uint8_t subjectUsefulness;

	HomeTask();

	uint8_t getPriority() const;

	bool operator< (const HomeTask& other) const;
	bool operator== (const HomeTask& other) const;
	bool operator> (const HomeTask& other) const;
	bool operator<= (const HomeTask& other) const;
	bool operator>= (const HomeTask& other) const;
	bool operator!= (const HomeTask& other) const;
};

