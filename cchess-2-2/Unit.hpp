#pragma once
#include "Utils.hpp"
#include "UnitData.hpp"

class Board;
struct PieceMoves;
namespace sprite { struct Sprite; }

class Unit
{
public:
	// Re-initializes the piece in the case that a constructor won't do.
	void Init(Coord pos, UnitColor color, Board* boardSpawningMe, unsigned char id);

	Coord GetLocation() const;
	UnitColor GetColor() const;
	UnitColor GetEnemyColor() const;

	bool NullOrEnemy(const Unit* unit); // Either the unit is null or an enemy
	bool UnitIsEnemy(const Unit* unit); // The unit is NOT null && is an enemy
	bool SpaceHasNoTeammate(const Coord testPos);
protected:
	bool PieceIsBlocking(Coord testPos, Coord* confirmedMoves, unsigned char& confirmedMoveCount);
	void LineTrace(Coord* confirmedMoves, unsigned char& confirmedMoveCount, const Coord direction);
public:
	virtual void Move(Coord newPosition);

	virtual const sprite::Sprite* GetSpritePointer();
	virtual void AvailableMoves(PieceMoves* moves);
	virtual Piece GetPieceType() const;
	bool IsHidden();
	void Hide();
	void UnHide();
	unsigned char GetID();
	virtual bool CouldITakeAt(Coord hypothetical); // Used in code for king

protected:
	Coord position = {};

	UnitColor team = UnitColor(0);

	// Set once during initialization. Never override again.
	Board* boardIAmOf = nullptr;

	// Should we hide the unit from the renderer?
	bool isHidden = false;

	unsigned char id = 0;
};
