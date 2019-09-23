#pragma once
#include "WorldBase.h"
#include "Patterns/Singleton.h"

class Game final : public Pattern::Singleton<Game>
{
public:
	explicit Game(Token);
	~Game();

	void PlayGame(const unsigned columns, const unsigned rows);

	bool GameOver() const;

	void Restart();

	constexpr bool Playing() const										{ return playing; }
	constexpr void SetPlaying(const bool p)								{ playing = p; }

	bool Winner() const;

private:

	void Update();
	void Draw() noexcept;

private:
	bool playing;
	
	std::shared_ptr<World::WorldBase> worlds;
};
