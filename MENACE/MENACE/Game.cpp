#include "Game.h"
#include "World1.h"


Game::Game(Token) : playing(true)
{
	worlds = std::make_shared<World::World1>(3, 3);
	Draw();
}

Game::~Game()
{}

bool Game::Winner() const
{
	return worlds->isPlayerWinner;
}

void Game::Update()
{
	worlds->Update();
}

void Game::Draw() noexcept
{
	worlds->DrawMap();
}

void Game::PlayGame(const unsigned columns, const unsigned rows)
{
	Update();
	Draw();
}

bool Game::GameOver() const
{
	return worlds->gameOver;
}

void Game::Restart()
{
	worlds->Restart();
	Draw();
}
