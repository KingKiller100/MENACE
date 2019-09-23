#pragma once
#include "iPiece.h"

class ComputerPiece : public iPiece
{
public:
	ComputerPiece(std::string& name, const int location) noexcept;
	virtual ~ComputerPiece();

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

