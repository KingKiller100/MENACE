#pragma once
#include "Entities.h"

class Player : public Entities
{
public:
	Player(std::string &name, double location) = delete;
	Player(std::string name, const unsigned short location);

	~Player() = default;

	void MoveLocation(const int loc);
};