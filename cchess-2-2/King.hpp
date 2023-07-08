#pragma once
#include "Unit.hpp"

namespace sprite { struct Sprite; }
struct PieceMoves;

class King : public Unit
{
private:
	bool isMoved = false;

public:
	Piece GetPieceType() const override;
	bool IsMoved() const { return isMoved; }
	void Move(Coord newPosition) override;
	const sprite::Sprite* GetSpritePointer() override;
	Unit* TestMoveSafety(Coord testPos);
	bool TestMoveSafetyValidate(Coord position);
	Unit* LineTraceSafety(Coord startPos, Coord direction);
	bool CanIBeTaken(const Coord position, const Coord direction);
	bool CheckSafetyDirectional(Coord position); // Safety from all pieces but knight
	bool CheckSafeAgainstKnight(Coord position); // Safety from knights
	bool SpaceIsSafeFromCheck(Coord ifIWasHere);
	bool SpaceIsSafeFromCheck();
	void AvailableMoves(PieceMoves* moves) override;
	void UnAvailableMoves(PieceMoves* checks);
	bool CouldITakeAt(Coord hypothetical) override;
};
