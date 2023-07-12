#include "output.h"
#include "constants.h"
#include <assert.h>

// Sprite > Brush > Part

HDC hdc;

unsigned char mode = 2;

HBRUSH cc2TileBrushes[NUM_TILEBRUSHES];
HBRUSH cc3TileBrushes[NUM_TILEBRUSHES];
HBRUSH* cccTileBrushes = cc2TileBrushes; // Brushes used in this

HBRUSH cc2UnitBrushes[2][NUM_TEAM_SPRITE_BRUSHES_CC2];
HBRUSH cc3UnitBrushes[2][NUM_TEAM_SPRITE_BRUSHES_CC3];

size_t numUnitBrushes = NUM_TEAM_SPRITE_BRUSHES_CC2;
HBRUSH* cccUnitBrushes[2] = cc2UnitBrushes; // Brushes used in this | Array of array references

void InitBrushes()
{
    // CC2
    {
        const COLORREF cc2TileBrushColors[] = {
            [TILEBRUSH_TILE_WHITE]        = RGB(252, 219, 166),
            [TILEBRUSH_TILE_BLACK]        = RGB(236, 167,  95),

            [TILEBRUSH_SELECT]            = RGB( 44, 200,  37),
            [TILEBRUSH_AVAILABLE_MOVE]    = RGB(155, 235, 135),
            [TILEBRUSH_AVAILABLE_CAPTURE] = RGB(255,  80,  80),

            [TILEBRUSH_KING_CHECK]        = RGB(255, 200,  80),
            [TILEBRUSH_SPACE_TAKEN]       = RGB(127, 127, 127),
        };

        const COLORREF cc2UnitBrushColors[2][4] = {
            [TEAM_WHITE] = {
                [UNITBRUSH_FILL]    = RGB(240, 240, 230),
                [UNITBRUSH_SHADE]   = RGB(180, 150, 120),
                [UNITBRUSH_OUTLINE] = RGB(100, 100,  90),
                [UNITBRUSH_SHINE]   = RGB(255, 255, 255),
            },

            [TEAM_BLACK] = {
                [UNITBRUSH_FILL]    = RGB( 80,  80,  90),
                [UNITBRUSH_SHADE]   = RGB( 50,  55,  60),
                [UNITBRUSH_OUTLINE] = RGB( 40,  30,  50),
                [UNITBRUSH_SHINE]   = RGB(100, 100, 110),
            },
        };

        for (size_t i = 0; i < _countof(cc2TileBrushColors); ++i)
        {
            cc2TileBrushes[i] = CreateSolidBrush(cc2TileBrushColors[i]);
        }

        for (size_t team = 0; team < _countof(cc2UnitBrushColors); ++team)
        {
            const COLORREF colorArray[] = cc2UnitBrushColors[team];
            for (size_t i = 0; i < _countof(cc2UnitBrushColors[0]); ++i)
            {
                cc2TileBrushes[i] = CreateSolidBrush(colorArray[i]);
            }
        }
    }
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

RECT PartRect(int xPixel, int yPixel, SpriteRectPart part)
{
    RECT rect = {
        xPixel + (part.x[0] + 0) * GAME_SCALE,
        yPixel + (part.y[0] + 0) * GAME_SCALE,
        xPixel + (part.x[1] + 1) * GAME_SCALE,
        yPixel + (part.y[1] + 1) * GAME_SCALE,
    };
    return rect;
}

void DrawSpriteBrush(int xPixel, int yPixel, size_t numParts, const SpriteRectPart parts[], HBRUSH brush)
{
    for (size_t i = 0; i < numParts; ++i)
    {
        SpriteRectPart part = parts[i];
        const RECT rect = PartRect(xPixel, yPixel, part);
        FillRect(hdc, &rect, brush);
    }
}

void DrawSprite(int xPixel, int yPixel, const Sprite* sprite, const HBRUSH palette[], size_t numBrushes)
{
    DrawSpriteBrush(xPixel, yPixel, sprite->numOutlineParts, sprite->outlineParts, palette->outlineBrush);
    DrawSpriteBrush(xPixel, yPixel, sprite->numFillParts,    sprite->fillParts,    palette->fillBrush);
    DrawSpriteBrush(xPixel, yPixel, sprite->numShadeParts,   sprite->shadeParts,   palette->shadeBrush);
    DrawSpriteBrush(xPixel, yPixel, sprite->numShineParts,   sprite->shineParts,   palette->shineBrush);
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
