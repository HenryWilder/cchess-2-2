#include "UnitDirections.h"
#include "Pawn.h"

signed int Pawn::GetForward() const
{
	if (GetColor() == UnitColor::Black) return 1;
	else return -1;
}

Piece Pawn::GetPieceType() const
{
	return Piece::Pawn;
}

void Pawn::Move(Coord newPosition)
{
	m_moved = true;
	if (newPosition.y == GetLocation().y + 2 || newPosition.y == GetLocation().y - 2) en_pasant = true;
	Unit::Move(newPosition);
}

sprite::Sprite* Pawn::GetSpritePointer()
{
	return &sprite::unit::pawn;
}

void Pawn::AvailableMoves(PieceMoves* moves)
{
	// Template moves
	Coord possibleMoves[4];

	// Forward from the perspective of our pawn
	const int fw = GetForward();
	Coord p = GetLocation(); // Position

	possibleMoves[0] = { p.x,     p.y + fw };
	possibleMoves[1] = { p.x,     p.y + fw + fw }; // First turn only
	possibleMoves[2] = { p.x - 1, p.y + fw }; // Only if capturing
	possibleMoves[3] = { p.x + 1, p.y + fw }; // Only if capturing


	Coord confirmedMoves[6];

	unsigned char confirmedMoveCount = 0;

	// Can move forward one?
	if (ValidPos(possibleMoves[0]) && !m_boardIAmOf->IsUnitAtPos(possibleMoves[0])) confirmedMoves[confirmedMoveCount++] = possibleMoves[0];

	// Can move forward two?
	// No pawn will ever be starting at a position 2 moves behind an out-of-bounds position, so we don't have to validate the position.
	if (m_moved == false &&
		!m_boardIAmOf->IsUnitAtPos(possibleMoves[0]) && // Really weird edge-case
		!m_boardIAmOf->IsUnitAtPos(possibleMoves[1]))
	{
		confirmedMoves[confirmedMoveCount++] = possibleMoves[1];
	}

	// Can move diagonally?
	for (char i = 2; i < 4; ++i)
	{
		Unit* pEnemy = m_boardIAmOf->GetUnitAtPos((possibleMoves[i]));

		// Note that we don't have to check if the position is valid, as no enemy will be at an invalid position.
		if (UnitIsEnemy(pEnemy)) confirmedMoves[confirmedMoveCount++] = possibleMoves[i];

		//
		// En'passant
		//
		Coord passantPos = { possibleMoves[i].x, possibleMoves[i].y - fw };
		Pawn* passantPawn = dynamic_cast<Pawn*>(m_boardIAmOf->GetUnitAtPos(passantPos));

		if (UnitIsEnemy(passantPawn) && passantPawn->en_pasant) confirmedMoves[confirmedMoveCount++] = possibleMoves[i];
	}



	moves->SetMoves(confirmedMoves, confirmedMoveCount);
}

bool Pawn::CouldITakeAt(Coord hypothetical)
{
	int fwDirection = 1; // Default assumes black unit (because black is first in the enum definition (personal preference, does not affect code.))

	if (GetColor() == UnitColor::White) fwDirection = -1; // If the unit is found to be white, invert the forward direction.

	if (hypothetical == (m_position + Coord{ 1 /*right*/, fwDirection }) ||
		hypothetical == (m_position + Coord{ -1 /*left*/, fwDirection })) return true;
	else return false;
}