#include "Utils.h"

// Get a console handle
HWND window = GetConsoleWindow();

// Get a handle to device context
HDC hdc = GetDC(window);

void SleepForMS(int ms) {
    auto time = std::chrono::milliseconds(ms);
    std::this_thread::sleep_for(time);
}
void SleepForMS(double ms) {
    auto time = std::chrono::microseconds((int)(ms * 1000.0));
    std::this_thread::sleep_for(time);
}

bool ValidPos(const Coord testPos)
{
    if (((testPos.x >= 0) && (testPos.x < space::game::sideTileCount)) &&
        ((testPos.y >= 0) && (testPos.y < space::game::sideTileCount))) return true;
    else return false;
}

Vec2 Snap(Vec2 vec, PixelPos gridsize)
{
    return {
        Snap(vec.x, gridsize.x),
        Snap(vec.y, gridsize.y)
    };
}

Vec2 Snap(Vec2 vec, int gridsize)
{
    return {
        Snap(vec.x, gridsize),
        Snap(vec.y, gridsize)
    };
}

PixelPos Snap(PixelPos px, PixelPos gridsize)
{
    return {
        Snap(px.x, gridsize.x),
        Snap(px.y, gridsize.y)
    };
}

PixelPos Snap(PixelPos px, int gridsize)
{
    return {
        Snap(px.x, gridsize),
        Snap(px.y, gridsize)
    };
}

PixelPos PixelSpace(const Coord tile)
{
    return {
        tile.x * space::screen::tileWidth,
        tile.y * space::screen::tileWidth
    };
}

Coord BoardSpace(const PixelPos pixel)
{
    return {
        pixel.x / space::screen::tileWidth,
        pixel.y / space::screen::tileWidth
    };
}

BoardTile::BoardTile(Coord tile)
{
    // Top-left pixel of the space
    beginPx = PixelSpace(tile);
    // Bottom-right pixel of the space
    endPx = beginPx + PixelPos(space::screen::tileWidth + 1, space::screen::tileWidth + 1);
}

BoardTile::BoardTile(int tileX, int tileY)
{
    BoardTile(Coord(tileX, tileY));
}
