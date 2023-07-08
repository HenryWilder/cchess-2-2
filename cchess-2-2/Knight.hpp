#pragma once
#include "Unit.hpp"

namespace sprite { struct Sprite; }
struct PieceMoves;

class Knight : public Unit
{
public:
	Piece GetPieceType() const override;
	const sprite::Sprite* GetSpritePointer() override;
	void AvailableMoves(PieceMoves* moves) override;
	bool CouldITakeAt(Coord hypothetical) override;
};
