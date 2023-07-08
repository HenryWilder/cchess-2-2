#pragma once
#include "Color.hpp"
#include <Windows.h>
#include "Constants.hpp"

namespace sprite
{
    // Should stay synced with `colorPalette`.
    enum class Pltt : unsigned int
    {
        // Board

        Board_Black,
        Board_White,

        // Black

        UnitB_Fill,
        UnitB_Shade,
        UnitB_Edge,
        UnitB_Shine,

        // White

        UnitW_Fill,
        UnitW_Shade,
        UnitW_Edge,
        UnitW_Shine,

        // Select

        // This is the piece we want to move
        Select_Unit,

        // This space is available to move to
        Select_Available,

        // There is an enemy unit here we can take
        Select_TakePiece,

        // NoSelect

        // The space would put the king into check
        NoSelect_KingDanger,

        // There is a teammate there blocking us from movement
        NoSelect_Teammate,
    };
    extern const Color colorPalette[15];

    COLORREF PaletteColor(Pltt col);

    struct Sprite
    {
        // ' ' = empty (space)
        // '1' = fill
        // '2' = shade
        // '3' = edge
        // Last char will be a null terminator despite known length
        // This is due to sprites being written in the code as strings
        const char m_texture[space::screen::tileArea];

        COLORREF SpriteColor(size_t index, int team) const;
    };

    namespace unit
    {
        extern const Sprite null;
        extern const Sprite pawn;
        extern const Sprite rook;
        extern const Sprite knight;
        extern const Sprite bishop;
        extern const Sprite queen;
        extern const Sprite king;

        extern const Sprite* all[7];
    }

    namespace symbol
    {
        extern const Sprite arrowL;
        extern const Sprite arrowR;

        extern const Sprite* arrows[2];
    }
}
