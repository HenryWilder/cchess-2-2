#ifndef BOARD_H
#define BOARD_H
#include "constants.h"
#include "unit.h"
#include <sal.h>

void ResetBoard(void);
void PlayBoard(void);
_Bool IncrementTurn(void);

void PushMove(BoardPos from, BoardPos to);

void PopMove();

struct BoardState {

    size_t numUnits;

    _Field_size_part_(NUM_MAX_UNITS, numUnits)
    Unit units[NUM_MAX_UNITS];

} extern board;

void GameStateIncrement();
void GameStateDecrement();

void GameFlipbook(void);

#endif // !BOARD_H