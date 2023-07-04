#pragma once
#include "Utils.h"

// A 24-bit color in RGB space
struct Color
{
    UINT r : 8;
    UINT g : 8;
    UINT b : 8;
};

COLORREF CRef(Color c);

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

        Select_Unit,      // This is the piece we want to move
        Select_Available, // This space is available to move to
        Select_TakePiece, // There is an enemy unit here we can take

        // NoSelect

        NoSelect_KingDanger, // The space would put the king into check
        NoSelect_Teammate,   // There is a teammate there blocking us from movement
    };
    extern const Color colorPalette[15];

    COLORREF PaletteColor(Pltt col);

    struct Sprite
    {
        // ' ' = empty (space)
        // '1' = fill
        // '2' = shade
        // '3' = edge
        const char* m_texture;

        COLORREF SpriteColor(int index, int team) const;
    };

    namespace unit
    {
        extern Sprite null;
        extern Sprite pawn;
        extern Sprite rook;
        extern Sprite knight;
        extern Sprite bishop;
        extern Sprite queen;
        extern Sprite king;

        extern Sprite* all[7];
    }

    namespace symbol
    {
        extern Sprite arrowL;
        extern Sprite arrowR;
    }
}

struct FrameBuffer
{
private:
    COLORREF m_frame[space::screen::totalArea]; // 64 * 64

public:
    // Converts a coordinate to an index in the frame buffer
    // DOES NOT VALIDATE INPUT (may return values outside the buffer!)
    unsigned int Index(PixelPos pos);

    // Returns a bool for whether the input coordinate can be safely referenced in the frame buffer array without unexpected results
    bool Valid(PixelPos pos);

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
    /// <summary>
    /// Sets the color of a pixel at the given coordinates.
    /// </summary>
    /// <param name="pos">The position of the pixel being set.</param>
    /// <param name="c">The color the pixel will be set to.</param>
    bool DrawToBufferSafe(PixelPos pos, COLORREF c);
    bool DrawToBufferSafe(PixelPos pos, Color c);

    void DrawSpriteFAST(Coord space, sprite::Sprite* sprite, bool team, bool effect = false);
    void DrawSymbolSkippingBuffer(Coord space, char symbol, int colorspace);
    void DrawSpriteFASTWithBG(Coord space, const sprite::Sprite* sprite, bool team, COLORREF bgColor, bool effect = false); // Draws a sprite at the position with a background of the specified color.
    void BufferCleanplateSpace(Coord space); // Draws the buffer-stored pixels of a rectangular area
    void DrawGhost(PixelPos spritePosTL, PixelPos cleanPosTL, sprite::Sprite* sprite, bool team); // Draws a sprite with a cleanplate background without drawing the sprite to the buffer.
    void DrawSprite(Coord space, sprite::Sprite* sprite, bool team, bool effect = false);

    void DrawRectFAST(int startx, int starty, int endx, int endy, COLORREF color);
    void DrawRect(int startx, int starty, int endx, int endy, COLORREF color);
    void DrawRect(int startx, int starty, int endx, int endy, Color color);

    void DrawGridSpaceFAST(Coord space, COLORREF color);
    void DrawGridSpace(Coord space, COLORREF color);

    void DrawBoardPattern1SpaceFAST(Coord space);
    void DrawBoardPattern1Space(Coord space);

    void DrawBoardPattern();

    /// <summary>
    /// Draw the entire frame buffer to the console.
    /// </summary>
    void Draw();
};

extern FrameBuffer g_frameBuffer;

// Used for animating sprite movement
class Ghost
{
    sprite::Sprite* sprite; // The sprite we are drawing
    PixelPos pos; // Current position in pixel-space
    bool team;

    // This is for moving the ghost one position at a time
    void Move(PixelPos newPos);

    // https://easings.net/#easeInOutQuad
    double EaseInOutQuad(double t);

public:
    Ghost();
    Ghost(Coord space, sprite::Sprite* sprite, bool team);
    // Performs an animated motion with smoothed transition
    // Note that this uses board space position and not pixelspace position
    void Glide(Coord _newPos);
};
