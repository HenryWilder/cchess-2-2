#include "Rendering.hpp"
#include "Board.hpp"
#include <Windows.h>

using namespace space::screen;

COLORREF CRef(Color c)
{
    return RGB(c.r, c.g, c.b);
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
