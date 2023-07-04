#pragma once
#include "Unit.h"

class King : public Unit
{
public:
	Piece GetPieceType() const override;
	bool m_moved = false;
	void Move(Coord newPosition) override;
	sprite::Sprite* GetSpritePointer() override;
	Unit* TestMoveSafety(Coord testPos);
	bool TestMoveSafetyValidate(Coord position);
	Unit* LineTraceSafety(Coord startPos, Coord direction);
	bool CanIBeTaken(const Coord position, const Coord direction);
	bool CheckSafetyDirectional(Coord position); // Safety from all pieces but knight
	bool CheckSafeAgainstKnight(Coord position); // Safety from knights
	bool SpaceIsSafeFromCheck(Coord ifIWasHere = { -1,-1 });
	void AvailableMoves(PieceMoves* moves) override;
	void UnAvailableMoves(PieceMoves* checks);
	bool CouldITakeAt(Coord hypothetical) override;
};
