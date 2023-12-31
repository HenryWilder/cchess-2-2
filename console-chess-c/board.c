#include "input.h"
#include "board.h"
#include "unit.h"
#include "output.h"
#include <assert.h>
#include <stdlib.h>
#include <Windows.h>

#if _DEBUG
#include <stdio.h>
#endif

size_t turnIndex = 0;

UnitTeam CurrentTeam()
{
    return turnIndex & 1 ? TEAM_BLACK : TEAM_WHITE;
}

UnitTeam OpponentTeam()
{
    return CurrentTeam() == TEAM_WHITE ? TEAM_BLACK : TEAM_WHITE;
}

typedef struct Move {
    BoardPos from, to;
    UnitType x; // Use UNIT_NONE to indicate no unit is captured
    _Bool isCaptureMoved;
} Move;

struct History {

    size_t capMoves;

    _Field_range_(0, capMoves)
    size_t capRedoMoves;

    _Field_range_(0, capMoves)
    size_t numMoves;

    _Field_size_(capMoves)
    Move* moves;

} history = {
    .capMoves     = 0,
    .capRedoMoves = 0,
    .numMoves     = 0,
    .moves        = (Move*)NULL,
};

struct BoardState board = {
    .numUnits = 0,
};

/**
 * Finds the index of the unit at the coordinates(if any exists).
 * Returns board.numUnits if not found.
 */
_Return_type_success_(return < board.numUnits) _Must_inspect_result_ size_t IndexOfUnitAtPosition(BoardPosCoord_t x, BoardPosCoord_t y)
{
    for (size_t i = 0; i < board.numUnits; ++i)
    {
        const BoardPos pos = board.units[i].position;
        if (pos.x == x && pos.y == y)
        {
            return i;
        }
    }
    return board.numUnits;
}

/**
 * Finds the index of the unit at the coordinates (if any exists).  
 * Returns board.numUnits if not found.  
 * Prefer IndexOfUnitAtPosition() over constructing a BoardPos.
 */
_Return_type_success_(return < board.numUnits) _Must_inspect_result_ size_t IndexOfUnitAtBoardPos(BoardPos pos)
{
    return IndexOfUnitAtPosition(pos.x, pos.y);
}

_Return_type_success_(return != NULL) _Must_inspect_result_ Unit* UnitAtPosition(BoardPosCoord_t x, BoardPosCoord_t y)
{
    size_t index = IndexOfUnitAtPosition(x, y);

    _Bool isUnitAtPosition = (index != board.numUnits);

    Unit* unitPtr = isUnitAtPosition
        ? &(board.units[index])
        : NULL;

    return unitPtr;
}

// Prefer UnitAtPosition() over constructing a BoardPos
_Return_type_success_(return != NULL) _Must_inspect_result_ Unit* UnitAtBoardPos(BoardPos pos)
{
    return UnitAtPosition(pos.x, pos.y);
}

void PushUnitRaw(Unit unit)
{
    board.units[board.numUnits++] = unit;
}

void PushUnit(BoardPosCoord_t x, BoardPosCoord_t y, UnitType type, UnitTeam team)
{
    PushUnitRaw(InitUnit(x, y, type, team));
}

/**
 * Assume all unit pointers are invalidated when this is called.
 */
void RemoveUnitAtIndex(_In_range_(0, (board.numUnits - 1)) size_t index)
{
    assert(index < board.numUnits);

    for (size_t i = index + 1; i < board.numUnits; ++i)
    {
        board.units[i - 1] = board.units[i];
    }
    --board.numUnits;
}

/**
 * Prefer RemoveUnitAtIndex() if unit index is already known
 * Assume all unit pointers are invalidated when this is called.
 */
void RemoveUnit(Unit* unit)
{
    assert(unit != NULL);

    size_t index = board.numUnits;
    for (size_t i = 0; i < board.numUnits; ++i)
    {
        if (&(board.units[i]) == unit)
        {
            index = i;
            break;
        }
    }

    if (index == board.numUnits)
    {
        return;
    }

    RemoveUnitAtIndex(index);
}

size_t historyIndex = 0; // Tracks GameState position in history

#if 0 // memcpy is not defined
void memcpy(_Out_writes_bytes_all_(bytes) void* dest, _In_reads_bytes_(bytes) const void* src, size_t bytes)
{
    char* destBytes =       (char*)dest;
    const char* srcBytes  = (const char*)src;

    for (size_t i = 0; i < bytes; ++i)
    {
        destBytes[i] = srcBytes[i];
    }
}
#endif

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

void MoveUnitAtPosition(BoardPos at, BoardPos to)
{
    Unit* subjectUnit = UnitAtBoardPos(at);
    assert(subjectUnit != NULL);
    subjectUnit->position = to;
}

void RemoveUnitAtPosition(BoardPos at)
{
    size_t targetUnitIndex = IndexOfUnitAtBoardPos(at);
    assert(targetUnitIndex != board.numUnits);
    RemoveUnitAtIndex(targetUnitIndex);
}

void ApplyMove(Move move)
{
    if (move.x != UNIT_NONE)
    {
        RemoveUnitAtPosition(move.to);
    }

    MoveUnitAtPosition(move.from, move.to);
}

void UnapplyMove(Move move)
{
    MoveUnitAtPosition(move.to, move.from);

    if (move.x != UNIT_NONE)
    {
        Unit reincarnatedUnit = {
            .position = move.to,
            .type = move.x,
            .team = OpponentTeam(),
            .isMoved = move.isCaptureMoved,
        };
        PushUnitRaw(reincarnatedUnit);
    }
}

void ApplyCurrentMove()
{
    ApplyMove(history.moves[historyIndex++]);
}

void UnapplyCurrentMove()
{
    UnapplyMove(history.moves[--historyIndex]);
}

void PushMove(BoardPos from, BoardPos to)
{
    if (history.numMoves == history.capMoves)
    {
        ReserveHistory((history.capMoves != 0)
            ? (history.capMoves * 2)
            : 32);
    }

    Unit* capturedUnit = UnitAtBoardPos(to);

    assert(IndexOfUnitAtBoardPos(from) != board.numUnits); // Cannot push pieceless move (legality is not checked here)

    Move latestMove = {
        .from = from,
        .to = to,
        .x = capturedUnit ? capturedUnit->type : UNIT_NONE,
        .isCaptureMoved = capturedUnit && capturedUnit->isMoved,
    };

    __assume((history.moves[history.numMoves], 1));
    history.moves[history.numMoves++] = latestMove;
    history.capRedoMoves = history.numMoves;
}

// For undoing
void PopMove()
{
    assert(history.numMoves > 0);

    --history.numMoves;
}

// For redoing
void UnPopMove()
{
    if (history.numMoves < history.capRedoMoves)
    {
        ++history.numMoves;
    }
}

void GameStateDecrement()
{
    assert(historyIndex > 0);

    --historyIndex;

    UnapplyMove(history.moves[historyIndex]);
}

void GameStateIncrement()
{
    assert(historyIndex < (history.numMoves - 1));
    
    ApplyMove(history.moves[historyIndex]);

    ++historyIndex;
}

void ResetBoard()
{
    board.numUnits = 0;

    UnitType royalty[NUM_BOARD_SIDE_TILES] = {
        UNIT_ROOK,
        UNIT_KNIGHT,
        UNIT_BISHOP,
        UNIT_QUEEN,
        UNIT_KING,
        UNIT_BISHOP,
        UNIT_KNIGHT,
        UNIT_ROOK,
    };

    for (BoardPosCoord_t x = 0; x < NUM_BOARD_SIDE_TILES; ++x)
    {
        for (unsigned char yRep = 0; yRep < 4; ++yRep)
        {
            _Bool isFirstHalf = (yRep <= 1);
            _Bool isCenterHalf = ((1 <= yRep) && (yRep <= 2));

            BoardPosCoord_t baseY = isFirstHalf ? 0 : (NUM_BOARD_SIDE_TILES - 1);
            BoardPosCoord_t offsY = isCenterHalf ? (isFirstHalf ? 1 : -1) : 0;

            UnitType type = isCenterHalf ? UNIT_PAWN : royalty[x];
            UnitTeam team = isFirstHalf ? TEAM_WHITE : TEAM_BLACK;

            PushUnit(x, baseY + offsY, type, team);
        }
    }
}

RECT mouseTileLast = {-1,-1,-1,-1};
BoardPos lastTileHovered = { 0, 0 };

void DrawTile(BoardPos pos)
{
    Unit* unit = UnitAtBoardPos(pos);
    DrawEmptyTile(pos);
    DrawUnit(unit);
}

void PlayBoard()
{
    while (1)
    {
        MouseEvent e = PollMouseEvent(mouseTileLast);

        BoardPos tile = {
            .x = e.x / NUM_OUTPUT_TILE_SIDE_PIXELS,
            .y = e.y / NUM_OUTPUT_TILE_SIDE_PIXELS,
        };

        if (tile.x < NUM_BOARD_SIDE_TILES && tile.y < NUM_BOARD_SIDE_TILES)
        {
            DrawTile(tile);
        }

        mouseTileLast.left   = tile.x * NUM_OUTPUT_TILE_SIDE_PIXELS;
        mouseTileLast.top    = tile.y * NUM_OUTPUT_TILE_SIDE_PIXELS;
        mouseTileLast.right  = mouseTileLast.left + NUM_OUTPUT_TILE_SIDE_PIXELS;
        mouseTileLast.bottom = mouseTileLast.top  + NUM_OUTPUT_TILE_SIDE_PIXELS;
    }

}

void DecrementTurn()
{
    assert(turnIndex > 0);
    --turnIndex;
}

_Bool IncrementTurn()
{
    ++turnIndex;
    return 0;
}

void GameFlipbook()
{
    // todo
}

void RedrawBoard()
{
    BoardPos pos = {0};
    for (pos.y = 0; pos.y < NUM_BOARD_SIDE_TILES; ++pos.y)
    {
        for (pos.x = 0; pos.x < NUM_BOARD_SIDE_TILES; ++pos.x)
        {
            DrawEmptyTile(pos);
        }
    }

    for (size_t i = 0; i < board.numUnits; ++i)
    {
        DrawUnit(&(board.units[i]));
    }
}
