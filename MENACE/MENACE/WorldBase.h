#pragma once
#include "iWorld.h"

#include <map>
#include <vector>
#include <string>
#include <memory>

class iPiece;

namespace World
{	
	class WorldBase : public iWorld
	{		
	public:
		
		WorldBase(const unsigned columns, const unsigned rows);

		virtual ~WorldBase();

		virtual void Update()  {}
		virtual void DrawMap() {}
		virtual void Restart() {}

	protected:
		virtual unsigned ChoosePiece() = 0;
		virtual bool ValidPiece(const unsigned piece) const = 0;

		virtual void MovePlayer(iPiece& player);
		virtual bool ValidLocation(const unsigned location) const noexcept;
		virtual bool ValidMovement(const iPiece& player, const unsigned location) const;

		bool IsOnTheBoard(const unsigned location) const;
		
		// Win States
		void PlayerWin(const iPiece& player);
		void ComputerWin(const iPiece& computer);
		bool NoMovablePieces();
		void CheckWinState();

	public:
		bool gameOver;
		bool isPlayerWinner;

	protected:
		unsigned columns;
		unsigned rows;

		std::vector<std::unique_ptr<iPiece>> players;
		std::vector<std::unique_ptr<iPiece>> computers;

		std::map<unsigned short, std::string> worldMatrix;
	};
}
