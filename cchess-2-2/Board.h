#pragma once
#include "Utils.h"
#include <iostream>
#include <vector>
#include "Unit.h"
#include "Rendering.h"
#include "Input.h"

char NumToLetter(int value);
int LetterToNum(char letter);
char CharToValue(char character);
void ClearTextLine(int start = 0, int count = 1);

// Data regarding a space on the board
struct UnitData
{
	UnitColor color : 1;
	Piece piece : 3; // Piece::Null is considered erroneous. Use Piece::Empty if there is no piece.
};

class BoardStateMemory
{
private:
	UnitData m_stateData[space::game::sideTileCount][space::game::sideTileCount];

public:
	UnitData  operator[](Coord coord) const;
	UnitData& operator[](Coord coord);
};

// Creates unit data
// Input nullptr for empty space
UnitData MakeUnitData(Unit* unit);

class Board
{
private:
	// Member properties
	int width = 0;
	int height = 0;
	int turn = 0;
	std::vector<Unit*> whiteUnits;
	std::vector<Unit*> blackUnits;
	BoardStateMemory m_history[50];

	// Functions
	const std::vector<Unit*>* GetTeamArrayReadOnly(UnitColor team);
	std::vector<Unit*>* GetTeamArray(UnitColor team);

	void BuildRoyalty(int y, UnitColor col, unsigned char& unitID);
	void ConstructNewUnit(Coord pos, Piece type, UnitColor color, unsigned char& unitID);

	UnitColor CurrentTeam();
	UnitColor OpponentTeam();

public:
	Unit* GetTeamUnitAtPos(Coord pos, UnitColor team);
	Unit* GetUnitAtPos(Coord pos);
	bool IsTeamAtPos(Coord pos, UnitColor team);
	bool IsUnitAtPos(Coord pos);

	void ResetBoard(int _width, int _height = 0);

	void DrawBoardSpaceColored(Coord pos, COLORREF color, bool effect = false); // Draws the space on the board with the input color and the piece at that space
	void DrawBoardSpaceColored(Coord pos, Color color, bool effect = false); // Draws the space on the board with the input color and the piece at that space
	void DrawBoardSpaceReset(Coord pos);

	enum class Phase {
		Select = 0,
		HandleSelect = 1,
		Move = 2,
		Wrapup = 3,
	};

private: // Helper functions
	Coord WaitForClick(Phase turnPhase, const PieceMoves* pMoves = nullptr, const sprite::Sprite* sprite = nullptr, bool team = 0);
	//Coord TakePosInput();
	void MovePiece(Unit* unit, Coord moveTo);

	void DrawPossibleMoves(PieceMoves* moves, const UnitColor team);
	void UnDrawPossibleMoves(PieceMoves* moves);

	bool SelectPhase(const UnitColor team, Coord& input, Unit*& unit, PieceMoves* moves);
	bool HandleSelection(Coord input, Unit*& unit, PieceMoves* moves);
	int MovePhase(Coord& input, Coord& output, Unit*& unit, PieceMoves* moves, const UnitColor team);
	bool WrapUpTurn(Coord& input, Coord& output, Unit*& unit, PieceMoves* moves);
	Unit* FindKingFromTeam(UnitColor team);
	void ResetEnPasant();


public:
	void PlayBoard();
	void PrintBoard();

	void AddUnit(Unit* unit);
	void RemoveUnit(Unit* unit);

	void StoreBoardState();
	bool IncrementTurn(); // Returns whether the game is over
	void DrawBoardState(int state);
	int FlipbookWFClick(int state);
	void GameFlipbook();
};