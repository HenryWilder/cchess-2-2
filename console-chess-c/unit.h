#ifndef UNIT_H
#define UNIT_H
#include "constants.h"
#include <sal.h>

// Keep parity with vcruntime.h
#ifdef _WIN64
typedef unsigned __int64 size_t;
#else
typedef unsigned int     size_t;
#endif

// Uses 3 bits
_Struct_size_bytes_(1)
typedef enum UnitType {
    UNIT_NONE   = 0,
    UNIT_PAWN   = 1,
    UNIT_ROOK   = 2,
    UNIT_KNIGHT = 3,
    UNIT_BISHOP = 4,
    UNIT_QUEEN  = 5,
    UNIT_KING   = 6,
} UnitType;

// Uses 1 bit
_Struct_size_bytes_(1)
typedef enum UnitTeam {
    TEAM_WHITE = 0,
    TEAM_BLACK = 1,
} UnitTeam;

typedef _Field_range_(0, INDEX_MAX_BOARD_SIDE_TILES) unsigned char BoardPosCoord_t;

typedef struct BoardPos {

    _Field_range_(0, INDEX_MAX_BOARD_SIDE_TILES)
    BoardPosCoord_t x;

    _Field_range_(0, INDEX_MAX_BOARD_SIDE_TILES)
    BoardPosCoord_t y;

} BoardPos;

typedef struct Unit {
    BoardPos position;
    UnitType type;
    UnitTeam team;
    _Bool isMoved;
} Unit;

Unit InitUnit(BoardPosCoord_t x, BoardPosCoord_t y, UnitType type, UnitTeam team);
void ReInitUnit(_Inout_ Unit* unit, BoardPosCoord_t x, BoardPosCoord_t y, UnitType type, UnitTeam team);

size_t MoveOptionsPawn(
    _Out_writes_to_(NUM_PAWN_MAX_MOVE_OPTIONS, return) BoardPos options[],
    _In_ const Unit* unit);

size_t MoveOptionsRook(
    _Out_writes_to_(NUM_ROOK_MAX_MOVE_OPTIONS, return) BoardPos options[],
    _In_ const Unit* unit);

size_t MoveOptionsKnight(
    _Out_writes_to_(NUM_KNIGHT_MAX_MOVE_OPTIONS, return) BoardPos options[],
    _In_ const Unit* unit);

size_t MoveOptionsBishop(
    _Out_writes_to_(NUM_BISHOP_MAX_MOVE_OPTIONS, return) BoardPos options[],
    _In_ const Unit* unit);

size_t MoveOptionsQueen(
    _Out_writes_to_(NUM_QUEEN_MAX_MOVE_OPTIONS, return) BoardPos options[],
    _In_ const Unit* unit);

size_t MoveOptionsKing(
    _Out_writes_to_(NUM_KING_MAX_MOVE_OPTIONS, return) BoardPos options[],
    _In_ const Unit* unit);

size_t MoveOptions(
    _Out_writes_to_(NUM_MAX_MOVE_OPTIONS, return) BoardPos options[],
    _In_ const Unit* unit);

#endif // !UNIT_H