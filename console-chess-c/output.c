#include "output.h"
#include "constants.h"

#define SPRITES_LEVEL_OF_DETAIL 1

// Sprite > Brush > Part

HDC hdc;

HBRUSH tileBrushes[NUM_TILEBRUSHES];

void InitBrushes()
{
    tileBrushes[TILEBRUSH_TILE_WHITE           ] = CreateSolidBrush(RGB(252, 219, 166));
    tileBrushes[TILEBRUSH_TILE_BLACK           ] = CreateSolidBrush(RGB(236, 167,  95));

    tileBrushes[TILEBRUSH_SELECT               ] = CreateSolidBrush(RGB( 44, 200,  37));
    tileBrushes[TILEBRUSH_AVAILABLE_MOVE       ] = CreateSolidBrush(RGB(155, 235, 135));
    tileBrushes[TILEBRUSH_AVAILABLE_CAPTURE    ] = CreateSolidBrush(RGB(255,  80,  80));

    tileBrushes[TILEBRUSH_KING_CHECK           ] = CreateSolidBrush(RGB(255, 200,  80));
    tileBrushes[TILEBRUSH_SPACE_TAKEN          ] = CreateSolidBrush(RGB(127, 127, 127));

    spriteBrushes[TEAM_WHITE][UNITBRUSH_FILL   ] = CreateSolidBrush(RGB(240, 240, 230));
    spriteBrushes[TEAM_WHITE][UNITBRUSH_SHADE  ] = CreateSolidBrush(RGB(180, 150, 120));
    spriteBrushes[TEAM_WHITE][UNITBRUSH_OUTLINE] = CreateSolidBrush(RGB(100, 100,  90));
    spriteBrushes[TEAM_WHITE][UNITBRUSH_SHINE  ] = CreateSolidBrush(RGB(255, 255, 255));

    spriteBrushes[TEAM_BLACK][UNITBRUSH_FILL   ] = CreateSolidBrush(RGB( 80,  80,  90));
    spriteBrushes[TEAM_BLACK][UNITBRUSH_SHADE  ] = CreateSolidBrush(RGB( 50,  55,  60));
    spriteBrushes[TEAM_BLACK][UNITBRUSH_OUTLINE] = CreateSolidBrush(RGB( 40,  30,  50));
    spriteBrushes[TEAM_BLACK][UNITBRUSH_SHINE  ] = CreateSolidBrush(RGB(100, 100, 110));
}

RECT TileRect(BoardPos pos)
{
    LONG left   = pos.x * NUM_OUTPUT_TILE_SIDE_PIXELS;
    LONG top    = pos.y * NUM_OUTPUT_TILE_SIDE_PIXELS;
    LONG right  = left  + NUM_OUTPUT_TILE_SIDE_PIXELS;
    LONG bottom = top   + NUM_OUTPUT_TILE_SIDE_PIXELS;

    RECT rect = { left, top, right, bottom };

    return rect;
}

void DrawEmptyTile(BoardPos pos)
{
    RECT rect = TileRect(pos);

    _Bool isTileBlack = (pos.x ^ pos.y) & 1;

    static_assert(
        ((_Bool)TILEBRUSH_TILE_WHITE == 0) &&
        ((_Bool)TILEBRUSH_TILE_BLACK == 1),
        "Tilebrush implementation may have changed in a way that directly affects an assumption reliant on implementation.");

    FillRect(hdc, &rect, tileBrushes[isTileBlack]);
}

void DrawColoredTile(BoardPos pos, HBRUSH brush)
{
    RECT rect = TileRect(pos);

    FillRect(hdc, &rect, brush);
}

RECT PartRect(int xPixel, int yPixel, SpritePart part)
{
    RECT rect = {
        xPixel + (part.x[0] + 0) * GAME_SCALE,
        yPixel + (part.y[0] + 0) * GAME_SCALE,
        xPixel + (part.x[1] + 1) * GAME_SCALE,
        yPixel + (part.y[1] + 1) * GAME_SCALE,
    };
    return rect;
}

void DrawSpriteBrush(int xPixel, int yPixel, size_t numParts, const SpritePart parts[], HBRUSH brush)
{
    for (size_t i = 0; i < numParts; ++i)
    {
        SpritePart part = parts[i];
        const RECT rect = PartRect(xPixel, yPixel, part);
        FillRect(hdc, &rect, brush);
    }
}

void DrawSprite(int xPixel, int yPixel, const Sprite* sprite, const SpritePalette* palette)
{
    DrawSpriteBrush(xPixel, yPixel, sprite->numOutlineParts, sprite->outlineParts, palette->outlineBrush);
    DrawSpriteBrush(xPixel, yPixel, sprite->numFillParts,    sprite->fillParts,    palette->fillBrush);
#if SPRITES_LEVEL_OF_DETAIL >= 1
    DrawSpriteBrush(xPixel, yPixel, sprite->numShadeParts,   sprite->shadeParts,   palette->shadeBrush);
    DrawSpriteBrush(xPixel, yPixel, sprite->numShineParts,   sprite->shineParts,   palette->shineBrush);
#endif
}

void DrawUnitSpriteBrush(int xPixel, int yPixel, size_t brushIndex, size_t numParts, const SpritePart parts[], UnitTeam team)
{
    HBRUSH brush = spriteBrushes[team][brushIndex];
    for (size_t i = 0; i < numParts; ++i)
    {
        SpritePart part = parts[i];
        const RECT rect = PartRect(xPixel, yPixel, part);
        FillRect(hdc, &rect, brush);
    }
}

// Also used for ghosts
void DrawUnitSprite(int xPixel, int yPixel, UnitType type, UnitTeam team)
{
    const Sprite* sprite = unitSprites[type];
    DrawUnitSpriteBrush(xPixel, yPixel, UNITBRUSH_OUTLINE, sprite->numOutlineParts, sprite->outlineParts, team);
    DrawUnitSpriteBrush(xPixel, yPixel, UNITBRUSH_FILL,    sprite->numFillParts,    sprite->fillParts,    team);
#if SPRITES_LEVEL_OF_DETAIL >= 1
    DrawUnitSpriteBrush(xPixel, yPixel, UNITBRUSH_SHADE,   sprite->numShadeParts,   sprite->shadeParts,   team);
    DrawUnitSpriteBrush(xPixel, yPixel, UNITBRUSH_SHINE,   sprite->numShineParts,   sprite->shineParts,   team);
#endif
}

void DrawUnit(const Unit* unit)
{
    if (unit != NULL)
    {
        DrawUnitSprite(
            unit->position.x * NUM_OUTPUT_TILE_SIDE_PIXELS,
            unit->position.y * NUM_OUTPUT_TILE_SIDE_PIXELS,
            unit->type,
            unit->team);
    }
}
