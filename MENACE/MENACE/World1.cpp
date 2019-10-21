#include "World1.h"
#include "PlayerPiece.h"
#include "ComputerPiece.h"
#include "DecisionManager.h"

#include <iostream>

namespace World
{	
	World1::World1(const unsigned columns, const unsigned rows)
	: WorldBase(columns, rows), decisionManager(DecisionManager::Reference())
	{
		for (unsigned short i = 0; i < 6; ++i)
		{
			const auto compTeam = i < 3;
			std::string name = compTeam ? "X" : "O";

			unsigned short pos;

			switch (i)
			{
			case 0:
				pos = 1;
				name += std::to_string(1);
				break;
			case 1:
				pos = 2;
				name += std::to_string(2);
				break;
			case 2:
				pos = 3;
				name += std::to_string(3);
				break;
			case 3:
				pos = 7;
				name += std::to_string(1);
				break;
			case 4:
				pos = 8;
				name += std::to_string(2);
				break;
			case 5:
				pos = 9;
				name += std::to_string(3);
				break;
			default: break;
			}

			compTeam ?
				computers.emplace_back(std::make_unique<ComputerPiece>(name, pos)) :
				players.emplace_back(std::make_unique<PlayerPiece>(name, pos));
		}
	}

	World1::~World1()
		= default;

	void World1::Restart()
	{
		for (unsigned i = 0; i < computers.size(); ++i)
		{
			computers[i]->SetName("X" + std::to_string(i + 1));

			switch (i)
			{
			case 0: computers[i]->SetLocation(1);
				break;
			case 1: computers[i]->SetLocation(2);
				break;
			case 2: computers[i]->SetLocation(3);
				break;
			default: break;
			}

			computers[i]->Live();
		}

		for (unsigned i = 0; i < players.size(); ++i)
		{
			players[i]->SetName("O" + std::to_string(i + 1));

			switch (i)
			{
			case 0: players[i]->SetLocation(7);
				break;
			case 1: players[i]->SetLocation(8);
				break;
			case 2: players[i]->SetLocation(9);
				break;
			default: break;
			}

			players[i]->Live();
		}

		decisionManager.Restart(isPlayerWinner);
	}
	

	unsigned World1::ChoosePiece()
	{
		unsigned short piece = 0;

		do
		{
			std::cout << "Select a valid piece number" << std::endl;
			std::cin >> piece;
		}
		while (!ValidPiece(piece) || !players[piece - 1]->IsAlive());

		return piece;
	}

	void World1::Update()
	{
		const auto piece = ChoosePiece() - 1;

		MovePlayer(*players[piece]);

		for (const auto& computer : computers)
		{
			if (players[piece]->GetLocation() == computer->GetLocation())
				computer->Dead();
		}

		std::cout << "Player's Move" << std::endl;

		DrawMap();

		std::cout << "Computer's Move" << std::endl;
		decisionManager.Move(players, computers);

		isPlayerWinner = gameOver = NoMovablePieces();

		if (gameOver)
			return;

		CheckWinState();
	}

	void World1::DrawMap()
	{
		for (unsigned y = 0; y < rows; ++y)
		{
			for (unsigned x = 0; x < columns; ++x)
			{
				unsigned short offset = x + y * 5;

				if (!(y & 1))
					worldMatrix[offset] = x % 2 != 0 ? "|" : std::to_string(short(x * .5 + y * .5 * 3) + 1) + " ";
				else
					worldMatrix[offset] = x % 2 == 0 ? "--" : " ";
			}
		}

		for (const auto& player : players)
		{
			if (!player->IsAlive())
				continue;

			if (worldMatrix.find(player->GetLocation()) != worldMatrix.end())
			{
				const auto location = player->GetLocation();
				unsigned offset;

				if (location > 3 && location <= 6)
					offset = location * 2 + 2;
				else if (location > 6)
					offset = location * 2 + 6;
				else
					offset = location * 2 - 2;

				worldMatrix[offset] = player->GetName();
			}
		}

		for (const auto& computer : computers)
		{
			if (!computer->IsAlive())
				continue;

			if (worldMatrix.find(computer->GetLocation()) != worldMatrix.end())
			{
				const auto location = computer->GetLocation();
				unsigned offset;

				if (location > 3 && location <= 6)
					offset = location * 2 + 2;
				else if (location > 6)
					offset = location * 2 + 6;
				else
					offset = location * 2 - 2;

				worldMatrix[offset] = computer->GetName();
			}
		}

		const auto size = worldMatrix.size();
		for (unsigned i = 0; i < size; ++i)
		{
			if (i % rows == 0)
				std::cout << std::endl;

			std::cout << worldMatrix[i];
		}

		std::cout << "\n\n";
	}

	bool World1::ValidPiece(const unsigned piece) const
	{
		return piece >= 1 && piece <= players.size();
	}
}
