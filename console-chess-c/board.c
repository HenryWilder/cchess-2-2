#include "board.h"
#include "unit.h"
#include <assert.h>
#include <stdlib.h>

void ResetBoard()
{
    // todo
}

void PlayBoard()
{
    // todo
}

_Bool IncrementTurn()
{
    return 0;
}

typedef struct Move {
    BoardPos from, to;
} Move;

struct History {

    size_t capMoves;

    _Field_range_(0, capMoves)
    size_t numMoves;

    _Field_size_(capMoves)
    Move* moves;

} history = {
    .capMoves = 0,
    .numMoves = 0,
    .moves    = NULL,
};

struct BoardState board = {
    .numUnits = 0,
};

size_t historyIndex = 0; // Tracks GameState position in history

void memcpy(_Out_writes_bytes_all_(bytes) void* dest, _In_reads_bytes_(bytes) const void* src, size_t bytes)
{
          char* destBytes =       (char*)dest;
    const char* srcBytes  = (const char*)src;

    for (size_t i = 0; i < bytes; ++i)
    {
        destBytes[i] = srcBytes[i];
    }
}

_Return_type_success_(1) _Bool ReserveHistory(size_t newSize)
{
    if (newSize <= history.capMoves)
    {
        return 0;
    }

    Move* newArray = (Move*)malloc(newSize * sizeof(Move));

    if (newArray == NULL)
    {
        return 0;
    }

    if (history.moves != NULL)
    {
        memcpy(newArray, history.moves, history.numMoves * sizeof(Move));
        free(history.moves);
    }

    history.moves = newArray;
    history.capMoves = newSize;

    return 1;
}

void PushMove(BoardPos from, BoardPos to)
{
    if (history.numMoves == history.capMoves)
    {
        ReserveHistory((history.capMoves != 0)
            ? (history.capMoves * 2)
            : 32);
    }

    history.moves[history.numMoves].from = from;
    history.moves[history.numMoves].to   = to;
    ++history.numMoves;
}

void PopMove()
{
    assert(history.numMoves > 0);

    --history.numMoves;
}

void GameStateIncrement()
{
    assert(historyIndex > 0);

    // todo

    --historyIndex;
}

void GameStateDecrement()
{
    assert(historyIndex < (history.numMoves - 1));
    
    // todo

    ++historyIndex;
}

void GameFlipbook()
{
    // todo
}
