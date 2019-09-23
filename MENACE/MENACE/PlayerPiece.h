#pragma once
#include "iPiece.h"

class PlayerPiece : public iPiece
{
public:
	PlayerPiece(std::string name, const unsigned short location);

	~PlayerPiece() = default;

	void MoveLocation(const unsigned short loc);
	std::string& GetName() noexcept override;
	void SetName(const std::string& n) noexcept override;
	unsigned short GetLocation() const noexcept override;
	void SetLocation(const unsigned short l) noexcept override;
	bool IsAlive() const noexcept override;
	void LiveAgain() noexcept override;
	void Dead() noexcept override;

protected:
	bool isAlive_;
	std::string name_;
	unsigned short location_;	
};
