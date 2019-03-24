#include "Player.h"

Player::Player(std::string name, const unsigned short location) : Entities(name, location)
{}

void Player::MoveLocation(const int loc)
{
	location = loc;
}
