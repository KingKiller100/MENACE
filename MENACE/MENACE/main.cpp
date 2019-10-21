#include "Game.h"
#include <iostream>

const unsigned short columns = 5;
const unsigned short rows = 5;

bool PlayAgain()
{
	std::cout << "play again?" << std::endl;
	std::string input;
	std::cin >> input;

	return input.front() == 'Y' || input.front() == 'y';	
}

int main(int argc, char **argv)
{
	std::cout << "Welcome To MENACE!" << std::endl;
	
	auto& game = Game::Reference();

	std::cout << "You are the O's" << std::endl << "BEGIN" << std::endl;

	auto play = game.Playing();

	while (play)
	{
		game.PlayGame(columns, rows);

		if (game.GameOver())
		{			
			const auto winner = game.Winner() ? "PLAYER" : "COMPUTER";
			std::cout << "Winner: " << winner << std::endl;
			game.Restart();
			play = PlayAgain();
		}
	}
	
	std::cin.get();

	return 0;
}