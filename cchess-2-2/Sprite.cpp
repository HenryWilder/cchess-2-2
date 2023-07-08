#include "Sprite.hpp"

namespace sprite
{
    const Color colorPalette[15]
    {
        // Board

        { 236, 167,  95 }, // Black
        { 252, 219, 166 },  // White

                            // Black

        {  80,  80,  90 }, // Fill
        {  50,  55,  60 }, // Shade
        {  40,  30,  50 }, // Outline
        { 100, 100, 110 }, // Shine

                           // White

        { 240, 240, 230 }, // Fill
        { 180, 150, 120 }, // Shade
        { 100, 100,  90 }, // Outline
        { 255, 255, 255 }, // Shine

                           // Select

        {  44, 200,  37 }, // Unit we are moving
        { 155, 235, 135 }, // Available space we can move to
        { 255,  80,  80 }, // Available space with a piece we can take

                           // NoSelect

        { 255, 200,  80 }, // King would be put in check
        { 127, 127, 127 }, // A teammate is already at that space
    };

    COLORREF PaletteColor(Pltt col)
    {
        return CRef(colorPalette[(unsigned int)col]);
    }

    COLORREF Sprite::SpriteColor(size_t index, int team) const
    {
        char value = m_texture[index];

        Pltt out = Pltt::Board_Black;

        bool isTeam  = (team == 0 || team == 1);
        bool isBoard = (team == 2);

        // Glow
        if ((isTeam && value == '5') || (isBoard && value == '2'))
        {
            return PaletteColor(Pltt::Select_Unit);
        }

        if (isTeam)
        {
            unsigned int teamOffset = (unsigned int)((team == 1)
                ? Pltt::UnitW_Fill
                : Pltt::UnitB_Fill);

            out = (Pltt)((unsigned int)(value - '1') + teamOffset);
        }
        else
        {
            switch (value)
            {
            case '1': out = Pltt::Select_Available;    break;
                // Todo: Something about this gap.
            case '3': out = Pltt::Select_TakePiece;    break;
            case '4': out = Pltt::NoSelect_KingDanger; break;
            case '5': out = Pltt::NoSelect_Teammate;   break;
            }
        }

        return PaletteColor(out);
    }
}
