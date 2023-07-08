#pragma once
#include "Coord.hpp"
#include "PixelPos.hpp"
#include "PositionUtils.hpp"

namespace sprite { struct Sprite; }

// Used for animating sprite movement
class Ghost
{
    const sprite::Sprite* sprite; // The sprite we are drawing
    PixelPos pos; // Current position in pixel-space
    bool team;

    // This is for moving the ghost one position at a time
    void Move(PixelPos newPos);

    // https://easings.net/#easeInOutQuad
    double EaseInOutQuad(double t);

public:
    Ghost();

    constexpr Ghost(Coord space, const sprite::Sprite* sprite, bool team) :
        sprite{ sprite },
        pos{ PixelSpace(space) },
        team{ team } {}

    // Performs an animated motion with smoothed transition
    // Note that this uses board space position and not pixelspace position
    void Glide(Coord _newPos);
};
