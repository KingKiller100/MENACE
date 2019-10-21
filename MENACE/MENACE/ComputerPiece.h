#pragma once
#include "iPiece.h"

class ComputerPiece : public iPiece
{
public:
	ComputerPiece(std::string& name, const int location) noexcept;
	virtual ~ComputerPiece();

	const std::string& GetName() const noexcept override;
	void SetName(const std::string& n) noexcept override;

	unsigned short GetLocation() const noexcept override;
	void SetLocation(const unsigned short l) noexcept override;

	bool IsAlive() const noexcept override;
	void Live() noexcept override;
	void Dead() noexcept override;

	void MoveLocation(const unsigned short loc) override;
	
protected:
	bool isAlive_;
	std::string name_;
	unsigned short location_;
};

