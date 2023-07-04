#pragma once
#include "Unit.h"

class Rook : public Unit
{
public:
	Piece GetPieceType() const override;
	bool m_moved = false;
	void Move(Coord newPosition) override;
	sprite::Sprite* GetSpritePointer() override;
	void AvailableMoves(PieceMoves* moves) override;
	bool CouldITakeAt(Coord hypothetical) override;
};
