#include "Board.hpp"
#include "Unit.hpp"

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
	const Unit* unitAtPos = boardIAmOf->GetUnitAtPos(testPos);

	return NullOrEnemy(unitAtPos);
}

bool Unit::PieceIsBlocking(Coord testPos, Coord* confirmedMoves, unsigned char& confirmedMoveCount)
{
	const Unit* testUnit = boardIAmOf->GetUnitAtPos(testPos);

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

void Unit::Init(Coord pos, UnitColor color, Board* boardSpawningMe, unsigned char id)
{
	position = pos;
	team = color;
	boardIAmOf = boardSpawningMe;
	isHidden = false;
	id = id;
}

Coord Unit::GetLocation() const
{
	return position;
}

UnitColor Unit::GetColor() const
{
	return team;
}

UnitColor Unit::GetEnemyColor() const
{
	return (team == UnitColor::Black ? UnitColor::White : UnitColor::Black);
}

void Unit::Move(Coord newPosition)
{
	position = newPosition;
}

const sprite::Sprite* Unit::GetSpritePointer()
{
	return &sprite::unit::null;
}

void Unit::AvailableMoves(PieceMoves* moves) {}

Piece Unit::GetPieceType() const
{
	return Piece::Null;
}

bool Unit::IsHidden()
{
	return isHidden;
}

void Unit::Hide()
{
	isHidden = true;
}

void Unit::UnHide()
{
	isHidden = false;
}

unsigned char Unit::GetID()
{
	return id;
}

bool Unit::CouldITakeAt(Coord hypothetical)
{
	return false;
}
