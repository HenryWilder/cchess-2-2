#pragma once
#include "Utils.h"
#include "Rendering.h"
#include "Board.h"

enum class Piece : unsigned char
{
	Null = 0,
	Pawn,
	Rook,
	Knight,
	Bishop,
	Queen,
	King,
	Empty = 0b111,
};

struct PieceMoves
{
	Coord m_available[space::game::sideTileCount * 4];
	unsigned char m_availableMovesCount = 0;

	// Set all of the moves at once
	void SetMoves(const Coord* moves, const unsigned char count);

	// For modifying an outside array of moves. Returns the number of moves valid in the array being modified.
	int GetMoves(Coord* moves);

	// Takes a coord as input and checks whether it is in the list of valid moves
	bool MoveIsValid(Coord move) const;
};

// The color of the piece
enum class UnitColor : bool
{
	Black = false,
	White = true,
};

struct Unit
{
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

	virtual sprite::Sprite* GetSpritePointer();
	virtual void AvailableMoves(PieceMoves* moves);
	virtual Piece GetPieceType() const;
	bool IsHidden();
	void Hide();
	void UnHide();
	unsigned char GetID();
	virtual bool CouldITakeAt(Coord hypothetical); // Used in code for king

protected:
	Coord m_position; // 8 bytes
	UnitColor m_team; // 8 bytes
					  // Set once during initialization. Never override again.
	Board* m_boardIAmOf; // 8 bytes
						 // Should we hide the unit from the renderer?
	bool b_hidden; // 1 byte
	unsigned char m_ID; // 1 byte
						// 2 bytes left in alignment
};

//int size = sizeof(Unit);
//int align = alignof(Unit);

#include "Pawn.h"
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "Queen.h"
#include "King.h"
