#include "Game.h"

#include "World1.h"


Game::Game(Token) : playing(true)
{
	worlds = std::make_unique<World::World1>(3, 3);
	Draw();
}

Game::~Game()
= default;

bool Game::Winner() const
{
	return worlds->isPlayerWinner;
}

void Game::Update() const
{
	worlds->Update();
}

void Game::Draw() const noexcept
{
	worlds->DrawMap();
}

void Game::PlayGame(const unsigned columns, const unsigned rows) const
{
	Update();
	Draw();
}

bool Game::GameOver() const
{
	return worlds->gameOver;
}

void Game::Restart() const
{
	worlds->Restart();
	Draw();
}

bool Game::Playing() const
{
	return playing;
}

constexpr void Game::SetPlaying(const bool p)
{
	playing = p;
}
