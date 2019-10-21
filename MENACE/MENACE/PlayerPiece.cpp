#include "PlayerPiece.h"

PlayerPiece::PlayerPiece(std::string& name, const unsigned short location)
: isAlive_(false),
  name_(std::move(name)),
  location_(location)
{}

void PlayerPiece::MoveLocation(const unsigned short loc)
{
	location_ = loc;
}

const std::string& PlayerPiece::GetName() const noexcept
{
	return name_;
}

void PlayerPiece::SetName(const std::string& n) noexcept
{
	name_ = n;
}

unsigned short PlayerPiece::GetLocation() const noexcept
{
	return location_;
}

void PlayerPiece::SetLocation(const unsigned short l) noexcept
{
	location_ = l;
}

bool PlayerPiece::IsAlive() const noexcept
{
	return isAlive_;
}

void PlayerPiece::Live() noexcept
{
	isAlive_ = true;
}

void PlayerPiece::Dead() noexcept
{
	isAlive_ = false;
}


