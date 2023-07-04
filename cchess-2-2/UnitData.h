#pragma once

enum class Piece : unsigned char
{
	Null = 0,
	Pawn,
	Rook,
	Knight,
	Bishop,
	Queen,
	King,
	Empty = 0b111,
};

// The color of the piece
enum class UnitColor : bool
{
	Black = false,
	White = true,
};

// Data regarding a space on the board
struct UnitData
{
	UnitData() :
		color{},
		piece{}
	{}

	UnitColor color : 1;
	Piece piece : 3; // Piece::Null is considered erroneous. Use Piece::Empty if there is no piece.
};
