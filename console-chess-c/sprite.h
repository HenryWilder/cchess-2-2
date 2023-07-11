#ifndef SPRITE_H
#define SPRITE_H
#include <Windows.h>
#include <sal.h>
#include "constants.h"

#define NUM_TEAM_SPRITE_BRUSHES 4

typedef enum UnitBrush {
    UNITBRUSH_OUTLINE,
    UNITBRUSH_FILL,
    UNITBRUSH_SHADE,
    UNITBRUSH_SHINE,
} UnitBrush;

// spriteBrushes[team][brushIndex]
extern HBRUSH spriteBrushes[2][NUM_TEAM_SPRITE_BRUSHES];

typedef struct SpritePart {

    unsigned char x[2], y[2];

} SpritePart;

typedef struct SpritePalette {

    HBRUSH outlineBrush;
    HBRUSH    fillBrush;
    HBRUSH   shadeBrush;
    HBRUSH   shineBrush;

} SpritePalette;

typedef struct Sprite {

    _Field_range_(0, NUM_TILE_PIXELS) size_t numOutlineParts;
    _Field_range_(0, NUM_TILE_PIXELS) size_t numFillParts;
    _Field_range_(0, NUM_TILE_PIXELS) size_t numShadeParts;
    _Field_range_(0, NUM_TILE_PIXELS) size_t numShineParts;

    _Field_size_(numOutlineParts) SpritePart* outlineParts;
    _Field_size_(numFillParts)    SpritePart*    fillParts;
    _Field_size_(numShadeParts)   SpritePart*   shadeParts;
    _Field_size_(numShineParts)   SpritePart*   shineParts;

} Sprite;

const Sprite* unitSprites[7];
const Sprite* arrowSprites[2];

#endif // !SPRITE_H