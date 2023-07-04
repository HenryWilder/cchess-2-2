#include "Queen.h"

Piece Queen::GetPieceType() const
{
	return Piece::Piece_Queen;
}

sprite::Sprite* Queen::GetSpritePointer()
{
	return &sprite::unit::queen;
}

void Queen::AvailableMoves(PieceMoves* moves)
{
	Coord confirmedMoves[sideTileCount * 4];

	unsigned char confirmedMoveCount = 0;

	Coord testPos;

	// All directions
	for (int direction = 0; direction < 8; ++direction)
	{
		LineTrace(confirmedMoves, confirmedMoveCount, AllDir(direction));
	}

	moves->SetMoves(confirmedMoves, confirmedMoveCount);
}

// We are assuming that a straight line of sight has already been established for this to be called.
bool Queen::CouldITakeAt(Coord hypothetical)
{
	return true; // In the case of the queen, the answer is yes.
}
