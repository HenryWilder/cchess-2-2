#include "UnitDirections.h"

Coord CardinalDir(int i)
{
	/* Array of cardinal directions
	* [ ][0][ ]
	* [3]   [1]
	* [ ][2][ ]*/
	Coord cardinals[] = { { 0, 1 },{ 1, 0 },{ 0, -1 },{ -1, 0 } };
	return cardinals[i % 4]; // Pick the index from the array
}

Coord DiagonalDir(int i)
{
	/* Array of diagonal directions
	*[3][ ][0]
	*[ ]   [ ]
	*[2][ ][1]*/
	Coord diagonals[] = { { 1, 1 },{ 1, -1 },{ -1, -1 },{ -1, 1 } };
	return diagonals[i % 4]; // Pick the index from the array
}

Coord AllDir(int i)
{
	/* Array of all directions
	*[7][0][1]
	*[6]   [2]
	*[5][4][3]*/
	if (IsEven(i)) return CardinalDir(i / 2);	// Return cardinal on even input
	else return DiagonalDir((i - 1) / 2);	// Return diagonal on odd input
}

Coord KnightDir(int i)
{
	/* Array of all knight directions
	*  ==============================
	* The knight's movement array is created from a diagonal + a cardinal offset.
	*     [c0]    [c0]
	* [c3](d3)    (d0)[c1]
	*         init
	* [c3](d2)    (d1)[c1]
	*     [c2]    [c2]
	* 
	* Our index of that array will be in this order:
	*    [7]   [0]
	* [6]         [1]
	*       pos
	* [5]         [2]
	*    [4]   [3]
	* 
	* In other words:
	* Knight(0) = Diagonal(0) + Cardinal(0)
	* Knight(1) = Diagonal(0) + Cardinal(1)
	* Knight(2) = Diagonal(1) + Cardinal(1)
	* Knight(3) = Diagonal(1) + Cardinal(2)
	* Knight(4) = Diagonal(2) + Cardinal(2)
	* Knight(5) = Diagonal(2) + Cardinal(3)
	* Knight(6) = Diagonal(3) + Cardinal(3)
	* Knight(7) = Diagonal(3) + Cardinal(0)
	* 
	* Notice how the pattern for i in Cardinal(i) is the same as Diagonal(i + 1)
	* So the pattern for i in Diagonal can be thought of as floor(i / 2), while for Cardinal it would be ceil(i / 2)
	* 0: (floor(0 / 2) = 0)        + (ceil(0 / 2) = 0)       
	* 1: (floor(1 / 2) = 0.5 -> 0) + (ceil(1 / 2) = 0.5 -> 1)
	* 2: (floor(2 / 2) = 1)        + (ceil(2 / 2) = 1)       
	* 3: (floor(3 / 2) = 1.5 -> 1) + (ceil(3 / 2) = 1.5 -> 2)
	* 4: (floor(4 / 2) = 2)        + (ceil(4 / 2) = 2)       
	* 5: (floor(5 / 2) = 2.5 -> 2) + (ceil(5 / 2) = 2.5 -> 3)
	* 6: (floor(6 / 2) = 3)        + (ceil(6 / 2) = 3)       
	* 7: (floor(7 / 2) = 3.5 -> 3) + (ceil(7 / 2) = 3.5 -> 0) */

	return DiagonalDir(i / 2) + CardinalDir((i + 1) / 2);
}
