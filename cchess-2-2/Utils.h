#pragma once
#include <Windows.h>
#include <chrono>
#include <thread>
#include <concepts>

template<typename T> concept numeric = std::is_integral_v<T> || std::is_floating_point_v<T>;

// Get a console handle
extern HWND window;

// Get a handle to device context
extern HDC hdc;

void SleepForMS(int ms = 1);

void SleepForMS(double ms = 1.0);

namespace space
{
    // Boardspace
    namespace game
    {
        const constexpr int sideTileCount = 8; // The number of spaces in a row
        const constexpr int boardArea = sideTileCount * sideTileCount; // The total spaces on the board
    }
    // Pixelspace
    namespace screen
    {
        const constexpr int tileWidth = 16; // The number of pixels on the side of a space
        const constexpr int tileArea = tileWidth * tileWidth; // The total pixels in a space
        const constexpr int boardWidth = tileWidth * game::sideTileCount; // The number of pixels on the side of the board
        const constexpr int totalArea = boardWidth * boardWidth; // The total pixels in the board
        const constexpr int gameScale = 2;

        namespace output
        {
            const constexpr int otileWidth = screen::tileWidth * screen::gameScale; // The number of pixels on the side of a space, scaled by render output
            const constexpr int oboardWidth = screen::boardWidth * screen::gameScale; // The number of pixels on the side of the entire board, scaled by render output
            const constexpr int oboardLIndex = boardWidth - tileWidth; // The number of pixels on the side of the entire board, scaled by render output, minus one tile to act as an index
        }
    }
}

int Snap(int value, int gridsize);

bool Even(int a);

struct Coord;
struct PixelPos;

// A generic 2D integer.
// Can be added/subtracted.
struct Vec2
{
    template<std::floating_point fT>
    Vec2(fT x, fT y) :
        x{ (int)(x + ((fT)0.5)) },
        y{ (int)(y + ((fT)0.5)) }
    {}

    template<std::integral iT>
    Vec2(iT x, iT y) :
        x{ (int)x },
        y{ (int)y }
    {}

    Vec2(int x, int y) :
        x{ x },
        y{ y }
    {}

    Vec2(const Vec2& in) :
        x{ in.x },
        y{ in.y }
    {}

    Vec2() :
        x{ 0 },
        y{ 0 }
    {}

    int x, y;

    Vec2& operator=(const Vec2 b)
    {
        x = b.x;
        y = b.y;
        return *this;
    }
    Vec2 operator+(const Vec2 b) const
    {
        return { x + b.x, y + b.y};
    }
    Vec2 operator-(const Vec2 b) const
    {
        return { x - b.x, y - b.y};
    }
    Vec2& operator+=(const Vec2 b)
    {
        return *this = *this + b;
    }
    Vec2& operator-=(const Vec2 b)
    {
        return *this = *this - b;
    }
};

bool ValidPos(const Coord testPos);

// Screenspace position.
// Can be multiplied/divided and scaled.
struct PixelPos : public Vec2
{
    template<numeric nT>
    PixelPos(nT x, nT y) :
        Vec2(x,y)
    {}

    PixelPos(const Vec2& in) :
        Vec2(in)
    {}

    PixelPos(const PixelPos& in) :
        Vec2(in.x, in.y)
    {}

    PixelPos() :
        Vec2()
    {}

    // Conversion to boardspace.
    operator Coord() const;

    PixelPos& operator=(const PixelPos b)
    {
        x = b.x;
        y = b.y;
        return *this;
    }

    PixelPos operator*(const PixelPos b) const
    {
        return {
            x * b.x,
            y * b.y
        };
    }
    PixelPos operator/(const PixelPos b) const
    {
        return {
            x / b.x,
            y / b.y
        };
    }
    PixelPos& operator*=(const PixelPos b)
    {
        return *this = *this * b;
    }
    PixelPos& operator/=(const PixelPos b)
    {
        return *this = *this / b;
    }

    template<std::integral iT>
    PixelPos operator*(const iT scale) const
    {
        using TBig = std::conditional_t<sizeof(iT) >= sizeof(int), iT, int>;
        return {
            (int)((TBig)x * (TBig)scale),
            (int)((TBig)y * (TBig)scale)
        };
    }
    template<std::integral iT>
    PixelPos operator/(const iT scale) const
    {
        using TBig = std::conditional_t<sizeof(iT) >= sizeof(int), iT, int>;
        return {
            (int)((TBig)x / (TBig)scale),
            (int)((TBig)y / (TBig)scale)
        };
    }

    template<std::integral iT>
    PixelPos& operator*=(const iT scale)
    {
        return *this = *this * scale;
    }
    template<std::integral iT>
    PixelPos& operator/=(const iT scale)
    {
        return *this = *this / scale;
    }

    template<std::floating_point fT>
    PixelPos  operator* (const fT scale) const
    {
        return {
            (int)((fT)x * scale),
            (int)((fT)y * scale)
        };
    }
    template<std::floating_point fT>
    PixelPos  operator/ (const fT scale) const
    {
        return {
            (int)((fT)x / scale),
            (int)((fT)y / scale)
        };
    }
    template<std::floating_point fT>
    PixelPos& operator*=(const fT scale)
    {
        return *this = *this * scale;
    }
    template<std::floating_point fT>
    PixelPos& operator/=(const fT scale)
    {
        return *this = *this / scale;
    }
};

PixelPos Snap(PixelPos pix, PixelPos gridsize);
PixelPos Snap(PixelPos pix, int gridsize);

// Boardspace position.
// Can be compared for equality (but not greater/less than).
struct Coord : public Vec2
{
    template<numeric nT>
    Coord(nT x, nT y) :
        Vec2(x,y)
    {}

    Coord(const Vec2& in) :
        Vec2(in)
    {}

    Coord(const Coord& in) :
        Vec2(in.x, in.y)
    {}

    Coord() :
        Vec2()
    {}

    // Conversion to screenspace.
    operator PixelPos() const;

    bool operator==(const Coord& p2) const
    {
        return
            (x == p2.x) &&
            (y == p2.y);
    }
    bool operator!=(const Coord& p2) const
    {
        return
            (x != p2.x) ||
            (y != p2.y);
    }
};

// Returns the top-left pixel of the input board space.
PixelPos PixelSpace(const Coord tile);

// Returns the coordinate of the board tile containing the pixel.
Coord BoardSpace(const PixelPos pixel);

// The start and end positions of a space.
struct BoardTile
{
    BoardTile();
    BoardTile(Coord tile);

    PixelPos start, end;
};

// I think the idea of this was so that the pixels could be iterated over using a ranged for-loop.
// This can be performed better by simply using begin() and end() methods.
#if false
// An array of all pixels in a board tile
struct BoardTile2
{
BoardTile2();
BoardTile2(Coord tile);

std::vector<PixelPos> pixels[space::screen::tileArea];
};
#endif
