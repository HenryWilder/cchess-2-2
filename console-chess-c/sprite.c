#include "sprite.h"
#include "output.h"

HBRUSH cc2SpriteBrushes[_NUM_PALETTE_BRUSHES];
HBRUSH cc3SpriteBrushes[_NUM_PALETTE_BRUSHES];

_Field_size_(_NUM_PALETTE_BRUSHES)
HBRUSH* cccSpriteBrushes; // Array reference

void InitSpriteBrushes()
{
    for (size_t i = 0; i < _NUM_PALETTE_BRUSHES; ++i)
    {
        cc2SpriteBrushes[i] = CreateSolidBrush(cc2SpriteColors[i]);
    }

    for (size_t i = 0; i < _NUM_PALETTE_BRUSHES; ++i)
    {
        cc3SpriteBrushes[i] = CreateSolidBrush(cc3SpriteColors[i]);
    }
}

void SetRenderVersion(CCRenderVersion version)
{
    switch (version)
    {
    default: // Unsupported/nonexistent version
        assert(0);
        return;

    case 0: // Null version
        assert(0);
        return;

    case 2:
        cccSpriteBrushes = cc2SpriteBrushes;
        break;

    case 3:
        cccSpriteBrushes = cc3SpriteBrushes;
        break;
    }
}
