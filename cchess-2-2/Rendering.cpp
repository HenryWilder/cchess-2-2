#include "Rendering.h"
#include "Board.h"

using namespace space;

COLORREF CRef(Color c)
{
    return RGB(c.r, c.g, c.b);
}

COLORREF Lerp(COLORREF a, COLORREF b, float alpha = .5f)
{
    return RGB(
        BYTE(((float)GetRValue((a)) * alpha + (float)GetRValue((b))) * (1.0f - alpha)),
        BYTE(((float)GetGValue((a)) * alpha + (float)GetGValue((b))) * (1.0f - alpha)),
        BYTE(((float)GetBValue((a)) * alpha + (float)GetBValue((b))) * (1.0f - alpha)));
}

namespace frameBuffer
{
    COLORREF m_frame[space::screen::totalArea]; // 64 * 64

    unsigned int Index(PixelPos pos)
    {
        unsigned int index = (screen::boardWidth)*pos.y + pos.x;
        return index;
    }

    bool IsValidPxPosition(PixelPos pos)
    {
        bool valid;
        valid = (
            (pos.x < screen::boardWidth) && // The input x is not beyond the boundaries of the screen, which would wrap around to the next row
            (pos.y < screen::boardWidth)); // The input position does not produce an index outside the buffer, which would throw an exception

                                           // The input y does not need to be validated if both these are true.
                                           // The PixelPos type is made up of UINTs, and so "x >= 0" does not need to be tested for.
        return valid;
    }

    COLORREF Get(PixelPos pixel)
    {
        return m_frame[Index(pixel)];
    }

    COLORREF SpacePatternAtPos(Coord space)
    {
        // Pick the color
        if (IsEven(space.x + space.y))
            return sprite::PaletteColor(sprite::Pltt::Board_Black);
        else
            return sprite::PaletteColor(sprite::Pltt::Board_White);
    }

    void DrawPixel(PixelPos pixel, COLORREF color)
    {
        PixelPos pix = pixel * space::screen::gameScale; // Output-space

        for (int x = pix.x; x < pix.x + space::screen::gameScale; ++x)
            for (int y = pix.y; y < pix.y + space::screen::gameScale; ++y)
                SetPixelV(hdc, x, y, color);
    }
    void DrawPixel(PixelPos pixel, Color color)
    {
        DrawPixel(pixel, CRef(color));
    }

    bool DrawPixelSafe(PixelPos pixel, COLORREF color)
    {
        if (IsValidPxPosition(pixel)) {
            DrawPixel(pixel, color);
            return true;
        }
        else
            return false;
    }
    bool DrawPixelSafe(PixelPos pixel, Color color)
    {
        return DrawPixelSafe(pixel, CRef(color));
    }

    void DrawToBufferAndScreen(PixelPos pos, COLORREF c)
    {
        m_frame[Index(pos)] = c;
        DrawPixel(pos, c);
    }

    void DrawToBufferAndScreen(PixelPos pos, Color c)
    {
        DrawToBufferAndScreen(pos, CRef(c));
    }

    void WriteToBuffer(PixelPos pos, COLORREF c)
    {
        m_frame[Index(pos)] = c;
    }

    void WriteToBuffer(PixelPos pos, Color c)
    {
        WriteToBuffer(pos, CRef(c));
    }

    bool DrawToBufferSafe(PixelPos pos, COLORREF c)
    {
        if (IsValidPxPosition(pos)) {
            m_frame[Index(pos)] = c;
            return true;
        }
        else
            return false;
    }
    bool DrawToBufferSafe(PixelPos pos, Color c)
    {
        return DrawToBufferSafe(pos, CRef(c));
    }

    void DrawSpriteNOW(Coord space, const sprite::Sprite* sprite, bool team, bool effect)
    {
        BoardTile spaceBounds = BoardTile(space);

        PixelPos px;

        size_t i = 0;
        for (px.y = spaceBounds.beginPx.y; px.y < spaceBounds.endPx.y; ++px.y)
        {
            for (px.x = spaceBounds.beginPx.x; px.x < spaceBounds.endPx.x; ++px.x, ++i)
            {
                // Skip transparent
                if (sprite->m_texture[i] != ' ') continue;

                DrawToBufferAndScreen(px, sprite->SpriteColor(i, team));
            }
        }
    }

    void DrawSymbolSkippingBuffer(Coord space, char symbol, int colorspace)
    {
        if (symbol != '<' && symbol != '>') return;

        const sprite::Sprite* sprite = (symbol == '<') 
            ? &sprite::symbol::arrowL
            : &sprite::symbol::arrowR;

        BoardTile spaceBounds = BoardTile(space);

        PixelPos px;

        size_t i = 0;
        for (px.y = spaceBounds.beginPx.y; px.y < spaceBounds.endPx.y; ++px.y)
        {
            for (px.x = spaceBounds.beginPx.x; px.x < spaceBounds.endPx.x; ++px.x, ++i)
            {
                // Skip transparent
                if (sprite->m_texture[i] == ' ') continue;

                DrawPixel(px, sprite->SpriteColor(i, colorspace));
            }
        }
    }

    void DrawSpriteWithBackgroundNOW(Coord space, const sprite::Sprite* sprite, bool team, COLORREF bgColor, bool useEffect)
    {
        BoardTile spaceBounds = BoardTile(space);

        PixelPos px;

        size_t i = 0;
        for (px.y = spaceBounds.beginPx.y; px.y < spaceBounds.endPx.y; ++px.y)
        {
            for (px.x = spaceBounds.beginPx.x; px.x < spaceBounds.endPx.x; ++px.x, ++i)
            {
                // Draw background where transparent
                if (sprite->m_texture[i] == ' ')
                {
                    DrawToBufferAndScreen(px, bgColor);
                    continue;
                }

                COLORREF pixelColor = sprite->SpriteColor(i, team);

                // Ghost effect
                if (useEffect)
                {
                    pixelColor = Lerp(pixelColor, bgColor, .4f);
                }

                DrawToBufferAndScreen(px, pixelColor);
            }
        }
    }

    void BufferCleanplateSpace(Coord space)
    {
        COLORREF color = SpacePatternAtPos(space);

        BoardTile spaceBounds = BoardTile(space);

        PixelPos pix;

        for (pix.y = spaceBounds.beginPx.y; pix.y < spaceBounds.endPx.y; ++pix.y)
        {
            for (pix.x = spaceBounds.beginPx.x; pix.x < spaceBounds.endPx.x; ++pix.x)
            {
                WriteToBuffer(pix, color); // Writes to buffer, does not draw to render
            }
        }
        //DrawGridSpaceNOW(space, 0); Sanity check
    }

    void DrawGhost(
        PixelPos spritePosTL, // The top-left corner of the sprite
        PixelPos cleanPosTL, // The top-left corner of the cleanplate
        const sprite::Sprite* sprite, bool team)
    {
        // Start and end WILL NOT be the same size as a tile. There will always be some amount of movement.
        PixelPos start;
        PixelPos end;

        // X-values
        if (spritePosTL.x > cleanPosTL.x) {
            start.x = cleanPosTL.x;
            end.x = spritePosTL.x + screen::tileWidth;
        }
        else {
            start.x = spritePosTL.x;
            end.x = cleanPosTL.x + screen::tileWidth;
        }
        // Y-values
        if (spritePosTL.y > cleanPosTL.y) {
            start.y = cleanPosTL.y;
            end.y = spritePosTL.y + screen::tileWidth;
        }
        else {
            start.y = spritePosTL.y;
            end.y = cleanPosTL.y + screen::tileWidth;
        }


        PixelPos pix; // The pixel we are currently drawing

        unsigned int i = 0; // The index of the sprite's array

        for (pix.y = start.y; pix.y < end.y; ++pix.y) {
            for (pix.x = start.x; pix.x < end.x; ++pix.x)
            {
                // We want to pause incrementing the sprite index when we are outside the bounds of the sprite's image.
                bool inSpriteBounds =
                    pix.x >= spritePosTL.x &&
                    pix.y >= spritePosTL.y &&
                    pix.x < (spritePosTL.x + screen::tileWidth) &&
                    pix.y < (spritePosTL.y + screen::tileWidth);

                if (inSpriteBounds)
                {
                    if (sprite->m_texture[i] != ' ') // Check is opaque
                        DrawPixel(pix, sprite->SpriteColor(i, team));
                    else
                        DrawPixel(pix, Get(pix));

                    ++i;
                }
                else
                {
                    DrawPixel(pix, Get(pix));
                }
            }
        }
    }

    void DrawSprite(Coord space, const sprite::Sprite* sprite, bool team, bool effect)
    {
        BoardTile spaceBounds = BoardTile(space);

        PixelPos pix;

        unsigned int i = 0; // The index of the sprite's array

        for (pix.y = spaceBounds.beginPx.y; pix.y < spaceBounds.endPx.y; ++pix.y)
        {
            for (pix.x = spaceBounds.beginPx.x; pix.x < spaceBounds.endPx.x; ++pix.x)
            {
                if (sprite->m_texture[i] != ' ') // Check is opaque
                {
                    WriteToBuffer(pix, sprite->SpriteColor(i, team)); // Draws the pixel from the frame buffer to the console
                }

                ++i;
            }
        }
    }

    void DrawRectNOW(int startx, int starty, int endx, int endy, COLORREF color)
    {
        PixelPos pos;

        for (int x = startx; x < endx; ++x)
        {
            pos.x = x;

            for (int y = starty; y < endy; ++y)
            {
                pos.y = y;

                DrawToBufferAndScreen(pos, color); // Draws the pixel from the frame buffer to the console
            }
        }
    }

    void DrawRect(int startx, int starty, int endx, int endy, COLORREF color)
    {
        PixelPos pos;

        for (int x = startx; x < endx; ++x)
        {
            pos.x = x;

            for (int y = starty; y < endy; ++y)
            {
                pos.y = y;

                WriteToBuffer(pos, color); // Draws the pixel from the frame buffer to the console
            }
        }
    }
    void DrawRect(int startx, int starty, int endx, int endy, Color color)
    {
        DrawRect(startx, starty, endx, endy, CRef(color));
    }

    void DrawGridSpaceNOW(Coord space, COLORREF color)
    {
        BoardTile spaceBounds = BoardTile(space);
        DrawRectNOW(spaceBounds.beginPx.x, spaceBounds.beginPx.y, spaceBounds.endPx.x, spaceBounds.endPx.y, color);
    }

    void DrawGridSpace(Coord space, COLORREF color)
    {
        BoardTile spaceBounds = BoardTile(space);
        DrawRect(spaceBounds.beginPx.x, spaceBounds.beginPx.y, spaceBounds.endPx.x, spaceBounds.endPx.y, color);
    }

    void DrawBoardPattern1SpaceNOW(Coord space)
    {
        DrawGridSpaceNOW(space, SpacePatternAtPos(space));
    }

    void DrawBoardPattern1Space(Coord space)
    {
        DrawGridSpace(space, SpacePatternAtPos(space));
    }

    void DrawBoardPattern()
    {
        PixelPos space;

        for (space.y = 0; space.y < game::sideTileCount; ++space.y) // 8 rows
        {
            for (space.x = 0; space.x < game::sideTileCount; ++space.x) // 8 columns
            {
                DrawBoardPattern1Space(space);
            }
        }
    }

    void Draw()
    {
        using namespace screen;

        unsigned int i = 0;

        PixelPos pixel = { 0U,0U };

        for (pixel.y = 0U; pixel.y < boardWidth; ++pixel.y)
        {
            for (pixel.x = 0U; pixel.x < boardWidth; ++pixel.x)
            {
                DrawPixel(pixel, m_frame[i]);

                ++i;
            }
        }
    }
}

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

void Ghost::Move(PixelPos newPos)
{
    frameBuffer::DrawGhost(newPos, pos, sprite, team);
    pos = newPos;
}

// https://easings.net/#easeInOutQuad
double Ghost::EaseInOutQuad(double t)
{
    if (0.0 <= t && t < 0.5)
        return 2.0 * t * t;
    else if (0.5 <= t && t <= 1)
        return 1.0 - pow(-2.0 * t + 2.0, 2.0) / 2.0;
    else
        return 0.0;
}

void Ghost::Glide(Coord _newPos)
{
    PixelPos startingPos = pos;
    PixelPos newPos = PixelSpace(_newPos);
    PixelPos distance = newPos - pos;

    // Remove unit sprite from space in the buffer
    frameBuffer::BufferCleanplateSpace(BoardSpace(pos));

    constexpr int dt = 20;
    constexpr int transitionTime = 1000;
    constexpr int numFrames = transitionTime / dt;

    double
        deltaX{ (double)distance.x },
        deltaY{ (double)distance.y };

    for (int frame = 0; frame < numFrames; ++frame)
    {
        double t = ((double)frame * (double)dt);

        double ease = EaseInOutQuad(t);
        double easedX = deltaX * ease;
        double easedY = deltaY * ease;

        PixelPos offset = PixelPos(easedX, easedY);

        PixelPos newPos = startingPos + offset;

        Move(newPos);
        SleepForMS(dt);
    }

    // Guarantee that the ghost lines up with the piece
    Move(newPos);
}
