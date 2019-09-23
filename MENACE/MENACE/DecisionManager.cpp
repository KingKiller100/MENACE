#include "DecisionManager.h"
#include <random>

DecisionManager::DecisionManager(Token) : turn(0)
{
	firstActions = secondActions = thirdActions = {0, 1, 2};
}

DecisionManager::~DecisionManager()
{
}

void DecisionManager::Move(std::vector<iPiece::u_ptr>& players, std::vector<iPiece::u_ptr>& computers)
{
	switch (turn)
	{
	case 0:
		FirstTurn(players, computers);
		break;
	case 1:
		SecondTurn(players, computers);
		break;
	case 2:
		ThirdTurn(players, computers);
		break;
	default: ;
	}

	turn++;
}

unsigned MakeChoice(const std::vector<int> &lesson)
{	
	std::random_device rd;
	std::default_random_engine generator(rd());
	const std::uniform_real_distribution<float> distribution(0, float(lesson.size()));

	return unsigned(distribution(generator));
}

void DecisionManager::FirstTurn(std::vector<iPiece::u_ptr>& players, std::vector<iPiece::u_ptr>& computers)
{
	choice = MakeChoice(firstActions);

	if (players[0]->GetLocation() == 4)
	{
		switch (firstActions[choice])
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
		if (firstActions[choice] == 0)
			computers[0]->SetLocation(4);
		else
		{
			computers[0]->SetLocation(5);
			players[1]->Dead();
		}
	}
	else
	{
		if (firstActions[choice] == 0)
			computers[1]->SetLocation(5);
		else if (firstActions[choice] == 1)
		{
			computers[1]->SetLocation(6);
			players[2]->Dead();
		}
		else
			computers[2]->SetLocation(6);
	}
}

void DecisionManager::SecondTurn(std::vector<iPiece::u_ptr>& players, std::vector<iPiece::u_ptr>& computers)
{
	choice = MakeChoice(secondActions);

	if (players[0]->GetLocation() == 7 && players[1]->GetLocation() == 5 && players[2]->GetLocation() == 6)
	{
		if (secondActions[choice] == 0)
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
		switch (secondActions[choice])
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
		switch (secondActions[choice])
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
	else if(players[0]->GetLocation() == 4 && !(players[1]->GetLocation() == 5) && players[2]->GetLocation() == 9)
	{
		if (secondActions[choice] == 0)
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

void DecisionManager::ThirdTurn(std::vector<iPiece::u_ptr>& players, std::vector<iPiece::u_ptr>& computers)
{
}

void DecisionManager::Restart(const bool playerWon)
{
	if (!playerWon)
	{
		if (turn == 0)
			firstActions.emplace_back(choice);
		else if (turn == 1)
			secondActions.emplace_back(choice);
		else
			thirdActions.emplace_back(choice);
	}

	turn = 0;
}

