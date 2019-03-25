#pragma once
#include "Entities.h"

class Computer : public Entities
{
public:
	Computer(std::string &name, const unsigned short location) : Entities(name, location)
	{}

	virtual ~Computer() = default;
};