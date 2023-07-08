#include "Rendering.hpp"
#include "PieceMoves.hpp"
#include "UnitDirections.hpp"
#include "Queen.hpp"
#include "Board.hpp"

const sprite::Sprite* Queen::GetSpritePointer()
{
	return &sprite::unit::queen;
}

void Queen::AvailableMoves(PieceMoves* moves)
{
	Coord confirmedMoves[space::board::sideTileCount * 4];

	unsigned char confirmedMoveCount = 0;

	Coord testPos;

	// All directions
	for (int direction = 0; direction < 8; ++direction)
	{
		LineTrace(confirmedMoves, confirmedMoveCount, Clockwise(direction));
	}

	moves->SetMoves(confirmedMoves, confirmedMoveCount);
}

// We are assuming that a straight line of sight has already been established for this to be called.
bool Queen::CouldITakeAt(Coord hypothetical)
{
	return true; // In the case of the queen, the answer is yes.
}
