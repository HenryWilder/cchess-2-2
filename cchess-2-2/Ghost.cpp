#include "Ghost.hpp"
#include "Sprites.hpp"

Ghost::Ghost() :
    sprite{ &sprite::unit::null },
    pos{},
    team{} {}
