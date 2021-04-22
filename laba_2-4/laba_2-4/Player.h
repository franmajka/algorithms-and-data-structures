#pragma once

#include <string>

struct Player
{
	std::string nickname;
	int experience; // Hours spent
	int mmr; // Current matchmaking rating
	int donated; // USD spent

	Player(const std::string& anickname, const int& aexp, const int& ammr, const int& adonated);
	Player();

	float getPriority() const;

	bool operator<	(const Player& other) const;
	bool operator== (const Player& other) const;
	bool operator>	(const Player& other) const;
	bool operator<= (const Player& other) const;
	bool operator>= (const Player& other) const;
	bool operator!= (const Player& other) const;
};

