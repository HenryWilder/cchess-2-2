#pragma once
#include "Unit.hpp"

namespace sprite { struct Sprite; }
struct PieceMoves;

class Rook : public Unit
{
public:
	Piece GetPieceType() const override;
	bool m_moved = false;
	void Move(Coord newPosition) override;
	const sprite::Sprite* GetSpritePointer() override;
	void AvailableMoves(PieceMoves* moves) override;
	bool CouldITakeAt(Coord hypothetical) override;
};
