#ifndef BOARD_H
#define BOARD_H
#include "constants.h"
#include "unit.h"
#include <sal.h>

// Keep parity with vcruntime.h
#ifdef _WIN64
typedef unsigned __int64 size_t;
#else
typedef unsigned int     size_t;
#endif

extern size_t turnIndex;
UnitTeam CurrentTeam(void);
UnitTeam OpponentTeam(void);

void ApplyCurrentMove(void);
void UnapplyCurrentMove(void);

void PushMove(BoardPos from, BoardPos to);

// Undo
void PopMove(void);
//Redo
void UnPopMove(void);

struct BoardState {

    size_t numUnits;

    _Field_size_part_(NUM_MAX_UNITS, numUnits)
    Unit units[NUM_MAX_UNITS];

} extern board;

// Previous move in the history
void GameStateDecrement(void);
// Next move in the history
void GameStateIncrement(void);

void ResetBoard(void);
void PlayBoard(void);
void DecrementTurn(void);
_Bool IncrementTurn(void);
void GameFlipbook(void);

#if _DEBUG
void PrintBoardDebug(void);
#endif

#endif // !BOARD_H