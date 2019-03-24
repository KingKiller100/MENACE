#include "Game.h"
#include "World1.h"
#include <array>

Game *Game::mInstance = nullptr;

Game* Game::Create()
{
	if (!mInstance)
		mInstance = new Game;

	return mInstance;
}

Game::Game()
{
	playing = true;
	level = 0;
	worlds.emplace_back(new World1(3, 3));

	Draw();
}

Game::~Game()
{
	delete mInstance;
}

void Game::Update()
{
	const auto currentWorld = worlds[level];

	if (level == 0)
		dynamic_cast<World1*>(currentWorld)->Update();
}

void Game::Draw()
{
	const auto currentWorld = worlds[level];

	if (level == 0)
		dynamic_cast<World1*>(currentWorld)->DrawMap();
}

void Game::PlayGame(const unsigned columns, const unsigned rows)
{
	Update();
	Draw();
}
