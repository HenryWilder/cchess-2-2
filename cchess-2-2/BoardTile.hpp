#pragma once
#include "Coord.hpp"
#include "PixelPos.hpp"
#include "PositionUtils.hpp"

// The start and end positions of a space.
// [start..end]
struct BoardTile
{
    constexpr BoardTile(Coord tile) :
        beginPx{ PixelSpace(tile) },
        endPx{}
    {
        using space::screen::tileWidth;

        endPx.x = beginPx.x + tileWidth;
        endPx.y = beginPx.y + tileWidth;
    }

    constexpr BoardTile(int tileX, int tileY) :
        BoardTile(Coord(tileX, tileY)) {}

    BoardTile() :
        beginPx{},
        endPx{} {}

    PixelPos beginPx, endPx;
};
