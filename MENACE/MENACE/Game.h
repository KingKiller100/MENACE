#pragma once
#include <vector>
#include "iWorld.h"

class Game final
{
public:
	~Game();

	static Game *Create();
	void PlayGame(const unsigned columns, const unsigned rows);

	bool Playing() const											{ return playing; }
	void SetPlaying(const bool p)									{ playing = p; }

	bool GameOver() const
	{
		return worlds[level]->gameOver;
	}

	void Restart()
	{
		worlds[level]->Restart();
		Draw();
	}

	bool Winner() const												{ return worlds[level]->playerWon; }

private:
	Game();

	void Update();
	void Draw();

private:
	static Game *mInstance;

	unsigned level;

	bool playing;
	
	std::vector<iWorld*> worlds;
};
