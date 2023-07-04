#pragma once
#include <iostream>
#include <vector>
#include "Utils.h"
#include "Rendering.h"
#include "Input.h"
#include "UnitData.h"

class Unit;
struct PieceMoves;

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

enum class Phase {
	Select = 0,
	HandleSelect = 1,
	Move = 2,
	Wrapup = 3,
};

class Board
{
private:
	constexpr static int width = space::game::sideTileCount;
	constexpr static int height = space::game::sideTileCount;

	int turn = 0;
	std::vector<Unit*> whiteUnits;
	std::vector<Unit*> blackUnits;
	BoardStateMemory m_history[50];

	std::vector<Unit*>& GetTeamArray(UnitColor team);
	const std::vector<Unit*>& GetTeamArrayReadOnly(UnitColor team) const;

	void BuildRoyalty(int y, UnitColor col, unsigned char& unitID);
	void ConstructNewUnit(Coord pos, Piece type, UnitColor color, unsigned char& unitID);

	UnitColor CurrentTeam();
	UnitColor OpponentTeam();

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
	Unit* GetTeamUnitAtPos(Coord pos, UnitColor team);
	Unit* GetUnitAtPos(Coord pos);
	bool IsTeamAtPos(Coord pos, UnitColor team);
	bool IsUnitAtPos(Coord pos);

	void ResetBoard();

	// Draws the space on the board with the input color and the piece at that space
	void DrawBoardSpaceColored(Coord pos, COLORREF color, bool effect = false);

	// Draws the space on the board with the input color and the piece at that space
	void DrawBoardSpaceColored(Coord pos, Color color, bool effect = false);

	// Draws the space as it is without any selection or effects. Draws the unit there if there is one.
	void DrawBoardSpaceReset(Coord pos);

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