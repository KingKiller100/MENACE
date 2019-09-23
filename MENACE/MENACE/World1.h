#pragma once
#include "WorldBase.h"

namespace World
{
	class World1 final : public WorldBase
	{
	public:
		World1(const unsigned columns, const unsigned rows);
		~World1();

		void Restart() override;
		void Update() override;
		
		void DrawMap() override;
		bool ValidPiece(const unsigned piece) const override;

	private:
		unsigned ChoosePiece() override;
	};
}