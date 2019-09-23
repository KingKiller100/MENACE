#include "PlayerPiece.h"

PlayerPiece::PlayerPiece(std::string name, const unsigned short location) : Piece(name, location)
{}

void PlayerPiece::MoveLocation(const unsigned short loc)
{
	location = loc;
}
