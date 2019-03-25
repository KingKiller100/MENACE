#pragma once
#include <vector>
#include "Computer.h"
#include "Player.h"

class DecisionManager final
{
public:
	DecisionManager(const DecisionManager &&) = delete;
	DecisionManager(const DecisionManager &) = delete;
	
	~DecisionManager();

	static DecisionManager * Instance();

	void Clear();

	void InputPlayers(Player *player);
	void InputComputers(Computer* computer);

	void Move();

	void FirstTurn();
	void SecondTurn();
	void ThirdTurn();

	void Restart(const bool playerWon);
	
	DecisionManager& operator=(const DecisionManager &) = delete;

private:
	DecisionManager();

	static DecisionManager * mInstance;

	std::vector<Computer*> computers;
	std::vector<Player*> players;

	std::vector<int> firstLessons;
	std::vector<int> secondLessons;
	std::vector<int> thirdLessons;

	unsigned turn;
	unsigned choice;
};

