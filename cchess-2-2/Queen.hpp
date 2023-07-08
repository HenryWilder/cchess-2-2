#pragma once
#include "Unit.hpp"

namespace sprite { struct Sprite; }
struct PieceMoves;

class Queen : public Unit
{
public:
	constexpr Piece GetPieceType() const override { return Piece::Queen; }
	const sprite::Sprite* GetSpritePointer() override;
	void AvailableMoves(PieceMoves* moves) override;
	bool CouldITakeAt(Coord hypothetical) override;
};
