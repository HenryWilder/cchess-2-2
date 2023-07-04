#pragma once
#include "Unit.h"

class Bishop : public Unit
{
public:
	Piece GetPieceType() const override;
	sprite::Sprite* GetSpritePointer() override;
	void AvailableMoves(PieceMoves* moves) override;
	bool CouldITakeAt(Coord hypothetical) override;
};
