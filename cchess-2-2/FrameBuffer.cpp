#include "FrameBuffer.hpp"
#include "Constants.hpp"
#include "Utils.hpp"
#include "Color.hpp"
#include "Sprite.hpp"
#include "BoardTile.hpp"
#include <Windows.h>

extern HWND window;
extern HDC hdc;

using namespace space::screen;

COLORREF Lerp(COLORREF a, COLORREF b, float alpha = .5f)
{
    return RGB(
        BYTE(((float)GetRValue((a)) * alpha + (float)GetRValue((b))) * (1.0f - alpha)),
        BYTE(((float)GetGValue((a)) * alpha + (float)GetGValue((b))) * (1.0f - alpha)),
        BYTE(((float)GetBValue((a)) * alpha + (float)GetBValue((b))) * (1.0f - alpha)));
};

namespace frameBuffer
{
    COLORREF m_frame[totalArea];

    unsigned int Index(PixelPos pos)
    {
        unsigned int index = boardWidth * pos.y + pos.x;
        return index;
    }

    bool IsValidPxPosition(PixelPos pos)
    {
        bool valid  =
            (0 <= pos.x && pos.x < boardWidth) &&
            (0 <= pos.y && pos.y < boardWidth);

        // The PixelPos type is made up of UINTs, and so "x >= 0" does not need to be tested for.
        // July 5 2023: When was the last time you checked PixelPos? It was already using regular ints when I pulled it up for the first time in three years

        return valid;
    }

    COLORREF Get(PixelPos pixel)
    {
        return m_frame[Index(pixel)];
    }

    COLORREF SpacePatternAtPos(Coord space)
    {
        int spaceHash = space.x + space.y;
        bool isSpaceBlack = IsEven(spaceHash);
        return sprite::PaletteColor(isSpaceBlack
            ? sprite::Pltt::Board_Black
            : sprite::Pltt::Board_White);
    }

    void DrawPixel(PixelPos pixel, COLORREF color)
    {
        PixelPos start = pixel * output::gameScale;

        for (int x = 0; x < output::gameScale; ++x)
        {
            for (int y = 0; y < output::gameScale; ++y)
            {
                int px = start.x + x;
                int py = start.y + x;
                SetPixelV(hdc, px, py, color);
            }
        }
    }
    void DrawPixel(PixelPos pixel, Color color)
    {
        DrawPixel(pixel, CRef(color));
    }

    bool DrawPixelSafe(PixelPos pixel, COLORREF color)
    {
        bool isValid = IsValidPxPosition(pixel);
        if (isValid)
        {
            DrawPixel(pixel, color);
        }
        return isValid;
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

    // Writes to buffer, does not draw to render
    void WriteToBuffer(PixelPos pos, COLORREF c)
    {
        m_frame[Index(pos)] = c;
    }

    // Writes to buffer, does not draw to render
    void WriteToBuffer(PixelPos pos, Color c)
    {
        WriteToBuffer(pos, CRef(c));
    }

    bool DrawToBufferSafe(PixelPos pos, COLORREF c)
    {
        bool isValid = IsValidPxPosition(pos);
        if (isValid)
        {
            m_frame[Index(pos)] = c;
        }
        return isValid;
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
                WriteToBuffer(pix, color);
            }
        }
    }

    void DrawGhost(PixelPos spritePosTL, PixelPos cleanPosTL, const sprite::Sprite* sprite, bool team)
    {
        // Start and end WILL NOT be the same size as a tile. There will always be some amount of movement.
        PixelPos start;
        PixelPos end;

        // X-values
        if (spritePosTL.x > cleanPosTL.x)
        {
            start.x = cleanPosTL.x;
            end.x = spritePosTL.x + tileWidth;
        }
        else
        {
            start.x = spritePosTL.x;
            end.x = cleanPosTL.x + tileWidth;
        }

        // Y-values
        if (spritePosTL.y > cleanPosTL.y)
        {
            start.y = cleanPosTL.y;
            end.y = spritePosTL.y + tileWidth;
        }
        else
        {
            start.y = spritePosTL.y;
            end.y = cleanPosTL.y + tileWidth;
        }

        PixelPos px; // The pixel we are currently drawing

        size_t i = 0; // The index of the sprite's array

        for (px.y = start.y; px.y < end.y; ++px.y)
        {
            for (px.x = start.x; px.x < end.x; ++px.x)
            {
                // We want to pause incrementing the sprite index when we are outside the bounds of the sprite's image.
                bool inSpriteBounds =
                    spritePosTL.x <= px.x && px.x < (spritePosTL.x + tileWidth) &&
                    spritePosTL.y <= px.y && px.y < (spritePosTL.y + tileWidth);

                bool isOpaque = inSpriteBounds && sprite->m_texture[i] != ' ';

                COLORREF color = isOpaque
                    ? sprite->SpriteColor(i, team)
                    : Get(px);

                DrawPixel(px, color);

                i += (size_t)inSpriteBounds;
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

        for (space.y = 0; space.y < space::board::sideTileCount; ++space.y) // 8 rows
        {
            for (space.x = 0; space.x < space::board::sideTileCount; ++space.x) // 8 columns
            {
                DrawBoardPattern1Space(space);
            }
        }
    }

    void Draw()
    {
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

namespace frameBuffer2
{
    void Draw()
    {
        unsigned int i = 0;
        
        int lastChangeCol = -1;
        COLORREF prevColColor = 0;

        for (int y = 0; y < boardWidth; ++y)
        {
            for (int x = 0; x < boardWidth; ++x, ++i)
            {
                COLORREF c = frameBuffer::m_frame[i];
                if (lastChangeCol != -1 && c == prevColColor)
                {
                    continue;
                }

                using space::screen::output::gameScale;

                int endOfRegion = (lastChangeCol != -1) ? x - 1 : x;

                int left = lastChangeCol * gameScale;
                int right = (x - 1) * gameScale + gameScale;
                int top = y * gameScale;
                int bottom = top + gameScale;

                Rectangle(hdc, left, top, right, bottom);

                lastChangeCol = c;
            }
            lastChangeCol = -1;
        }
    }
}
