#include <iostream>
#include "Game.h"

const unsigned short columns = 5;
const unsigned short rows = 5;

bool PlayAgain()
{
	std::cout << "play again?" << std::endl;
	std::string input;
	std::cin >> input;

	return input.at(0) == 'Y' || input.at(0) == 'y';	
}

int main(int argc, char *argv)
{
	const auto game = Game::Create();
	
	auto play = game->Playing();

	while (play)
	{
		game->PlayGame(columns, rows);

		if (game->GameOver())
		{			
			const auto winner = game->Winner() ? "PLAYER" : "COMPUTER";
			std::cout << "Winner: " << winner << std::endl;
			play = PlayAgain();

			game->Restart();
		}
	}
	
	std::cin.get();

	return 0;
}