#pragma once
#include "Unit.h"

class Pawn : public Unit
{
public:
	signed int GetForward() const;
	Piece GetPieceType() const override;
	bool m_moved = false;
	bool en_pasant = false;
	void Move(Coord newPosition) override;
	sprite::Sprite* GetSpritePointer() override;
	void AvailableMoves(PieceMoves* moves) override;
	bool CouldITakeAt(Coord hypothetical) override;
};
