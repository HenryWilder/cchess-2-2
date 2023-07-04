#include "Unit.h"

enum class UnitColor : bool;

using namespace space;
using namespace game;

Coord CardinalDir(int i)
{
	/* Array of cardinal directions
	* [ ][0][ ]
	* [3]   [1]
	* [ ][2][ ]*/
	Coord cardinals[] = { { 0, 1 },{ 1, 0 },{ 0, -1 },{ -1, 0 } };
	return cardinals[i % 4]; // Pick the index from the array
}
Coord DiagonalDir(int i)
{
	/* Array of diagonal directions
	*[3][ ][0]
	*[ ]   [ ]
	*[2][ ][1]*/
	Coord diagonals[] = { { 1, 1 },{ 1, -1 },{ -1, -1 },{ -1, 1 } };
	return diagonals[i % 4]; // Pick the index from the array
}
Coord AllDir(int i)
{
	/* Array of all directions
	*[7][0][1]
	*[6]   [2]
	*[5][4][3]*/
	if (IsEven(i)) return CardinalDir(i / 2);	// Return cardinal on even input
	else return DiagonalDir((i - 1) / 2);	// Return diagonal on odd input
}
Coord KnightDir(int i)
{
	/* Array of all knight directions
	*  ==============================
	* The knight's movement array is created from a diagonal + a cardinal offset.
	*     [c0]    [c0]
	* [c3](d3)    (d0)[c1]
	*         init
	* [c3](d2)    (d1)[c1]
	*     [c2]    [c2]
	* 
	* Our index of that array will be in this order:
	*    [7]   [0]
	* [6]         [1]
	*       pos
	* [5]         [2]
	*    [4]   [3]
	* 
	* In other words:
	* Knight(0) = Diagonal(0) + Cardinal(0)
	* Knight(1) = Diagonal(0) + Cardinal(1)
	* Knight(2) = Diagonal(1) + Cardinal(1)
	* Knight(3) = Diagonal(1) + Cardinal(2)
	* Knight(4) = Diagonal(2) + Cardinal(2)
	* Knight(5) = Diagonal(2) + Cardinal(3)
	* Knight(6) = Diagonal(3) + Cardinal(3)
	* Knight(7) = Diagonal(3) + Cardinal(0)
	* 
	* Notice how the pattern for i in Cardinal(i) is the same as Diagonal(i + 1)
	* So the pattern for i in Diagonal can be thought of as floor(i / 2), while for Cardinal it would be ceil(i / 2)
	* 0: (floor(0 / 2) = 0)        + (ceil(0 / 2) = 0)       
	* 1: (floor(1 / 2) = 0.5 -> 0) + (ceil(1 / 2) = 0.5 -> 1)
	* 2: (floor(2 / 2) = 1)        + (ceil(2 / 2) = 1)       
	* 3: (floor(3 / 2) = 1.5 -> 1) + (ceil(3 / 2) = 1.5 -> 2)
	* 4: (floor(4 / 2) = 2)        + (ceil(4 / 2) = 2)       
	* 5: (floor(5 / 2) = 2.5 -> 2) + (ceil(5 / 2) = 2.5 -> 3)
	* 6: (floor(6 / 2) = 3)        + (ceil(6 / 2) = 3)       
	* 7: (floor(7 / 2) = 3.5 -> 3) + (ceil(7 / 2) = 3.5 -> 0) */

	return DiagonalDir(i / 2) + CardinalDir((i + 1) / 2);
}

bool Unit::NullOrEnemy(const Unit* unit)
{
	if (unit == nullptr) return true;
	else return (unit->GetColor() != GetColor());
}

bool Unit::UnitIsEnemy(const Unit* unit)
{
	return (unit != nullptr && unit->GetColor() != GetColor());
}

// Used for testing the aliance of a unit at a space we have the coordinates of, but haven't yet searched for a unit in.
bool Unit::SpaceHasNoTeammate(const Coord testPos)
{
	const Unit* unitAtPos = m_boardIAmOf->GetUnitAtPos(testPos);

	return NullOrEnemy(unitAtPos);
}

bool Unit::PieceIsBlocking(Coord testPos, Coord* confirmedMoves, unsigned char& confirmedMoveCount)
{
	const Unit* testUnit = m_boardIAmOf->GetUnitAtPos(testPos);

	bool thereIsUnit = testUnit != nullptr;

	bool unitIsTeammate = false;

	if (thereIsUnit) unitIsTeammate = (testUnit->GetColor() == GetColor());

	if (!unitIsTeammate) {
		confirmedMoves[confirmedMoveCount++] = testPos; // The unit is an enemy
	} return thereIsUnit;
}

void Unit::LineTrace(Coord* confirmedMoves, unsigned char& confirmedMoveCount, const Coord direction)
{
	for (Coord testPos = GetLocation() + direction; ValidPos(testPos); testPos = (testPos + direction))
	{
		if (PieceIsBlocking(testPos, confirmedMoves, confirmedMoveCount)) break; // If there is a unit at all, break. Append blocking unit if they are an enemy.
	}
}

void PieceMoves::SetMoves(const Coord* moves, const unsigned char count)
{
	m_availableMovesCount = count;

	for (unsigned char i = 0; i < m_availableMovesCount; ++i)
	{
		m_available[i] = *(moves + i); // The next index of the moves array
	}
}

int PieceMoves::GetMoves(Coord* moves)
{
	moves = m_available;
	return (int)m_availableMovesCount;
}

bool PieceMoves::MoveIsValid(Coord move) const
{
	bool valid = false;

	for (unsigned int i = 0; i < m_availableMovesCount; ++i)
	{
		if (move == m_available[i])
		{
			valid = true;
			break;
		}
	}

	return valid;
}

void Unit::Init(Coord pos, UnitColor color, Board* boardSpawningMe, unsigned char id)
{
	m_position = pos;
	m_team = color;
	m_boardIAmOf = boardSpawningMe;
	b_hidden = false;
	m_ID = id;
}

Coord Unit::GetLocation() const
{
	return m_position;
}

UnitColor Unit::GetColor() const
{
	return m_team;
}

UnitColor Unit::GetEnemyColor() const
{
	return (m_team == UnitColor::Unit_Black ? UnitColor::Unit_White : UnitColor::Unit_Black);
}

void Unit::Move(Coord newPosition)
{
	m_position = newPosition;
}

sprite::Sprite* Unit::GetSpritePointer() {	return &sprite::unit::null;	}

void Unit::AvailableMoves(PieceMoves* moves) {}

Piece Unit::GetPieceType() const
{
	return Piece::Null;
}

bool Unit::IsHidden()
{
	return b_hidden;
}

void Unit::Hide()
{
	b_hidden = true;
}

void Unit::UnHide()
{
	b_hidden = false;
}

unsigned char Unit::GetID()
{
	return m_ID;
}

bool Unit::CouldITakeAt(Coord hypothetical)
{
	return false;
}
