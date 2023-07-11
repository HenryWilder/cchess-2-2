#ifndef OUTPUT_H
#define OUTPUT_H
#include <Windows.h>
#include "unit.h"
#include "sprite.h"

extern HDC hdc;

#define NUM_TILEBRUSHES 7

typedef enum TileBrush {

    // Diagetic

    TILEBRUSH_TILE_WHITE = 0,
    TILEBRUSH_TILE_BLACK = 1,

    // Legal

    TILEBRUSH_SELECT,
    TILEBRUSH_AVAILABLE_MOVE,
    TILEBRUSH_AVAILABLE_CAPTURE,

    // Illegal

    TILEBRUSH_KING_CHECK,
    TILEBRUSH_SPACE_TAKEN,

} TileBrush;

extern HBRUSH tileBrushes[NUM_TILEBRUSHES];

void InitBrushes();

void DrawEmptyTile(BoardPos pos);
void DrawColoredTile(BoardPos pos, HBRUSH brush);

void DrawSprite(int xPixel, int yPixel, const Sprite* sprite, const SpritePalette* palette);
void DrawUnitSpriteBrush(int xPixel, int yPixel, size_t brushIndex, size_t numParts, const SpritePart parts[], UnitTeam team);
void DrawUnitSprite(int xPixel, int yPixel, UnitType type, UnitTeam team);
void DrawUnit(const Unit* unit);

#endif // OUTPUT_H