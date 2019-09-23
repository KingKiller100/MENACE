#pragma once
#include "iWorld.h"
#include "iPiece.h"

#include <map>
#include <vector>
#include <string>

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
		virtual bool ValidPiece(const unsigned piece) const = 0;
		virtual unsigned ChoosePiece() = 0;

		virtual bool ValidLocation(const unsigned location) const noexcept;
		bool IsOnTheBoard(const unsigned location) const;
		virtual bool ValidMovement(iPiece::u_ptr& player, const unsigned location) const;
		virtual void MovePlayer(iPiece::u_ptr& player);

		// Win States
		void PlayerWin(const iPiece::u_ptr& player);
		void ComputerWin(const iPiece::u_ptr& computer);
		bool NoMovablePieces();
		void CheckWinState();

	public:
		bool gameOver;
		bool isPlayerWinner;

	protected:
		unsigned columns;
		unsigned rows;

		std::vector<iPiece::u_ptr> players;
		std::vector<iPiece::u_ptr> computers;

		std::map<unsigned short, std::string> matrix;
	};
}
