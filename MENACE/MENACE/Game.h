#pragma once
#include "WorldBase.h"
#include "Patterns/Singleton.h"

class Game final : public Pattern::Singleton<Game>
{
public:
	explicit Game(Token);
	~Game();

	void PlayGame(const unsigned columns, const unsigned rows) const;

	bool GameOver() const;

	void Restart() const;

	bool Playing() const					;					
	constexpr void SetPlaying(const bool p)			;					

	bool Winner() const;

private:

	void Update() const;
	void Draw() const noexcept;

private:
	bool playing;
	
	std::unique_ptr<World::WorldBase> worlds;
};

