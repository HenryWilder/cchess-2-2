#include "UnitDirections.h"
#include "Rook.h"

Piece Rook::GetPieceType() const
{
	return Piece::Rook;
}

void Rook::Move(Coord newPosition)
{
	m_moved = true;
	Unit::Move(newPosition);
}

sprite::Sprite* Rook::GetSpritePointer()
{
	return &sprite::unit::rook;
}

void Rook::AvailableMoves(PieceMoves* moves)
{
	Coord confirmedMoves[space::game::sideTileCount * 2];

	unsigned char confirmedMoveCount = 0;

	Coord testPos;

	// Straight lines
	for (int direction = 0; direction < 4; ++direction)
	{
		LineTrace(confirmedMoves, confirmedMoveCount, CardinalDir(direction));
	}

	moves->SetMoves(confirmedMoves, confirmedMoveCount);
}

// We are assuming that a straight line of sight has already been established for this to be called.
bool Rook::CouldITakeAt(Coord hypothetical)
{
	if (hypothetical.x == m_position.x ||
		hypothetical.y == m_position.y) return true;
	else return false;
}
