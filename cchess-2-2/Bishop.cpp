#include "UnitDirections.h"
#include "Bishop.h"

Piece Bishop::GetPieceType() const
{
	return Piece::Bishop;
}

const sprite::Sprite* Bishop::GetSpritePointer()
{
	return &sprite::unit::bishop;
}

void Bishop::AvailableMoves(PieceMoves* moves)
{
	Coord confirmedMoves[space::game::sideTileCount * 3];

	unsigned char confirmedMoveCount = 0;

	Coord testPos;

	// Diagonals
	for (int direction = 0; direction < 4; ++direction)
	{
		LineTrace(confirmedMoves, confirmedMoveCount, DiagonalDir(direction));
	}

	moves->SetMoves(confirmedMoves, confirmedMoveCount);
}

// We are assuming that a straight line of sight has already been established for this to be called.
bool Bishop::CouldITakeAt(Coord hypothetical)
{
	if (hypothetical.x != position.x &&
		hypothetical.y != position.y) return true;
	else return false;
}
