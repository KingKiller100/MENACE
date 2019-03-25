#include "World1.h" 

World1::World1(const unsigned columns, const unsigned rows) : iWorld(columns, rows)
{	
	computerDecisionManager = DecisionManager::Instance();
	
	for (unsigned i = 0; i < 3; ++i)
	{
		std::string name = "X" + std::to_string(i + 1);
		unsigned pos = 0;
		
		switch (i)
		{
		case 0: pos = 1;
			break;
		case 1: pos = 2 ;
			break;
		case 2: pos = 3;
			break;
		default: break;
		}

		computers.emplace_back(new Computer(name, pos));

		computerDecisionManager->InputComputers(computers[i]);
	}

	for (unsigned i = 0; i < 3; ++i)
	{
		const auto name = "O" + std::to_string(i + 1);
		unsigned pos = 0;

		switch (i)
		{
		case 0: pos = 7;
			break;
		case 1: pos = 8;
			break;
		case 2: pos = 9;
			break;
		default: break;
		}

		players.push_back(new Player(name, pos));

		computerDecisionManager->InputPlayers(players[i]);
	}
}

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

		computers[i]->LiveAgain();
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

		players[i]->LiveAgain();
	}

	computerDecisionManager->Restart(playerIsWinner);
}

unsigned World1::ChoosePiece()
{
	unsigned short piece = 0;

	while (!ValidPiece(piece) || !players[piece - 1]->IsAlive())
	{
		std::cout << "Select a valid piece number" << std::endl;
		std::cin >> piece;
	}

	return piece;
}

void World1::Update()
{
	const auto piece = ChoosePiece() - 1;

	MovePlayer(players[piece]);

	for (auto computer : computers)
	{
		if (players[piece]->GetLocation() == computer->GetLocation())
			computer->Dead();		
	}

	std::cout << "Player's Move" << std::endl;

	DrawMap();

	std::cout << "Computer's Move" << std::endl;
	computerDecisionManager->Move();

	playerIsWinner = gameOver = NoMovablePieces();

	if (gameOver)
		return;

	CheckWinState();
}

void World1::DrawMap()
{
	for (unsigned y = 0; y < rows; ++y)
		for (unsigned x = 0; x < columns; ++x)
		{
			unsigned short offset = x + y * 5;

			if (!(y & 1))
				matrix[offset] = x % 2 != 0 ? "|" : std::to_string(short(x * .5 + y * .5 * 3) + 1) + " ";
			else
				matrix[offset] = x % 2 == 0 ? "--" : " ";
		}
	
		
	for (auto && player : players)
	{
		if (!player->IsAlive())
			continue;

		if (matrix.find(player->GetLocation()) != matrix.end())
		{
			const auto location = player->GetLocation();
			unsigned offset;

			if (location > 3 && location <= 6)
				offset = location * 2 + 2;
			else if (location > 6)
				offset = location * 2 + 6;
			else
				offset = location * 2 - 2;
			 
			matrix[offset] = player->GetName();
		}
	}

	for (auto && c : computers)
	{
		if (!c->IsAlive())
			continue;

		if (matrix.find(c->GetLocation()) != matrix.end())
		{
			const auto location = c->GetLocation();
			unsigned offset;

			if (location > 3 && location <= 6)
				offset = location * 2 + 2;
			else if (location > 6)
				offset = location * 2 + 6;
			else
				offset = location * 2 - 2;
						
			matrix[offset] = c->GetName();
		}
	}	

	const auto size = matrix.size();
	for (unsigned i = 0; i < size; ++i)
	{
		if (i % rows == 0)
			std::cout << std::endl;

		std::cout << matrix[i];
	}

	std::cout << "\n\n";
}