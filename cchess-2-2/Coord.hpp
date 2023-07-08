#pragma once
#include "Vec2.hpp"
#include <concepts>

// Boardspace position.
// Can be compared for equality (but not greater/less than).
struct Coord : public Vec2
{
    template<std::integral iT>
    constexpr Coord(iT x, iT y) :
        Vec2(x,y) {}

    template<std::floating_point fT>
    constexpr Coord(fT x, fT y) :
        Vec2(x,y) {}

    constexpr Coord(const Vec2& in) :
        Vec2(in) {}

    constexpr Coord(const Coord& in) :
        Vec2(in.x, in.y) {}

    constexpr Coord() :
        Vec2() {}

    constexpr bool operator==(const Coord& p2) const
    {
        bool result = (x == p2.x) && (y == p2.y);
        return result;
    }

    constexpr bool operator!=(const Coord& p2) const
    {
        bool result = (x != p2.x) || (y != p2.y);
        return result;
    }
};

constexpr bool ValidPos(const Coord testPos)
{
    using space::board::sideTileCount;

    bool result =
        ((testPos.x >= 0) && (testPos.x < sideTileCount)) &&
        ((testPos.y >= 0) && (testPos.y < sideTileCount));

    return result;
}
