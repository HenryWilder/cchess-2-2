#pragma once
#include <concepts>

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