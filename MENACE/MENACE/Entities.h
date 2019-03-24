#pragma once
#include <string>
#include <utility>

class Entities
{
public:
	Entities()
	{
		name = "X";
		location = 0;
		isAlive = true;
	}

	Entities(std::string &name, const int location) : name(std::move(name)), location(location)
	{		
		isAlive = true;
	}

	virtual ~Entities() = default;

	std::string GetName() const							{ return name; }
	void SetName(const std::string &n)					{ name = n; }

	int GetLocation() const								{ return location; }
	void SetLocation(const int l)						{ location = l; }

	bool IsAlive() const								{ return isAlive; }
	void LiveAgain()									{ isAlive = true; }
	void Dead()											{ isAlive = false; }
	
protected:
	std::string name;
	unsigned short location;

	bool isAlive;
};

