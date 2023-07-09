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

void PushMove(BoardPos from, BoardPos to, Unit* capturedUnit);

// Undo
void PopMove();
//Redo
void UnPopMove();

struct BoardState {

    size_t numUnits;

    _Field_size_part_(NUM_MAX_UNITS, numUnits)
    Unit units[NUM_MAX_UNITS];

} extern board;

// Previous move in the history
void GameStateDecrement();
// Next move in the history
void GameStateIncrement();

void ResetBoard(void);
void PlayBoard(void);
_Bool IncrementTurn(void);
void GameFlipbook(void);

#if _DEBUG
void PrintBoardDebug();
#endif

#endif // !BOARD_H