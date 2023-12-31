#ifndef SPRITE_H
#define SPRITE_H
#include <Windows.h>
#include <sal.h>

enum { NUM_SUPPORTED_SPRITE_VERSIONS = 2 };

// Independent of team
enum {
    NUM_CC2_UNIT_COLORS = 4,

    NUM_CC3_UNIT_COLORS = 6,

    NUM_MAX_UNIT_COLORS = ((NUM_CC3_UNIT_COLORS)>(NUM_CC2_UNIT_COLORS)?(NUM_CC3_UNIT_COLORS):(NUM_CC2_UNIT_COLORS)),
};

// Some keys share index, and some colors are empty in one version while being expressed in another.
typedef enum PaletteKey {

    // Tiles

    BRUSH_TILE_BLACK = 0,
    BRUSH_TILE_WHITE,
    BRUSH_TILE_SELECT,
    BRUSH_TILE_MOVE,
    BRUSH_TILE_CAPTURE,

    BRUSH_TILE_CHECK,
    BRUSH_TILE_TAKEN,

    // Number of tile brushes
    _NUM_PALETTE_TILE_BRUSHES,

    // CC2

    BRUSH_UNIT_WHITE_CC2_OUTLINE = _NUM_PALETTE_TILE_BRUSHES,
    BRUSH_UNIT_WHITE_CC2_FILL,
    BRUSH_UNIT_WHITE_CC2_SHADE,
    BRUSH_UNIT_WHITE_CC2_SHINE,
    // [blank]
    // [blank]

    _BRUSH_UNIT_HELPER_1,
    _NUM_UNIT_WHITE_CC2_BRUSHES = _BRUSH_UNIT_HELPER_1 - _NUM_PALETTE_TILE_BRUSHES,
    _NUM_UNIT_CC2_BRUSHES_PER_TEAM = _NUM_UNIT_WHITE_CC2_BRUSHES,

    BRUSH_UNIT_BLACK_CC2_OUTLINE = _NUM_PALETTE_TILE_BRUSHES + NUM_MAX_UNIT_COLORS,
    BRUSH_UNIT_BLACK_CC2_FILL,
    BRUSH_UNIT_BLACK_CC2_SHADE,
    BRUSH_UNIT_BLACK_CC2_SHINE,
    // [blank]
    // [blank]

    // CC3

    BRUSH_UNIT_WHITE_CC3_0 = _NUM_PALETTE_TILE_BRUSHES,
    BRUSH_UNIT_WHITE_CC3_1,
    BRUSH_UNIT_WHITE_CC3_2,
    BRUSH_UNIT_WHITE_CC3_3,
    BRUSH_UNIT_WHITE_CC3_4,
    BRUSH_UNIT_WHITE_CC3_5,

    BRUSH_UNIT_BLACK_CC3_0 = _NUM_PALETTE_TILE_BRUSHES + NUM_MAX_UNIT_COLORS,
    BRUSH_UNIT_BLACK_CC3_1,
    BRUSH_UNIT_BLACK_CC3_2,
    BRUSH_UNIT_BLACK_CC3_3,
    BRUSH_UNIT_BLACK_CC3_4,
    BRUSH_UNIT_BLACK_CC3_5,


    // Number of (uniquely indexed) brushes
    _NUM_PALETTE_BRUSHES,

    // Number of unit brushes
    _NUM_MAX_PALETTE_UNIT_BRUSHES = _NUM_PALETTE_BRUSHES - _NUM_PALETTE_TILE_BRUSHES,

    // Number of unit brushes per team
    _NUM_MAX_PALETTE_UNIT_BRUSHES_PER_TEAM = _NUM_MAX_PALETTE_UNIT_BRUSHES / 2,

} PaletteKey;

static_assert(BRUSH_UNIT_WHITE_CC2_OUTLINE == BRUSH_UNIT_WHITE_CC3_0, "Palette key mismatch");
static_assert(BRUSH_UNIT_BLACK_CC2_OUTLINE == BRUSH_UNIT_BLACK_CC3_0, "Palette key mismatch");
static_assert(_NUM_UNIT_CC2_BRUSHES_PER_TEAM == NUM_CC2_UNIT_COLORS, "Palette key miscount");
static_assert(_NUM_MAX_PALETTE_UNIT_BRUSHES_PER_TEAM == NUM_MAX_UNIT_COLORS, "Palette key miscount");

extern COLORREF cc2SpriteColors[_NUM_PALETTE_BRUSHES];
extern COLORREF cc3SpriteColors[_NUM_PALETTE_BRUSHES];

extern HBRUSH cc2SpriteBrushes[_NUM_PALETTE_BRUSHES];
extern HBRUSH cc3SpriteBrushes[_NUM_PALETTE_BRUSHES];

_Field_size_(_NUM_PALETTE_BRUSHES)
extern HBRUSH* cccSpriteBrushes; // Array reference

void InitSpriteBrushes();
void SetSpriteBrushMode(CCRenderVersion mode);

typedef struct Point {
    
    UINT16 x, y;

} Point;

// Rectangle
typedef struct SpriteRec {

    UINT16 x[2], y[2];

} SpriteRec;

// Triangle
typedef struct SpriteTri {

    Point pt[3];

} SpriteTri;

// Ellipse
typedef struct SpriteElp  {

    Point o;
    UINT16 r[2];

} SpriteElp;

// Shape
typedef enum SpriteShapeType {

    SPRITE_PART_TYPE_REC, // Rectangle
    SPRITE_PART_TYPE_TRI, // Triangle
    SPRITE_PART_TYPE_ELP, // Ellipse

} SpriteShapeType;

// Single shape - color is controlled by parent layer
typedef struct SpriteShape {

    // What shape this represents
    SpriteShapeType type;

    // The actual geometry information
    union {
        SpriteRec rec;
        SpriteTri tri;
        SpriteElp elp;
    };

} SpriteShape;

// Monochrome layer
typedef struct SpriteLayer {

    /// Geometry ///

    // Number of readable parts
    size_t numShapes;

    // Array of shapes used in the vector sprite
    _Field_size_(numShapes) SpriteShape* shapes;

    /// Color ///

    // Number of items in brushKey
    _Field_range_(1, 2) size_t numBrushAlts;

    // Set of PaletteKeys for brush and alts.
    // Dereference for default brush (will always have at least one)
    _Field_size_(numBrushAlts) PaletteKey* brushes;

} SpriteLayer;

// Vector image
typedef struct Sprite {

    // Number of readable brushes
    size_t numLayers;

    // Color layers in the sprite.
    // Drawn in ascending order - 0 is drawn first, then 1, etc.
    _Field_size_(numLayers) SpriteLayer* layers;

} Sprite;

typedef enum SpriteKey {

    SPRITE_UNIT_PAWN = 0,
    SPRITE_UNIT_ROOK,
    SPRITE_UNIT_KNIGHT,
    SPRITE_UNIT_BISHOP,
    SPRITE_UNIT_QUEEN,
    SPRITE_UNIT_KING,

    SPRITE_SYMBOLS_ARROWL,
    SPRITE_SYMBOLS_ARROWR,

    // Number of sprites, not an index.
    _NUM_SPRITES,

} SpriteKey;

extern Sprite spritesheet[(NUM_SUPPORTED_SPRITE_VERSIONS * _NUM_SPRITES)];

#endif // SPRITE_H