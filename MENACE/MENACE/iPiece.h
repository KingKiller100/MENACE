#pragma once
#include <string>
#include <memory>

class iPiece
{
public:
	using W_Ptr = std::weak_ptr<iPiece>;
	using S_Ptr = std::shared_ptr<iPiece>;
	using U_Ptr = std::unique_ptr<iPiece>;
	
	virtual ~iPiece() = default;

	virtual void Dead() noexcept = 0;
	virtual void Live() noexcept = 0;
	virtual bool IsAlive() const noexcept = 0;
	virtual const std::string& GetName() const noexcept = 0;
	virtual void MoveLocation(const unsigned short loc) = 0;
	virtual void SetName(const std::string& n) noexcept = 0;
	virtual unsigned short GetLocation() const noexcept = 0;
	virtual void SetLocation(const unsigned short l) noexcept = 0;
	
};

