#pragma once
#include "Utils.hpp"

struct PieceMoves
{
	Coord available[space::board::sideTileCount * 4];
	unsigned char numAvailableMoves = 0;

	// Set all of the moves at once
	void SetMoves(const Coord* moves, const unsigned char count);

	// For modifying an outside array of moves. Returns the number of moves valid in the array being modified.
	int GetMoves(Coord* moves);

	// Takes a coord as input and checks whether it is in the list of valid moves
	bool MoveIsValid(Coord move) const;
};
