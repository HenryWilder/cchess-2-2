#include "unit.h"
#include <sal.h>
#include <assert.h>

void InitUnit(_Inout_ UnitPtr unit, int x, int y, UnitType type, UnitTeam team)
{
    unit->position.x = x;
    unit->position.y = y;
    unit->type = type;
    unit->team = team;
    unit->isMoved = 0;
}

unsigned int MoveOptionsPawn(
    _Pre_count_(NUM_PAWN_MAX_MOVE_OPTIONS) _Post_count_(return) BoardPos options[],
    _In_ const Unit* unit)
{
    assert(unit->type == UNIT_PAWN);

    unsigned int numOptions = 0;
    for (unsigned int i = 0; i < NUM_PAWN_MAX_MOVE_OPTIONS; ++i)
    {
        BoardPos testPos = { 0,0 };
        if (0) { break; }
        options[i] = testPos;
        ++numOptions;
    }

    assert(numOptions <= NUM_PAWN_MAX_MOVE_OPTIONS);

    return numOptions;
}

unsigned int MoveOptionsRook(
    _Pre_count_(NUM_ROOK_MAX_MOVE_OPTIONS) _Post_count_(return) BoardPos options[],
    _In_ const Unit* unit)
{
    assert(unit->type == UNIT_ROOK);

    unsigned int numOptions = 0;
    for (unsigned int i = 0; i < NUM_ROOK_MAX_MOVE_OPTIONS; ++i)
    {
        BoardPos testPos = { 0,0 };
        if (0) { break; }
        options[i] = testPos;
        ++numOptions;
    }

    assert(numOptions <= NUM_ROOK_MAX_MOVE_OPTIONS);

    return numOptions;
}

unsigned int MoveOptionsKnight(
    _Pre_count_(NUM_KNIGHT_MAX_MOVE_OPTIONS) _Post_count_(return) BoardPos options[],
    _In_ const Unit* unit)
{
    assert(unit->type == UNIT_KNIGHT);

    unsigned int numOptions = 0;
    for (unsigned int i = 0; i < NUM_KNIGHT_MAX_MOVE_OPTIONS; ++i)
    {
        BoardPos testPos = { 0,0 };
        if (0) { break; }
        options[i] = testPos;
        ++numOptions;
    }

    assert(numOptions <= NUM_KNIGHT_MAX_MOVE_OPTIONS);

    return numOptions;
}

unsigned int MoveOptionsBishop(
    _Pre_count_(NUM_BISHOP_MAX_MOVE_OPTIONS) _Post_count_(return) BoardPos options[],
    _In_ const Unit* unit)
{
    assert(unit->type == UNIT_BISHOP);

    unsigned int numOptions = 0;
    for (unsigned int i = 0; i < NUM_BISHOP_MAX_MOVE_OPTIONS; ++i)
    {
        BoardPos testPos = { 0,0 };
        if (0) { break; }
        options[i] = testPos;
        ++numOptions;
    }

    assert(numOptions <= NUM_BISHOP_MAX_MOVE_OPTIONS);

    return numOptions;
}

unsigned int MoveOptionsQueen(
    _Pre_count_(NUM_QUEEN_MAX_MOVE_OPTIONS) _Post_count_(return) BoardPos options[],
    _In_ const Unit* unit)
{
    assert(unit->type == UNIT_QUEEN);

    unsigned int numOptions = 0;
    for (unsigned int i = 0; i < NUM_QUEEN_MAX_MOVE_OPTIONS; ++i)
    {
        BoardPos testPos = { 0,0 };
        if (0) { break; }
        options[i] = testPos;
        ++numOptions;
    }

    assert(numOptions <= NUM_QUEEN_MAX_MOVE_OPTIONS);

    return numOptions;
}

unsigned int MoveOptionsKing(
    _Pre_count_(NUM_KING_MAX_MOVE_OPTIONS) _Post_count_(return) BoardPos options[],
    _In_ const Unit* unit)
{
    assert(unit->type == UNIT_KING);

    unsigned int numOptions = 0;
    for (unsigned int i = 0; i < NUM_KING_MAX_MOVE_OPTIONS; ++i)
    {
        BoardPos testPos = { 0,0 };
        if (0) { break; }
        options[i] = testPos;
        ++numOptions;
    }

    assert(numOptions <= NUM_KING_MAX_MOVE_OPTIONS);

    return numOptions;
}

unsigned int MoveOptions(
    _Pre_count_(NUM_MAX_MOVE_OPTIONS) _Post_count_(return) BoardPos options[],
    _In_ UnitCPtr unit)
{
    switch (unit->type)
    {
    case UNIT_PAWN:   return MoveOptionsPawn  (options, unit);
    case UNIT_ROOK:   return MoveOptionsRook  (options, unit);
    case UNIT_KNIGHT: return MoveOptionsKnight(options, unit);
    case UNIT_BISHOP: return MoveOptionsBishop(options, unit);
    case UNIT_QUEEN:  return MoveOptionsQueen (options, unit);
    case UNIT_KING:   return MoveOptionsKing  (options, unit);

    default:
    case UNIT_NONE:   return 0;
    }
}
