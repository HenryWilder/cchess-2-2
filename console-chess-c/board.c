#include "board.h"
#include "unit.h"
#include <assert.h>
#include <stdlib.h>

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

void ApplyMove(Move move)
{
    if (move.x != UNIT_NONE)
    {
        size_t targetUnitIndex = IndexOfUnitAtBoardPos(move.to);
        assert(targetUnitIndex != board.numUnits);
        RemoveUnitAtIndex(targetUnitIndex);
    }

    Unit* subjectUnit = UnitAtBoardPos(move.from);
    assert(subjectUnit != NULL);
    subjectUnit->position = move.to;
}

void ReverseMove(Move move)
{
    Unit* subjectUnit = UnitAtBoardPos(move.to);
    assert(subjectUnit != NULL);
    subjectUnit->position = move.from;

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

void PushMove(BoardPos from, BoardPos to, Unit* capturedUnit)
{
    if (history.numMoves == history.capMoves)
    {
        ReserveHistory((history.capMoves != 0)
            ? (history.capMoves * 2)
            : 32);
    }

    Move latestMove = {
        .from = from,
        .to = to,
        .x = capturedUnit ? capturedUnit->type : UNIT_NONE,
        .isCaptureMoved = capturedUnit && capturedUnit->isMoved,
    };

    history.moves[history.numMoves++] = latestMove;
    history.capRedoMoves = history.numMoves;
}

// Prefer PushMove() if Unit* is already known
void PushMoveIndexed(BoardPos from, BoardPos to, _In_range_(0, board.numUnits) size_t capturedUnitIndex)
{
    _Bool isUnitCaptured = capturedUnitIndex != board.numUnits;
    Unit* capturedUnit = isUnitCaptured ? &(board.units[capturedUnitIndex]) : NULL;
    PushMove(from, to, capturedUnit);
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

    ReverseMove(history.moves[historyIndex]);
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

            UnitType type = isCenterHalf ? royalty[x] : UNIT_PAWN;
            UnitTeam team = isFirstHalf ? TEAM_WHITE : TEAM_BLACK;

            PushUnit(x, baseY + offsY, type, team);
        }
    }
}

void PlayBoard()
{
    // todo
}

_Bool IncrementTurn()
{
    return 0;
}

void GameFlipbook()
{
    // todo
}

#if _DEBUG
#include <stdio.h>
void PrintBoardDebug()
{
#define NUM_ROWS NUM_BOARD_SIDE_TILES
#define NUM_COLS (NUM_BOARD_SIDE_TILES*2)
#define NUM_ROW_CHARS (NUM_COLS+1)
#define NUM_CHARS (NUM_ROW_CHARS*NUM_ROWS)

    char debugBoard[NUM_CHARS] = {0};
    for (size_t row = 0; row < NUM_ROWS; ++row)
    {
        size_t rowStartIndex = row * NUM_ROW_CHARS;
        for (size_t col = 0; col < NUM_COLS; ++col)
        {
            debugBoard[rowStartIndex + col] = ' ';
        }
        debugBoard[rowStartIndex + NUM_ROW_CHARS - 1] = '\n';
    }
    debugBoard[NUM_CHARS - 1] = '\0';

    for (size_t i = 0; i < board.numUnits; ++i)
    {
        const Unit unit = board.units[i];

        size_t index0 = (NUM_ROW_CHARS * (size_t)unit.position.y) + (2 * (size_t)unit.position.x);

        char teamChar = (unit.team == TEAM_WHITE) ? 'w' : 'b';
        char typeChar;
        switch (unit.type)
        {
        case UNIT_PAWN:   typeChar = 'P'; break;
        case UNIT_ROOK:   typeChar = 'R'; break;
        case UNIT_KNIGHT: typeChar = 'k'; break;
        case UNIT_BISHOP: typeChar = 'B'; break;
        case UNIT_QUEEN:  typeChar = 'Q'; break;
        case UNIT_KING:   typeChar = 'K'; break;

        default:
        case UNIT_NONE: typeChar = '?'; break;
        }

        debugBoard[index0] = teamChar;
        debugBoard[index0 + 1] = typeChar;
    }

    printf(debugBoard);

#undef NUM_ROWS
#undef NUM_COLS
#undef NUM_ROW_CHARS
#undef NUM_CHARS
}
#endif
