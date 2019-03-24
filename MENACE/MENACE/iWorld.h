#pragma once
#include <map>
#include <vector>
#include <string>
#include <iostream>
#include "Player.h"
#include "Computer.h"

class iWorld
{
public:
	iWorld(const unsigned columns, const unsigned rows) : gameOver(false), columns(columns + 2), rows(rows + 2)
	{}

	virtual void Restart() = 0;
	
	virtual ~iWorld()
	{
		for (auto && player : players)
		{
			delete player;
		}
		players.clear();

		for (auto && computer : computers)
		{
			delete computer;
		}
		computers.clear();

		matrix.clear();
	}
	
protected:
	virtual void DrawMap() = 0;

	// World Movement
	virtual bool ValidPiece(const unsigned piece) const = 0;

	virtual unsigned ChoosePiece() = 0;

	virtual bool ValidLocation(const unsigned location) const												{ return location >= 1 && location <= (rows - 2) * (columns - 2); }

	bool MoveableLocation(const unsigned location) const													{ return matrix.find(location) != matrix.end(); }

	virtual bool ValidMovement(Player *player, const unsigned location) const
	{
		if (!ValidLocation(location))
			return false;

		const auto playerLoc = player->GetLocation();
		

		if (playerLoc - location != columns - 2)
		{
			for (auto && computer : computers)
			{
				if (location == computer->GetLocation())
					return true;
			}
		}
		else
		{
			for (auto && computer : computers)
			{
				if (computer->GetLocation() == location)
					return false;
			}
		}

		return location < playerLoc;
	}

	virtual void MovePlayer(Player *player)
	{
		unsigned short location = 0;

		while (player->GetLocation() == location || !ValidMovement(player, location))
		{
				std::cout << "Select a new valid location" << std::endl;
				std::cin >> location;			
		}
		
		player->MoveLocation(location);
	}

	// Win States
	void PlayerWin(Player *player)
	{
		gameOver = player->GetLocation() <= columns - 2;
		if (gameOver) playerWon = true;
	}

	void ComputerWin(Computer *computer)
	{
		gameOver = computer->GetLocation() > ((rows - 2) * (columns - 2)) - (columns - 2);
		if (gameOver) playerWon = false;
	}

	void CheckWinState()
	{
		unsigned short deadPieces = 0;

		for (auto player : players)
		{
			if (player->IsAlive())
				PlayerWin(player);
			else
			{
				deadPieces++;
				gameOver = deadPieces == 3;
			}

			if (gameOver)
				return;
		}

		deadPieces = 0;

		for (auto computer : computers)
		{
			if (computer->IsAlive())
				ComputerWin(computer);
			else
			{
				deadPieces++;
				gameOver = deadPieces == 3;				
			}

			if (gameOver)
				return;
		}
	}
	
public:
	bool gameOver;
	bool playerWon;

protected:	
	unsigned columns;
	unsigned rows;

	std::vector<Player*> players;
	std::vector<Computer*> computers;

	std::map<unsigned short, std::string> matrix;
};
