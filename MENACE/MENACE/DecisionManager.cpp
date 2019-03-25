#include "DecisionManager.h"
#include <ctime>
#include <cstdlib>
#include <random>

DecisionManager* DecisionManager::mInstance = nullptr;

DecisionManager::DecisionManager()
{	
	for (int i = 0; i < 3; ++i)
	{
		firstLessons.emplace_back(i);
		secondLessons.emplace_back(i);
		thirdLessons.emplace_back(i);
	}
	
	turn = 0;
}

DecisionManager* DecisionManager::Instance()
{
	if (!mInstance)
		mInstance = new DecisionManager;

	return mInstance;
}

DecisionManager::~DecisionManager()
{
	Clear();
}

void DecisionManager::Clear()
{
	players = std::vector<Player*>();
	computers = std::vector<Computer*>();
}

void DecisionManager::InputPlayers(Player* player)
{
	players.emplace_back(player);
}

void DecisionManager::InputComputers(Computer* computer)
{
	computers.emplace_back(computer);
}

void DecisionManager::Move()
{
	switch (turn)
	{
	case 0:
		FirstTurn();
		break;
	case 1:
		SecondTurn();
		break;
	case 2:
		ThirdTurn();
		break;
	}

	turn++;
}

unsigned MakeChoice(const std::vector<int> &lesson)
{
	std::random_device rd;
	std::default_random_engine generator(rd());
	const std::uniform_real_distribution<float> distribution(0, lesson.size());

	return unsigned(distribution(generator));
}

void DecisionManager::FirstTurn()
{
	choice = MakeChoice(firstLessons);

	if (players[0]->GetLocation() == 4)
	{
		switch (firstLessons[choice])
		{
		case 0:
			computers[1]->SetLocation(5);
			break;

		case 1:
			computers[1]->SetLocation(4);
			players[0]->Dead();
			break;
		case 2: 
			computers[2]->SetLocation(6);
			break;
		default: break;
		}
	}
	else if (players[1]->GetLocation() == 5)
	{
		if (firstLessons[choice] == 0)
			computers[0]->SetLocation(4);
		else
		{
			computers[0]->SetLocation(5);
			players[1]->Dead();
		}
	}
	else
	{
		if (firstLessons[choice] == 0)
			computers[1]->SetLocation(5);
		else if (firstLessons[choice] == 1)
		{
			computers[1]->SetLocation(6);
			players[2]->Dead();
		}
		else
			computers[2]->SetLocation(6);
	}
}

void DecisionManager::SecondTurn()
{
	choice = MakeChoice(secondLessons);

	if (players[0]->GetLocation() == 7 && players[1]->GetLocation() == 5 && players[2]->GetLocation() == 6)
	{
		if (secondLessons[choice] == 0)
		{
			computers[1]->SetLocation(6);
			players[2]->Dead();
		}
		else
		{
			computers[2]->SetLocation(5);
			players[1]->Dead();
		}
	}
	else if (players[0]->GetLocation() == 7 && !players[1]->IsAlive() && players[2]->GetLocation() == 6)
	{
		switch (secondLessons[choice])
		{
		case 0:
			computers[0]->SetLocation(7);
			players[0]->Dead();
			break;
		case 1:
			computers[0]->SetLocation(8);
			break;
		case 2:
			computers[1]->SetLocation(6);
			players[2]->Dead();
			break;
		}
	}
	else if(players[0]->GetLocation() == 4 && players[1]->GetLocation() == 6 && players[2]->GetLocation() == 9)
	{
		switch (secondLessons[choice])
		{
		case 0:
			computers[1]->SetLocation(4);
			players[0]->Dead();
			break;
		case 1:
			computers[1]->SetLocation(5);
			break;
		case 2:
			computers[1]->SetLocation(6);
			players[2]->Dead();
			break;
		}
	}
	else if (players[1]->GetLocation() == 4 && !players[0]->IsAlive() && players[2]->GetLocation() == 9)
	{
		computers[2]->SetLocation(6);
	}
	else if(players[0]->GetLocation() == 4 && !players[1]->GetLocation() == 5 && players[2]->GetLocation() == 9)
	{
		if (secondLessons[choice] == 0)
		{
			computers[0]->SetLocation(5);
			players[1]->Dead();
		}
		else
		{
			computers[1]->SetLocation(4);
			players[0]->Dead();
		}
	}
}

void DecisionManager::ThirdTurn()
{
}

void DecisionManager::Restart(const bool playerWon)
{
	if (!playerWon)
	{
		if (turn == 0)
			firstLessons.emplace_back(choice);
		else if (turn == 1)
			secondLessons.emplace_back(choice);
		else
			thirdLessons.emplace_back(choice);
	}

	turn = 0;
}


