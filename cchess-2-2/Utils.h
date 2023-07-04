#pragma once
#include <Windows.h>
#include <chrono>
#include <thread>
#include <concepts>

template<typename T>
concept numeric = std::is_integral_v<T> || std::is_floating_point_v<T>;

template<typename Func, typename T>
concept Evalable = requires(Func fn, T px)
{
    { fn(px) };
};

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

template<std::integral iT>
bool IsOdd(iT a)
{
    return !!(a & (iT)1);
}

template<std::integral iT>
bool IsEven(iT a)
{
    return !(a & (iT)1);
}

template<std::integral iT1, std::integral iT2>
iT1 Snap(iT1 value, iT2 gridsize) {
    using TBig = std::conditional_t<sizeof(iT1) >= sizeof(iT2), iT1, iT2>;
    value = (iT1)((TBig)value / (TBig)gridsize);
    value = (iT1)((TBig)value * (TBig)gridsize);
    return value;
}

struct Coord;
struct PixelPos;

// A generic 2D integer.
// Can be added/subtracted.
struct Vec2
{
    template<std::floating_point fT>
    constexpr Vec2(fT x, fT y) :
        x{ (int)(x + ((fT)0.5)) },
        y{ (int)(y + ((fT)0.5)) } {}

    template<std::integral iT>
    constexpr Vec2(iT x, iT y) :
        x{ (int)x },
        y{ (int)y } {}

    constexpr Vec2(int x, int y) :
        x{ x },
        y{ y } {}

    constexpr Vec2(const Vec2& in) :
        x{ in.x },
        y{ in.y } {}

    constexpr Vec2() :
        x{ 0 },
        y{ 0 } {}

    int x, y;

    Vec2& operator=(const Vec2 b)
    {
        x = b.x;
        y = b.y;
        return *this;
    }
    constexpr Vec2 operator+(const Vec2 b) const
    {
        return { x + b.x, y + b.y};
    }
    constexpr Vec2 operator-(const Vec2 b) const
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

// Screenspace position.
// Can be multiplied/divided and scaled.
struct PixelPos : public Vec2
{
    template<numeric nT>
    constexpr PixelPos(nT x, nT y) :
        Vec2(x,y) {}

    constexpr PixelPos(const Vec2& in) :
        Vec2(in) {}

    constexpr PixelPos(const PixelPos& in) :
        Vec2(in.x, in.y) {}

    constexpr PixelPos() :
        Vec2() {}

    PixelPos& operator=(const PixelPos b)
    {
        x = b.x;
        y = b.y;
        return *this;
    }

    constexpr PixelPos operator*(const PixelPos b) const
    {
        return {
            x * b.x,
            y * b.y
        };
    }
    constexpr PixelPos operator/(const PixelPos b) const
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
    constexpr PixelPos operator*(const iT scale) const
    {
        using TBig = std::conditional_t<sizeof(iT) >= sizeof(int), iT, int>;
        return {
            (int)((TBig)x * (TBig)scale),
            (int)((TBig)y * (TBig)scale)
        };
    }

    template<std::integral iT>
    constexpr PixelPos operator/(const iT scale) const
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
    constexpr PixelPos operator*(const fT scale) const
    {
        return {
            (int)((fT)x * scale),
            (int)((fT)y * scale)
        };
    }

    template<std::floating_point fT>
    constexpr PixelPos operator/(const fT scale) const
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

constexpr PixelPos Snap(PixelPos px, PixelPos gridsize)
{
    return {
        Snap(px.x, gridsize.x),
        Snap(px.y, gridsize.y)
    };
}

constexpr PixelPos Snap(PixelPos px, int gridsize)
{
    return {
        Snap(px.x, gridsize),
        Snap(px.y, gridsize)
    };
}

// Boardspace position.
// Can be compared for equality (but not greater/less than).
struct Coord : public Vec2
{
    template<numeric nT>
    constexpr Coord(nT x, nT y) :
        Vec2(x,y) {}

    constexpr Coord(const Vec2& in) :
        Vec2(in) {}

    constexpr Coord(const Coord& in) :
        Vec2(in.x, in.y) {}

    constexpr Coord() :
        Vec2() {}

    constexpr bool operator==(const Coord& p2) const
    {
        return (x == p2.x) && (y == p2.y);
    }

    constexpr bool operator!=(const Coord& p2) const
    {
        return (x != p2.x) || (y != p2.y);
    }
};

constexpr bool ValidPos(const Coord testPos)
{
    if (((testPos.x >= 0) && (testPos.x < space::game::sideTileCount)) &&
        ((testPos.y >= 0) && (testPos.y < space::game::sideTileCount))) return true;
    else return false;
}

// Returns the top-left pixel of the input board space.
constexpr PixelPos PixelSpace(const Coord tile)
{
    return {
        tile.x * space::screen::tileWidth,
        tile.y * space::screen::tileWidth
    };
}

// Returns the coordinate of the board tile containing the pixel.
constexpr Coord BoardSpace(const PixelPos pixel)
{
    return {
        pixel.x / space::screen::tileWidth,
        pixel.y / space::screen::tileWidth
    };
}

// The start and end positions of a space.
// [start..end]
struct BoardTile
{
    inline BoardTile(Coord tile)
    {
        constexpr PixelPos tileSize = PixelPos(space::screen::tileWidth, space::screen::tileWidth);

        beginPx = PixelSpace(tile);
        endPx = beginPx + tileSize;
    }

    inline BoardTile(int tileX, int tileY)
    {
        BoardTile(Coord(tileX, tileY));
    }

    BoardTile() :
        beginPx{},
          endPx{} {}

    PixelPos beginPx, endPx;
};
