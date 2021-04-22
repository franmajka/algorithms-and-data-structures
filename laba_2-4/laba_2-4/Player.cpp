#include "Player.h"

#include <string>

#define NICKNAMES_ARRAY_LENGTH 26

std::string NICKNAMES_ARRAY[NICKNAMES_ARRAY_LENGTH] = {
	"aaron",
	"erin",
	"ronnie",
	"ron",
	"abbigail",
	"nabby",
	"abby",
	"gail",
	"abednego",
	"bedney",
	"abel",
	"ebbie",
	"ab",
	"abe",
	"eb",
	"abiel",
	"ab",
	"abigail",
	"nabby",
	"abby",
	"gail",
	"alexandria",
	"drina",
	"alexander",
	"alla",
	"sandra",
};

Player::Player(const std::string& anickname, const int& aexp, const int& ammr, const int& adonated)
{
	nickname = anickname;
	experience = aexp;
	mmr = ammr;
	donated = adonated;
}

Player::Player()
{
	nickname = NICKNAMES_ARRAY[rand() % NICKNAMES_ARRAY_LENGTH];
	experience = rand() % 10000;
	mmr = rand() % 10000;
	donated = rand() % 10000;
}

#define EXPERIENCE_COEFFICIENT .2
#define MMR_COEFFICIENT .1
#define DONATION_COEFFICIENT .7

float Player::getPriority() const
{
	return experience * EXPERIENCE_COEFFICIENT + mmr * MMR_COEFFICIENT + donated * DONATION_COEFFICIENT;
}

bool Player::operator<(const Player& other) const
{
	return getPriority() < other.getPriority();
}

bool Player::operator==(const Player& other) const
{
	//// All field comparison coz I don't wanna skip not the same objects
	//return nickname == other.nickname &&
	//	experience == other.experience &&
	//	mmr == other.mmr &&
	//	donated == other.donated;
	return getPriority() == other.getPriority();
}

bool Player::operator>(const Player& other) const
{
	return !(*this < other || *this == other);
}

bool Player::operator<=(const Player& other) const
{
	return *this < other || *this == other;
}

bool Player::operator>=(const Player& other) const
{
	return !(*this < other);
}

bool Player::operator!=(const Player& other) const
{
	return !(*this == other);
}
