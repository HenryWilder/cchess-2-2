#include "unit.h"
#include <sal.h>
#include <assert.h>

Unit InitUnit(BoardPosCoord_t x, BoardPosCoord_t y, UnitType type, UnitTeam team)
{
    Unit unit = {
        .position.x = x,
        .position.y = y,
        .type = type,
        .team = team,
        .isMoved = 0,
    };
    return unit;
}

void ReInitUnit(_Inout_ Unit* unit, BoardPosCoord_t x, BoardPosCoord_t y, UnitType type, UnitTeam team)
{
    unit->position.x = x;
    unit->position.y = y;
    unit->type = type;
    unit->team = team;
    unit->isMoved = 0;
}

_Use_decl_annotations_ size_t MoveOptionsPawn(BoardPos options[],const Unit* unit)
{
    assert(unit->type == UNIT_PAWN);

    size_t numOptions = 0;
    for (size_t i = 0; i < NUM_PAWN_MAX_MOVE_OPTIONS; ++i)
    {
        BoardPos testPos = { 0,0 };
        if (0) { break; }
        options[i] = testPos;
        ++numOptions;
    }

    assert(numOptions <= NUM_PAWN_MAX_MOVE_OPTIONS);

    return numOptions;
}

_Use_decl_annotations_ size_t MoveOptionsRook(BoardPos options[], const Unit* unit)
{
    assert(unit->type == UNIT_ROOK);

    size_t numOptions = 0;
    for (size_t i = 0; i < NUM_ROOK_MAX_MOVE_OPTIONS; ++i)
    {
        BoardPos testPos = { 0,0 };
        if (0) { break; }
        options[i] = testPos;
        ++numOptions;
    }

    assert(numOptions <= NUM_ROOK_MAX_MOVE_OPTIONS);

    return numOptions;
}

_Use_decl_annotations_ size_t MoveOptionsKnight(BoardPos options[], const Unit* unit)
{
    assert(unit->type == UNIT_KNIGHT);

    size_t numOptions = 0;
    for (size_t i = 0; i < NUM_KNIGHT_MAX_MOVE_OPTIONS; ++i)
    {
        BoardPos testPos = { 0,0 };
        if (0) { break; }
        options[i] = testPos;
        ++numOptions;
    }

    assert(numOptions <= NUM_KNIGHT_MAX_MOVE_OPTIONS);

    return numOptions;
}

_Use_decl_annotations_ size_t MoveOptionsBishop(BoardPos options[], const Unit* unit)
{
    assert(unit->type == UNIT_BISHOP);

    size_t numOptions = 0;
    for (size_t i = 0; i < NUM_BISHOP_MAX_MOVE_OPTIONS; ++i)
    {
        BoardPos testPos = { 0,0 };
        if (0) { break; }
        options[i] = testPos;
        ++numOptions;
    }

    assert(numOptions <= NUM_BISHOP_MAX_MOVE_OPTIONS);

    return numOptions;
}

_Use_decl_annotations_ size_t MoveOptionsQueen(BoardPos options[], const Unit* unit)
{
    assert(unit->type == UNIT_QUEEN);

    size_t numOptions = 0;
    for (size_t i = 0; i < NUM_QUEEN_MAX_MOVE_OPTIONS; ++i)
    {
        BoardPos testPos = { 0,0 };
        if (0) { break; }
        options[i] = testPos;
        ++numOptions;
    }

    assert(numOptions <= NUM_QUEEN_MAX_MOVE_OPTIONS);

    return numOptions;
}

_Use_decl_annotations_ size_t MoveOptionsKing(BoardPos options[], const Unit* unit)
{
    assert(unit->type == UNIT_KING);

    size_t numOptions = 0;
    for (size_t i = 0; i < NUM_KING_MAX_MOVE_OPTIONS; ++i)
    {
        BoardPos testPos = { 0,0 };
        if (0) { break; }
        options[i] = testPos;
        ++numOptions;
    }

    assert(numOptions <= NUM_KING_MAX_MOVE_OPTIONS);

    return numOptions;
}

_Use_decl_annotations_ size_t MoveOptions(BoardPos options[], const Unit* unit)
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
