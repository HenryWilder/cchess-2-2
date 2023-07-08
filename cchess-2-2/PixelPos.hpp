#pragma once
#include "Vec2.hpp"
#include <concepts>

// Screenspace position.
// Can be multiplied/divided and scaled.
struct PixelPos : public Vec2
{
    template<std::integral iT>
    constexpr PixelPos(iT x, iT y) :
        Vec2(x,y) {}

    template<std::floating_point fT>
    constexpr PixelPos(fT x, fT y) :
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
        PixelPos result(
            x * b.x,
            y * b.y);

        return result;
    }
    constexpr PixelPos operator/(const PixelPos b) const
    {
        PixelPos result(
            x / b.x,
            y / b.y);

        return result;
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

        PixelPos result(
            (int)((TBig)x * (TBig)scale),
            (int)((TBig)y * (TBig)scale)
        );

        return result;
    }

    template<std::integral iT>
    constexpr PixelPos operator/(const iT scale) const
    {
        using TBig = std::conditional_t<sizeof(iT) >= sizeof(int), iT, int>;

        PixelPos result(
            (int)((TBig)x / (TBig)scale),
            (int)((TBig)y / (TBig)scale)
        );

        return result;
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
        PixelPos result(
            (int)((fT)x * scale),
            (int)((fT)y * scale)
        );

        return result;
    }

    template<std::floating_point fT>
    constexpr PixelPos operator/(const fT scale) const
    {
        PixelPos result(
            (int)((fT)x / scale),
            (int)((fT)y / scale)
        );

        return result;
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

// Are these even needed?
// constexpr PixelPos Snap(PixelPos px, PixelPos gridsize)
// {
//     return {
//         Snap(px.x, gridsize.x),
//         Snap(px.y, gridsize.y)
//     };
// }
// 
// constexpr PixelPos Snap(PixelPos px, int gridsize)
// {
//     return {
//         Snap(px.x, gridsize),
//         Snap(px.y, gridsize)
//     };
// }
