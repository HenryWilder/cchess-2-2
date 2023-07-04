#pragma once
#include "Utils.h"
#include "Rendering.h"
#include "UnitData.h"

class Board;

struct PieceMoves
{
	Coord available[space::game::sideTileCount * 4];
	unsigned char numAvailableMoves = 0;

	// Set all of the moves at once
	void SetMoves(const Coord* moves, const unsigned char count);

	// For modifying an outside array of moves. Returns the number of moves valid in the array being modified.
	int GetMoves(Coord* moves);

	// Takes a coord as input and checks whether it is in the list of valid moves
	bool MoveIsValid(Coord move) const;
};

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
	Coord position;

	UnitColor team;

	// Set once during initialization. Never override again.
	Board* boardIAmOf;

	// Should we hide the unit from the renderer?
	bool isHidden;

	unsigned char id;
};

//int size = sizeof(Unit);
//int align = alignof(Unit);

#include "Pawn.h"
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "Queen.h"
#include "King.h"
