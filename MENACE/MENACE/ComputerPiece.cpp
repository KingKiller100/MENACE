#include "ComputerPiece.h"

ComputerPiece::ComputerPiece(std::string& name, const int location) noexcept
	: isAlive_(true), name_(std::move(name)), location_(location)
{
}

ComputerPiece::~ComputerPiece() = default;

const std::string& ComputerPiece::GetName() const noexcept
{
	return name_;
}

void ComputerPiece::SetName(const std::string& n) noexcept
{
	name_ = n;
}

unsigned short ComputerPiece::GetLocation() const noexcept
{
	return location_;
}

void ComputerPiece::SetLocation(const unsigned short l) noexcept
{
	location_ = l;
}

bool ComputerPiece::IsAlive() const noexcept
{
	return isAlive_;
}

void ComputerPiece::Live() noexcept
{
	isAlive_ = true;
}

void ComputerPiece::Dead() noexcept
{
	isAlive_ = false;
}

void ComputerPiece::MoveLocation(const unsigned short loc)
{
	location_ = loc;
}
