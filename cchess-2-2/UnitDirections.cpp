#include "UnitDirections.hpp"

// Identical to sine for integer multiples of pi/2 radians
int isin(int x)
{
	int m = ((x + 1) % 4) - 1;
	return m >= 1 ? 2 - m : m;
}

// Identical to cosine for integer multiples of pi/2 radians
int icos(int x)
{
	int m = ((x + 2) % 4) - 1;
	return m >= 1 ? 2 - m : m;
}

// Starts at 12:00
Coord Cardinal(int i)
{
	int x = -i + 1;

	// cos/sin
	int c{ icos(i) },
		s{ isin(i) };

	return Coord(c, s);
}

// Starts at 1:30
Coord Diagonal(int i)
{
	int x = -i + 1;

	// cos/sin
	int c{ icos(i) },
		s{ isin(i) };

	return Coord(c + s, s - c);
}

// Starts at 12:00
Coord Clockwise(int i)
{
	int x = -i + 1;

	// Floor half
	int ihf = i / 2;

	// cos/sin half floor
	int chf{ icos(ihf) },
		shf{ isin(ihf) };

	return (i & 1)
		? Coord(chf, shf)
		: Coord(chf + shf, chf - shf);
}

// Starts at 12:00
Coord KnightWise(int i)
{
	int x = -i + 1;

	// Floor half
	int ihf = i / 2;

	// cos/sin half floor
	int chf{ icos(ihf) },
		shf{ isin(ihf) };

	// Ceil half
	int ihc = i / 2 + i % 2;

	// cos/sin half ceil
	int chc{ icos(ihc) },
		shc{ isin(ihc) };

	return Coord(chf + (chc + shc), shf + (chc - shc));
}
