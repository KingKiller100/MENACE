#include "WorldBase.h"
#include "iPiece.h"
#include <iostream>

namespace World
{
	WorldBase::WorldBase(const unsigned columns, const unsigned rows)
	: gameOver(false), isPlayerWinner(false),
	columns(columns + 2), rows(rows + 2)
	{
	}

	WorldBase::~WorldBase()
	{
		for (auto& player : players)
		{
			player.reset();
		}
		players.clear();

		for (auto& computer : computers)
		{
			computer.reset();
		}
		computers.clear();

		worldMatrix.clear();
	}

	bool WorldBase::ValidLocation(const unsigned location) const noexcept
	{
		return location >= 1 && location <= (rows - 2) * (columns - 2);
	}

	bool WorldBase::IsOnTheBoard(const unsigned location) const
	{
		return worldMatrix.find(location) != worldMatrix.end();
	}

	bool WorldBase::ValidMovement(const iPiece& player, const unsigned location) const
	{
		if (!ValidLocation(location))
			return false;

		const auto playerLocation = player.GetLocation();

		if (playerLocation - location != columns - 2)
		{
			for (auto& computer : computers)
			{
				if (location == computer->GetLocation())
					return true;
			}
		}
		else
		{
			for (auto& computer : computers)
			{
				if (computer->GetLocation() == location)
					return false;
			}
		}

		return location < playerLocation;
	}

	void WorldBase::MovePlayer(iPiece& player)
	{
		unsigned short location = 0;

		while (player.GetLocation() == location || !ValidMovement(player, location))
		{
			std::cout << "Select a new valid location" << std::endl;
			std::cin >> location;
		}

		player.MoveLocation(location);
	}

	void WorldBase::PlayerWin(const iPiece& player)
	{
		gameOver = player.GetLocation() <= columns - 2;
		if (gameOver) isPlayerWinner = true;
	}

	bool WorldBase::NoMovablePieces()
	{
		auto immovable = unsigned(0);
		auto livingPlayers = unsigned(0);

		for (auto& player : players)
		{
			if (player->IsAlive())
				livingPlayers++;
			else
				continue;

			for (auto& computer : computers)
			{
				if (!computer->IsAlive())
					continue;

				if (player->GetLocation() - computer->GetLocation() == (rows - 2))
					immovable++;
			}
		}

		return immovable == livingPlayers;
	}

	void WorldBase::CheckWinState()
	{
		unsigned short deadPieces = 0;

		for (const auto& player : players)
		{
			if (player->IsAlive())
			{
				PlayerWin(*player);
			}
			else
			{
				deadPieces++;
				gameOver = deadPieces == 3;
				isPlayerWinner = false;
			}

			if (gameOver)
				return;
		}

		deadPieces = 0;

		for (auto& computer : computers)
		{
			if (computer->IsAlive())
				ComputerWin(*computer);
			else
			{
				deadPieces++;
				gameOver = deadPieces == 3;
				isPlayerWinner = true;
			}


			if (gameOver)
				return;
		}
	}

	void WorldBase::ComputerWin(const iPiece& computer)
	{
		gameOver = computer.GetLocation() > (rows - 2) * (columns - 2) - (columns - 2);
		if (gameOver) isPlayerWinner = false;
	}

}
