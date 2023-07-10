#include "output.h"
#include "constants.h"

HDC hdc;

HBRUSH boardWhite;
HBRUSH boardBlack;
HBRUSH boardSelect;

void InitBrushes()
{
    boardWhite  = CreateSolidBrush(RGB(252, 219, 166));
    boardBlack  = CreateSolidBrush(RGB(236, 167,  95));
    boardSelect = CreateSolidBrush(RGB( 44, 200,  37));
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

void DrawUnit(const Unit* unit)
{

}

void DrawSprite(int xPixel, int yPixel, UnitType type, UnitTeam team)
{

}
