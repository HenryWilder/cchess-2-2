#include "UnitDirections.h"
#include "Board.h"
#include "King.h"

Piece King::GetPieceType() const
{
	return Piece::King;
}

void King::Move(Coord newPosition)
{
	isMoved = true;
	Unit::Move(newPosition);
}

const sprite::Sprite* King::GetSpritePointer()
{
	return &sprite::unit::king;
}

Unit* King::TestMoveSafety(Coord testPos)
{
	Unit* unit = boardIAmOf->GetUnitAtPos(testPos);

	if (unit != nullptr) return unit;
	return nullptr; // Nobody is there
}

bool King::TestMoveSafetyValidate(Coord position)
{
	Unit* unit = TestMoveSafety(position);
	return (UnitIsEnemy(unit));
}

Unit* King::LineTraceSafety(Coord startPos, Coord direction)
{
	Unit* unit = nullptr;

	for (Coord testPos = startPos + direction; ValidPos(testPos); testPos = (testPos + direction))
	{
		unit = TestMoveSafety(testPos);

		if (unit != nullptr /*Space is not empty*/ && unit != this /*Ignore self*/)
		{
			if (unit->GetColor() == GetColor()) break; // The unit is a teammate, we cannot take them but they block our movement.
			else return unit; // The unit is an enemy
		}
	}
	// Stop. We have left the board.
	return nullptr;
}

bool King::CanIBeTaken(const Coord position, const Coord direction)
{
	Unit* potentialEnemy = LineTraceSafety(position, direction);

	// Does the enemy exist? An empty space cannot take us.
	if (potentialEnemy != nullptr && potentialEnemy->GetColor() != GetColor()) return potentialEnemy->CouldITakeAt(position);
	else return false; // There was no piece/they were a teammate
}

bool King::CheckSafetyDirectional(Coord position)
{
	for (int i = 0; i < 8; ++i) {
		if (CanIBeTaken(position, AllDir(i))) return false; // If i can be taken, return false.
	}
	return true; // Nobody was found who could take us
}

bool King::CheckSafeAgainstKnight(Coord position)
{
	Unit* unit;

	for (int i = 0; i < 8; ++i)
	{
		const Coord testPos = position + KnightDir(i);

		unit = boardIAmOf->GetUnitAtPos(testPos);

		//m_boardIAmOf->DrawBoardSpaceColored(testPos, RGB(127, 127, 127)); // Debug

		if (UnitIsEnemy(unit) &&
			unit->GetPieceType() == Piece::Knight)
		{
			//m_boardIAmOf->DrawBoardSpaceColored(testPos, RGB(255, 127, 127)); // Debug
			return  false;
		}
	}
	return true;
}

bool King::SpaceIsSafeFromCheck(Coord ifIWasHere)
{
	return CheckSafetyDirectional(ifIWasHere) && CheckSafeAgainstKnight(ifIWasHere);
}

bool King::SpaceIsSafeFromCheck()
{
	return SpaceIsSafeFromCheck(GetLocation());
}

void King::AvailableMoves(PieceMoves* moves)
{
	/*The array of moves we know are accurate. Starts empty, so that we can append new moves when we confirm them.
	* In this way, the confirmed moves are at the beginning of the array, and invalid moves are not in the list,
	* making it so that no fancy "add this move but then skip this one" is needed when writing to the output moveset. */
	Coord confirmedMoves[8];

	/*The total number of moves at a given instant = the index of the current last move + 1 (or the index of a brand new move).
	* This is how we fake a dynamic array in an array of constant size. */
	unsigned char confirmedMoveCount = 0;

	for (unsigned char i = 0; i < 8; ++i)
	{
		const Coord testPos = GetLocation() + AllDir(i); // testPos is the offset location

		if (ValidPos(testPos) && // Check that the position is on the board
			SpaceHasNoTeammate(testPos) && // The unit at the position, be there one at all, is not a teammate
			SpaceIsSafeFromCheck(testPos)) // Would that space be safe from putting me in check?
		{
			confirmedMoves[confirmedMoveCount++] = testPos; // Append the current array of confirmed moves with the move we are currently checking
		}
	}

	moves->SetMoves(confirmedMoves, confirmedMoveCount); // Write to the output
}

void King::UnAvailableMoves(PieceMoves* checks)
{
	Coord confirmedMoves[8];

	unsigned char confirmedMoveCount = 0;

	for (unsigned char i = 0; i < 8; ++i)
	{
		const Coord testPos = GetLocation() + AllDir(i); // testPos is the offset location

		if (ValidPos(testPos) && // Check that the position is on the board
			SpaceHasNoTeammate(testPos) && // The unit at the position, be there one at all, is not a teammate
			!SpaceIsSafeFromCheck(testPos)) // Would that space be safe from putting me in check?
		{
			confirmedMoves[confirmedMoveCount++] = testPos; // Append the current array of confirmed moves with the move we are currently checking
		}
	}

	checks->SetMoves(confirmedMoves, confirmedMoveCount); // Write to the output
}

bool King::CouldITakeAt(Coord hypothetical)
{
	return false; // @TODO
}
