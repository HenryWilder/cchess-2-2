#ifndef UNIT_H
#define UNIT_H
#include "constants.h"
#include <sal.h>

// Uses 3 bits
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
typedef enum UnitTeam {
    TEAM_WHITE = 0,
    TEAM_BLACK = 1,
} UnitTeam;

typedef struct BoardPos {
    unsigned char x, y;
} BoardPos;

typedef struct Unit {
    BoardPos position;
    UnitType type;
    UnitTeam team;
    _Bool isMoved;
} Unit;

Unit InitUnit(int x, int y, UnitType type, UnitTeam team);
void ReInitUnit(_Inout_ Unit* unit, int x, int y, UnitType type, UnitTeam team);

unsigned int MoveOptionsPawn(
    _Out_writes_to_(NUM_PAWN_MAX_MOVE_OPTIONS, return) BoardPos options[],
    _In_ const Unit* unit);

unsigned int MoveOptionsRook(
    _Out_writes_to_(NUM_ROOK_MAX_MOVE_OPTIONS, return) BoardPos options[],
    _In_ const Unit* unit);

unsigned int MoveOptionsKnight(
    _Out_writes_to_(NUM_KNIGHT_MAX_MOVE_OPTIONS, return) BoardPos options[],
    _In_ const Unit* unit);

unsigned int MoveOptionsBishop(
    _Out_writes_to_(NUM_BISHOP_MAX_MOVE_OPTIONS, return) BoardPos options[],
    _In_ const Unit* unit);

unsigned int MoveOptionsQueen(
    _Out_writes_to_(NUM_QUEEN_MAX_MOVE_OPTIONS, return) BoardPos options[],
    _In_ const Unit* unit);

unsigned int MoveOptionsKing(
    _Out_writes_to_(NUM_KING_MAX_MOVE_OPTIONS, return) BoardPos options[],
    _In_ const Unit* unit);

unsigned int MoveOptions(
    _Out_writes_to_(NUM_MAX_MOVE_OPTIONS, return) BoardPos options[],
    _In_ const Unit* unit);

#endif // !UNIT_H