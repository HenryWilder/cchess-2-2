#ifndef SPRITE_BUILDER_MACROS_H
#define SPRITE_BUILDER_MACROS_H
#include "sprite.h"

#define V(x,...) { 0x0##x, ((0x1##__VA_ARGS__ == 0x1) ? 0x0##x : 0x0##__VA_ARGS__) }

#define REC(xRange, yRange) {.type = SPRITE_PART_TYPE_REC, .rec = {.x = xRange, .y = yRange } }
#define TRI(p0, p1, p2)     {.type = SPRITE_PART_TYPE_TRI, .tri = {.pt = { p0, p1, p2 } } }
#define ELP(origin, rx, ry) {.type = SPRITE_PART_TYPE_ELP, .elp = {.o = origin, .r = { rx, ry } } }

#define SPRITE_SHAPE(identifier)

#define ARR(...) { __VA_ARGS__ }

#define LAYER(_name, _paletteArr, _shapeArr) \
    const PaletteKey _name##Plt[] = _paletteArr; \
    const SpriteShape _name##Shapes[] = _shapeArr; \
    const SpriteLayer _name##Layer = { .numShapes = _countof(_name##Shapes), .shapes = _name##Shapes, .numBrushAlts = _countof(_name##Plt), .brushes = _name##Plt }

LAYER(
    test,
    ARR( BRUSH_UNIT_WHITE_CC3_0, BRUSH_UNIT_BLACK_CC3_0 ),
    ARR( REC( V( 0 ), V( 0 ) ) )
)

#endif // !SPRITE_BUILDER_MACROS_H