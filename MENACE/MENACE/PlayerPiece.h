#pragma once
#include "iPiece.h"

class PlayerPiece : public iPiece
{
public:
	PlayerPiece(std::string& name, const unsigned short location);

	~PlayerPiece() = default;

	void Dead() noexcept override;
	void Live() noexcept override;
	bool IsAlive() const noexcept override;
	
	const std::string& GetName() const noexcept override;
	void SetName(const std::string& n) noexcept override;

	void MoveLocation(const unsigned short loc) override;
	unsigned short GetLocation() const noexcept override;
	void SetLocation(const unsigned short l) noexcept override;

protected:
	bool isAlive_;
	std::string name_;
	unsigned short location_;	
};
