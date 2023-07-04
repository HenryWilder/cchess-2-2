#include "Unit.h"

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
	return (m_team == UnitColor::Black ? UnitColor::White : UnitColor::Black);
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
