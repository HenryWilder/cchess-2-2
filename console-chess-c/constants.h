#ifndef CONSTANTS_H
#define CONSTANTS_H

#pragma region // Board

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

#pragma endregion

#pragma region // Units

// The most moves that any piece can possibly have is a queen at the center of an empty board with an odd-numbered side length.
// In such a case, the queen can move an entire row and column, as well as two full diagonals (whose lengths match the side length).
// However, the position she is currently at is duplicated in all four of these lines, and simultaneously not a valid move.
// Therefore we can subtract it prior to the multiplication.
// 
// The result on a board of 5x5 tiles is 2 tiles in all directions; or a total of 4(5-1=4)=16.
// .-------------------.
// | x |   | x |   | x |
// |---+---+---+---+---|
// |   | x | x | x |   |
// |---+---+---+---+---|
// | x | x | Q | x | x |
// |---+---+---+---+---|
// |   | x | x | x |   |
// |---+---+---+---+---|
// | x |   | x |   | x |
// '-------------------'
// 
// On an even-side-number board this number is smaller because at most one of the diagonals can ever match a full side length at a time.
// The difference is 1 space is lost compared to if even numbers shared the same "centering property" with odd numbers.
// 
// For example, on a 6x6 board, the largest number of moves that can be achieved for a space is 4(6-1=5)-1=19
// .-----------------------.
// | x |   | x |   | x |   |
// |---+---+---+---+---+---|
// |   | x | x | x |   |   |
// |---+---+---+---+---+---|
// | x | x | Q | x | x | x |
// |---+---+---+---+---+---|
// |   | x | x | x |   |   |
// |---+---+---+---+---+---|
// | x |   | x |   | x |   |
// |---+---+---+---+---+---|
// |   |   | x |   |   | x |
// '-----------------------'

// The maximum moves a pawn can have are:
// 1. Forward 1
// 2. Forward 2 (unmoved only)
// 3. Diagonal left
// 4. Diagonal right
// (en passant still counts as a diagonal)
#define NUM_PAWN_MAX_MOVE_OPTIONS 4

#define NUM_ROOK_MAX_MOVE_OPTIONS ((NUM_BOARD_SIDE_TILES-1)*2)

#define NUM_KNIGHT_MAX_MOVE_OPTIONS 8

#if NUM_BOARD_SIDE_TILES & 1
#define NUM_BISHOP_MAX_MOVE_OPTIONS ((NUM_BOARD_SIDE_TILES-1)*2)
#else
#define NUM_BISHOP_MAX_MOVE_OPTIONS (((NUM_BOARD_SIDE_TILES-1)*2)-1)
#endif

#define NUM_QUEEN_MAX_MOVE_OPTIONS (NUM_ROOK_MAX_MOVE_OPTIONS+NUM_BISHOP_MAX_MOVE_OPTIONS)

// All 8 directions.
// In order for the king to castle, he must have his back to the wall; meaning he still cannot make more than 8 moves.
#define NUM_KING_MAX_MOVE_OPTIONS 8

#define NUM_MAX_MOVE_OPTIONS NUM_QUEEN_MAX_MOVE_OPTIONS

#define NUM_MAX_UNITS (NUM_BOARD_SIDE_TILES*4)

#pragma endregion

#endif // !CONSTANTS_H