#include "output.h"
#include "constants.h"
#include "sprite.h"

HDC hdc;

HBRUSH boardWhite;
HBRUSH boardBlack;
HBRUSH boardSelect;

void InitBrushes()
{
    boardWhite  = CreateSolidBrush(RGB(252, 219, 166));
    boardBlack  = CreateSolidBrush(RGB(236, 167,  95));
    boardSelect = CreateSolidBrush(RGB( 44, 200,  37));

    spriteBrushes[TEAM_WHITE][0] = CreateSolidBrush(RGB(240, 240, 230));
    spriteBrushes[TEAM_WHITE][1] = CreateSolidBrush(RGB(180, 150, 120));
    spriteBrushes[TEAM_WHITE][2] = CreateSolidBrush(RGB(100, 100,  90));
    spriteBrushes[TEAM_WHITE][3] = CreateSolidBrush(RGB(255, 255, 255));

    spriteBrushes[TEAM_BLACK][0] = CreateSolidBrush(RGB( 80,  80,  90));
    spriteBrushes[TEAM_BLACK][1] = CreateSolidBrush(RGB( 50,  55,  60));
    spriteBrushes[TEAM_BLACK][2] = CreateSolidBrush(RGB( 40,  30,  50));
    spriteBrushes[TEAM_BLACK][3] = CreateSolidBrush(RGB(100, 100, 110));
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

    _Bool isTileWhite = !((pos.x ^ pos.y) & 1);

    FillRect(hdc, &rect, isTileWhite ? boardWhite : boardBlack);
}

void DrawHighlightedTile(BoardPos pos)
{
    RECT rect = TileRect(pos);

    FillRect(hdc, &rect, boardSelect);
}

void DrawSprite(int xPixel, int yPixel, UnitType type, UnitTeam team)
{
    Sprite* sprite = unitSprites[type];
    for (size_t i = 0; i < sprite->numParts; ++i)
    {
        SpritePart part = sprite->parts[i];
        const RECT rect = {
            xPixel + part.x0 * GAME_SCALE,
            yPixel + part.y0 * GAME_SCALE,
            xPixel + (part.x1 + 1) * GAME_SCALE,
            yPixel + (part.y1 + 1) * GAME_SCALE,
        };
        FillRect(hdc, &rect, spriteBrushes[team][part.brushIndex]);
    }
}

void DrawUnit(const Unit* unit)
{
    DrawSprite(
        unit->position.x * NUM_OUTPUT_TILE_SIDE_PIXELS,
        unit->position.y * NUM_OUTPUT_TILE_SIDE_PIXELS,
        unit->type,
        unit->team);
}
