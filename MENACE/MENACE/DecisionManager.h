#pragma once
#include "Patterns/Singleton.h"

#include <vector>
#include <memory>

class iPiece;

class DecisionManager final : public Pattern::Singleton<DecisionManager>
{
public:	
	DecisionManager(Token);
	~DecisionManager();
		
	void Move(std::vector<std::unique_ptr<iPiece>>& players, std::vector<std::unique_ptr<iPiece>>& computers);

	void FirstTurn(std::vector<std::unique_ptr<iPiece>>& players, std::vector<std::unique_ptr<iPiece>>& computers);
	void SecondTurn(std::vector<std::unique_ptr<iPiece>>& players, std::vector<std::unique_ptr<iPiece>>& computers);
	void ThirdTurn(std::vector<std::unique_ptr<iPiece>>& players, std::vector<std::unique_ptr<iPiece>>& computers);

	void Restart(const bool playerWon);
	
	DecisionManager& operator=(const DecisionManager &) = delete;

private:	
	std::vector<int> firstActions;
	std::vector<int> secondActions;
	std::vector<int> thirdActions;

	unsigned turn;
	unsigned choice;
};

