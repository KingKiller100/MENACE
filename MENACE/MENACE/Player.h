#pragma once
#include "Entities.h"

class Player : public Entities
{
public:
	Player()
	= default;

	Player(std::string name, const unsigned short location);

	~Player() = default;

	void MoveLocation(const int loc);
};