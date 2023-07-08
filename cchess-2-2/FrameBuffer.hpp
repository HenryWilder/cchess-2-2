#pragma once
#include "PixelPos.hpp"
#include "Coord.hpp"
#include "Color.hpp"
#include <Windows.h>

namespace sprite { struct Sprite; }

COLORREF CRef(Color c);

namespace frameBuffer
{
    // Converts a coordinate to an index in the frame buffer
    // ! DOES NOT VALIDATE INPUT (may return values outside the buffer)
    unsigned int Index(PixelPos pos);

    // Whether the input coordinate is within the frame buffer
    bool IsValidPxPosition(PixelPos pos);

    COLORREF Get(PixelPos pixel);

    COLORREF SpacePatternAtPos(Coord space);

    void DrawPixel(PixelPos pixel, COLORREF color);
    void DrawPixel(PixelPos pixel, Color color);
    bool DrawPixelSafe(PixelPos pixel, COLORREF color);
    bool DrawPixelSafe(PixelPos pixel, Color color);

    void DrawToBufferAndScreen(PixelPos pos, COLORREF c);
    void DrawToBufferAndScreen(PixelPos pos, Color c);

    void WriteToBuffer(PixelPos pos, COLORREF c);
    void WriteToBuffer(PixelPos pos, Color c);

    bool DrawToBufferSafe(PixelPos pos, COLORREF c);
    bool DrawToBufferSafe(PixelPos pos, Color c);

    void DrawSpriteNOW(Coord space, const sprite::Sprite* sprite, bool team, bool effect = false);

    void DrawSymbolSkippingBuffer(Coord space, char symbol, int colorspace);

    // Draws a sprite at the position with a background of the specified color.
    void DrawSpriteWithBackgroundNOW(Coord space, const sprite::Sprite* sprite, bool team, COLORREF bgColor, bool useEffect = false);

    // Draws the buffer-stored pixels of a rectangular area
    void BufferCleanplateSpace(Coord space);

    // Draws a sprite with a cleanplate background without drawing the sprite to the buffer.
    void DrawGhost(PixelPos spritePosTL, PixelPos cleanPosTL, const sprite::Sprite* sprite, bool team);

    void DrawSprite(Coord space, const sprite::Sprite* sprite, bool team, bool effect = false);

    void DrawRectNOW(int startx, int starty, int endx, int endy, COLORREF color);
    void DrawRect(int startx, int starty, int endx, int endy, COLORREF color);
    void DrawRect(int startx, int starty, int endx, int endy, Color color);

    void DrawGridSpaceNOW(Coord space, COLORREF color);
    void DrawGridSpace(Coord space, COLORREF color);

    void DrawBoardPattern1SpaceNOW(Coord space);
    void DrawBoardPattern1Space(Coord space);

    void DrawBoardPattern();

    // Draw the entire frame buffer to the console.
    void Draw();
}

namespace frameBuffer2
{

    // Draw the entire frame buffer to the console.
    void Draw();
}
