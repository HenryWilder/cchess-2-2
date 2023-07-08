#include "PieceMoves.hpp"

void PieceMoves::SetMoves(const Coord* moves, const unsigned char count)
{
	numAvailableMoves = count;

	for (unsigned char i = 0; i < numAvailableMoves; ++i)
	{
		available[i] = *(moves + i); // The next index of the moves array
	}
}

int PieceMoves::GetMoves(Coord* moves)
{
	moves = available;
	return (int)numAvailableMoves;
}

bool PieceMoves::MoveIsValid(Coord move) const
{
	bool valid = false;

	for (unsigned int i = 0; i < numAvailableMoves; ++i)
	{
		if (move == available[i])
		{
			valid = true;
			break;
		}
	}

	return valid;
}
