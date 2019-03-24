#pragma once
#include "iWorld.h"
#include "DecisionManager.h"

class World1 final : public iWorld
{
public:
	World1(const unsigned columns, const unsigned rows);
	void Restart() override;
	void Update();

	~World1() = default;

	void DrawMap() override;
	bool ValidPiece(const unsigned piece) const override						{ return piece >= 1 && piece <= players.size(); }

private:
	unsigned ChoosePiece() override;

private:
	DecisionManager * computerDecisionManager;
};
