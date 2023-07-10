#ifndef SPRITE_H
#define SPRITE_H
#include <Windows.h>
#include <sal.h>
#include "constants.h"

#define NUM_TEAM_SPRITE_BRUSHES 4

// spriteBrushes[team][brushIndex]
extern const spriteBrushes[2][NUM_TEAM_SPRITE_BRUSHES];

typedef struct SpritePart {

    // Team independent
    _Field_range_(0, NUM_TEAM_SPRITE_BRUSHES - 1)
    size_t brushIndex;

    unsigned char x0, x1, y0, y1;

} SpritePart;

typedef struct Sprite {

    _Field_range_(0, NUM_TILE_PIXELS)
    size_t numParts;

    _Field_size_(numParts)
    SpritePart* parts;

} Sprite;

const Sprite* units[7];
const Sprite* arrows[2];

#endif // !SPRITE_H