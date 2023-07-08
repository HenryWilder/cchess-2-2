#ifndef CONSTANTS_H
#define CONSTANTS_H

// macros can be used for compile-time constants, like stack array sizes.
// const ints used for checking the values of the macros.

#define NUM_BOARD_SIDE_TILES 8
static const int numBoardSideTiles = NUM_BOARD_SIDE_TILES;
#define NUM_BOARD_TILES (NUM_BOARD_SIDE_TILES*NUM_BOARD_SIDE_TILES)
static const int numBoardTiles = NUM_BOARD_TILES;

#define NUM_TILE_SIDE_PIXELS 16
static const int numTileSidePixels = NUM_TILE_SIDE_PIXELS;
#define NUM_TILE_PIXELS (NUM_TILE_SIDE_PIXELS*NUM_TILE_SIDE_PIXELS)
static const int numTilePixels = NUM_TILE_PIXELS;

#define NUM_BOARD_SIDE_PIXELS (NUM_BOARD_SIDE_TILES*NUM_TILE_SIDE_PIXELS)
static const int numBoardSidePixels = NUM_BOARD_SIDE_PIXELS;
#define NUM_BOARD_PIXELS (NUM_BOARD_SIDE_PIXELS*NUM_BOARD_SIDE_PIXELS)
static const int numBoardPixels = NUM_BOARD_PIXELS;

#define GAME_SCALE 2
static const int gameScale = GAME_SCALE;
#define NUM_OUTPUT_TILE_SIDE_PIXELS (NUM_TILE_SIDE_PIXELS*GAME_SCALE)
static const int numOutputTileSidePixels = NUM_OUTPUT_TILE_SIDE_PIXELS;
#define NUM_OUTPUT_TILE_PIXELS (NUM_TILE_PIXELS*GAME_SCALE)
static const int numOutputTilePixels = NUM_OUTPUT_TILE_PIXELS;
#define NUM_OUTPUT_BOARD_SIDE_PIXELS (NUM_BOARD_SIDE_PIXELS*GAME_SCALE)
static const int numOutputBoardSidePixels = NUM_OUTPUT_BOARD_SIDE_PIXELS;
#define NUM_OUTPUT_BOARD_PIXELS (NUM_BOARD_PIXELS*GAME_SCALE)
static const int numOutputBoardPixels = NUM_OUTPUT_BOARD_PIXELS;

#endif // !CONSTANTS_H