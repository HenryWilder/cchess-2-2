#include "UnitDirections.h"
#include "Knight.h"

Piece Knight::GetPieceType() const
{
	return Piece::Knight;
}

sprite::Sprite* Knight::GetSpritePointer()
{
	return &sprite::unit::knight;
}

void Knight::AvailableMoves(PieceMoves* moves)
{
	Coord confirmedMoves[8];

	unsigned char confirmedMoveCount = 0;

	// Relative space
	for (unsigned char i = 0; i < 8; ++i)
	{
		const Coord testPos = GetLocation() + KnightDir(i); // testPos is the offset location

		if (ValidPos(testPos)) // On the board
		{
			const Unit* testUnit = m_boardIAmOf->GetUnitAtPos(testPos);
			if (NullOrEnemy(testUnit)) confirmedMoves[confirmedMoveCount++] = testPos;
		}
	}

	moves->SetMoves(confirmedMoves, confirmedMoveCount);
}

bool Knight::CouldITakeAt(Coord hypothetical)
{
	// Find the hypothetical position in the list of possible positions
	for (int i = 0; i < 8; ++i)
	{
		Coord testPos = GetLocation() + KnightDir(i);
		if (hypothetical == testPos) return true;
	}
	return false;
}
