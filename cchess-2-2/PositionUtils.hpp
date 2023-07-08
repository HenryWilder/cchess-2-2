#pragma once
#include "Coord.hpp"
#include "PixelPos.hpp"
#include "Constants.hpp"

// Returns the top-left pixel of the input board space.
constexpr PixelPos PixelSpace(const Coord tile)
{
    using space::screen::tileWidth;

    PixelPos result(
        tile.x * tileWidth,
        tile.y * tileWidth);

    return result;
}

// Returns the coordinate of the board tile containing the pixel.
constexpr Coord BoardSpace(const PixelPos pixel)
{
    using space::screen::tileWidth;

    Coord result(
        pixel.x / tileWidth,
        pixel.y / tileWidth);

    return result;
}
