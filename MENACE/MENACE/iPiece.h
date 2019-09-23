#pragma once
#include <string>
#include <memory>

class iPiece
{
public:
	using s_ptr = std::shared_ptr<iPiece>;
	using u_ptr = std::unique_ptr<iPiece>;
	
	virtual ~iPiece() = default;

	virtual std::string& GetName() noexcept = 0;
	virtual void SetName(const std::string& n) noexcept = 0;
	virtual unsigned short GetLocation() const noexcept = 0;
	virtual void SetLocation(const unsigned short l) noexcept = 0;
	virtual bool IsAlive() const noexcept = 0;
	virtual void LiveAgain() noexcept = 0;
	virtual void Dead() noexcept = 0;
};

