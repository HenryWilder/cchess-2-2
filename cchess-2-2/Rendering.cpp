#include "Rendering.h"
#include "Board.h"

using namespace space;

COLORREF CRef(Color c)
{
    return RGB(c.r, c.g, c.b);
}

unsigned int FrameBuffer::Index(PixelPos pos)
{
    unsigned int index = (screen::boardWidth) * pos.y + pos.x;
    return index;
}

bool FrameBuffer::Valid(PixelPos pos)
{
    bool valid;
    valid = (
        (pos.x < screen::boardWidth) && // The input x is not beyond the boundaries of the screen, which would wrap around to the next row
        (pos.y < screen::boardWidth)); // The input position does not produce an index outside the buffer, which would throw an exception

                                       // The input y does not need to be validated if both these are true.
                                       // The PixelPos type is made up of UINTs, and so "x >= 0" does not need to be tested for.
    return valid;
}

COLORREF FrameBuffer::Get(PixelPos pixel)
{
    return m_frame[Index(pixel)];
}

COLORREF FrameBuffer::SpacePatternAtPos(Coord space)
{
    // Pick the color
    if (Even(space.x + space.y))
        return sprite::PaletteColor(sprite::Pltt::Board_Black);
    else
        return sprite::PaletteColor(sprite::Pltt::Board_White);
}

void FrameBuffer::DrawPixel(PixelPos pixel, COLORREF color)
{
    PixelPos pix = pixel * space::screen::gameScale; // Output-space

    for (int x = pix.x; x < pix.x + space::screen::gameScale; ++x)
        for (int y = pix.y; y < pix.y + space::screen::gameScale; ++y)
            SetPixelV(hdc, x, y, color);
}
void FrameBuffer::DrawPixel(PixelPos pixel, Color color)
{
    DrawPixel(pixel, CRef(color));
}

bool FrameBuffer::DrawPixelSafe(PixelPos pixel, COLORREF color)
{
    if (Valid(pixel)) {
        DrawPixel(pixel, color);
        return true;
    }
    else
        return false;
}
bool FrameBuffer::DrawPixelSafe(PixelPos pixel, Color color)
{
    return DrawPixelSafe(pixel, CRef(color));
}

void FrameBuffer::DrawToBufferAndScreen(PixelPos pos, COLORREF c)
{
    m_frame[Index(pos)] = c;
    DrawPixel(pos, c);
}

void FrameBuffer::DrawToBufferAndScreen(PixelPos pos, Color c)
{
    DrawToBufferAndScreen(pos, CRef(c));
}

void FrameBuffer::WriteToBuffer(PixelPos pos, COLORREF c)
{
    m_frame[Index(pos)] = c;
}

void FrameBuffer::WriteToBuffer(PixelPos pos, Color c)
{
    WriteToBuffer(pos, CRef(c));
}

bool FrameBuffer::DrawToBufferSafe(PixelPos pos, COLORREF c)
{
    if (Valid(pos)) {
        m_frame[Index(pos)] = c;
        return true;
    }
    else
        return false;
}
bool FrameBuffer::DrawToBufferSafe(PixelPos pos, Color c)
{
    return DrawToBufferSafe(pos, CRef(c));
}

void FrameBuffer::DrawSpriteFAST(Coord space, sprite::Sprite* sprite, bool team, bool effect)
{
    BoardTile spaceBounds = BoardTile(space);

    PixelPos pix;

    unsigned int i = 0; // The index of the sprite's array

    for (pix.y = spaceBounds.start.y; pix.y < spaceBounds.end.y; ++pix.y)
    {
        for (pix.x = spaceBounds.start.x; pix.x < spaceBounds.end.x; ++pix.x)
        {
            if (sprite->m_texture[i] != ' ') // Check is opaque
                DrawToBufferAndScreen(pix, sprite->SpriteColor(i, team)); // Draws the pixel from the frame buffer to the console

            ++i;
        }
    }
}

void FrameBuffer::DrawSymbolSkippingBuffer(Coord space, char symbol, int colorspace)
{
    sprite::Sprite* sprite;

    switch (symbol)
    {
    case '<':
        sprite = &sprite::symbol::arrowL;
        break;
    case '>':
        sprite = &sprite::symbol::arrowR;
        break;
    default:
        sprite = nullptr;
        break;
    }

    if (sprite != nullptr)
    {
        BoardTile spaceBounds = BoardTile(space);

        PixelPos pix;

        unsigned int i = 0; // The index of the sprite's array

        for (pix.y = spaceBounds.start.y; pix.y < spaceBounds.end.y; ++pix.y)
        {
            for (pix.x = spaceBounds.start.x; pix.x < spaceBounds.end.x; ++pix.x)
            {
                if (sprite->m_texture[i] != ' ') // Check is opaque
                    DrawPixel(pix, sprite->SpriteColor(i, colorspace)); // Draws the pixel from the frame buffer to the console

                ++i;
            }
        }
    }
}

COLORREF AverageCRef(COLORREF a, COLORREF b, float alpha = .5f)
{
    return RGB(
        BYTE(((float)GetRValue((a)) * alpha + (float)GetRValue((b))) * (1.0f - alpha)),
        BYTE(((float)GetGValue((a)) * alpha + (float)GetGValue((b))) * (1.0f - alpha)),
        BYTE(((float)GetBValue((a)) * alpha + (float)GetBValue((b))) * (1.0f - alpha)));
}

void FrameBuffer::DrawSpriteFASTWithBG(Coord space, const sprite::Sprite* sprite, bool team, COLORREF bgColor, bool effect)
{
    BoardTile spaceBounds = BoardTile(space);

    PixelPos pix;

    unsigned int i = 0; // The index of the sprite's array

    for (pix.y = spaceBounds.start.y; pix.y < spaceBounds.end.y; ++pix.y)
    {
        for (pix.x = spaceBounds.start.x; pix.x < spaceBounds.end.x; ++pix.x)
        {
            if (sprite->m_texture[i] != ' ') // Check is opaque
            {
                COLORREF pixelColor = sprite->SpriteColor(i, team);

                if (effect) pixelColor = AverageCRef(pixelColor, bgColor, .4f); // Causes ghost effect

                DrawToBufferAndScreen(pix, pixelColor); // Draws the pixel from the frame buffer to the console
            }
            else
                DrawToBufferAndScreen(pix, bgColor);

            ++i;
        }
    }
}

void FrameBuffer::BufferCleanplateSpace(Coord space)
{
    COLORREF color = SpacePatternAtPos(space);

    BoardTile spaceBounds = BoardTile(space);

    PixelPos pix;

    for (pix.y = spaceBounds.start.y; pix.y < spaceBounds.end.y; ++pix.y)
    {
        for (pix.x = spaceBounds.start.x; pix.x < spaceBounds.end.x; ++pix.x)
        {
            WriteToBuffer(pix, color); // Writes to buffer, does not draw to render
        }
    }
    //DrawGridSpaceFAST(space, 0); Sanity check
}

void FrameBuffer::DrawGhost(
    PixelPos spritePosTL, // The top-left corner of the sprite
    PixelPos cleanPosTL, // The top-left corner of the cleanplate
    sprite::Sprite* sprite, bool team)
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

void FrameBuffer::DrawSprite(Coord space, sprite::Sprite* sprite, bool team, bool effect)
{
    BoardTile spaceBounds = BoardTile(space);

    PixelPos pix;

    unsigned int i = 0; // The index of the sprite's array

    for (pix.y = spaceBounds.start.y; pix.y < spaceBounds.end.y; ++pix.y)
    {
        for (pix.x = spaceBounds.start.x; pix.x < spaceBounds.end.x; ++pix.x)
        {
            if (sprite->m_texture[i] != ' ') // Check is opaque
            {
                WriteToBuffer(pix, sprite->SpriteColor(i, team)); // Draws the pixel from the frame buffer to the console
            }

            ++i;
        }
    }
}

void FrameBuffer::DrawRectFAST(int startx, int starty, int endx, int endy, COLORREF color)
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

void FrameBuffer::DrawRect(int startx, int starty, int endx, int endy, COLORREF color)
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
void FrameBuffer::DrawRect(int startx, int starty, int endx, int endy, Color color)
{
    DrawRect(startx, starty, endx, endy, CRef(color));
}

void FrameBuffer::DrawGridSpaceFAST(Coord space, COLORREF color)
{
    BoardTile spaceBounds = BoardTile(space);
    DrawRectFAST(spaceBounds.start.x, spaceBounds.start.y, spaceBounds.end.x, spaceBounds.end.y, color);
}

void FrameBuffer::DrawGridSpace(Coord space, COLORREF color)
{
    BoardTile spaceBounds = BoardTile(space);
    DrawRect(spaceBounds.start.x, spaceBounds.start.y, spaceBounds.end.x, spaceBounds.end.y, color);
}

void FrameBuffer::DrawBoardPattern1SpaceFAST(Coord space)
{
    DrawGridSpaceFAST(space, SpacePatternAtPos(space));
}

void FrameBuffer::DrawBoardPattern1Space(Coord space)
{
    DrawGridSpace(space, SpacePatternAtPos(space));
}

void FrameBuffer::DrawBoardPattern()
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

void FrameBuffer::Draw()
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

FrameBuffer g_frameBuffer;

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

    COLORREF Sprite::SpriteColor(int index, int team) const
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
    g_frameBuffer.DrawGhost(newPos, pos, sprite, team);
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

Ghost::Ghost()
{
    sprite = &sprite::unit::null;
    pos = { 0,0 };
    team = 0;
}

Ghost::Ghost(Coord space, sprite::Sprite* sprite, bool team)
{
    this->sprite = sprite;
    this->pos = PixelSpace(space);
    this->team = team;
}

void Ghost::Glide(Coord _newPos)
{
    PixelPos startingPos = pos; // Storing this because pos will be changing over the course of this function.
    PixelPos newPos = PixelSpace(_newPos);
    PixelPos distance = newPos - pos;

    g_frameBuffer.BufferCleanplateSpace(BoardSpace(pos)); // Removes the unit sprite from the space in the buffer
                                                          //g_frameBuffer.Draw(); // Sanity check

    int napTime = 20; // ms between frames

    double transitionTime = 1.0; // Seconds the transition should take

    double tPerFrame = transitionTime / (double)napTime; // How much t should change per frame

    double deltaX, deltaY;
    deltaX = (double)distance.x;
    deltaY = (double)distance.y;

    // Cumulative, get your mind out of the gutter.
    double cumX = 0.0;
    double cumY = 0.0;


    double t; // Time along the easing curve
    for (t = 0.0; t <= 1.0; t = t + tPerFrame)
    {
        Move(startingPos + PixelPos{ (int)(cumX + 0.5), (int)(cumY + 0.5)});
        cumX = deltaX * EaseInOutQuad(t);
        cumY = deltaY * EaseInOutQuad(t);
        SleepForMS(napTime); // 0.02 seconds
    }
    Move(newPos); // This is here to guarantee absolutely that the ghost will line up with the piece at the end.
}
