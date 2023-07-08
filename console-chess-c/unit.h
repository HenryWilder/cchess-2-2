#ifndef UNIT_H
#define UNIT_H
#include <sal.h>
#include "constants.h"

// Uses 3 bits
typedef enum UnitType {
    UNIT_NONE = 0,
    UNIT_PAWN = 1,
    UNIT_ROOK = 2,
    UNIT_KNIGHT = 3,
    UNIT_BISHOP = 4,
    UNIT_QUEEN = 5,
    UNIT_KING = 6,
} UnitType;

// Uses 1 bit
typedef enum UnitTeam {
    TEAM_WHITE = 0,
    TEAM_BLACK = 1,
} UnitTeam;

typedef struct BoardPos {
    int x, y;
} BoardPos;

typedef struct Unit {
    BoardPos position;
    UnitType type;
    UnitTeam team;
    _Bool isMoved;
} Unit, *UnitPtr;

Unit InitUnit(int x, int y, UnitType type, UnitTeam team);
void ReInitUnit(_Inout_ UnitPtr unit, int x, int y, UnitType type, UnitTeam team);

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

unsigned int MoveOptionsPawn(
    _Out_writes_to_(NUM_PAWN_MAX_MOVE_OPTIONS, return) BoardPos options[],
    _In_ _Pre_satisfies_(_Curr_->type == UNIT_PAWN) const Unit* unit);

unsigned int MoveOptionsRook(
    _Out_writes_to_(NUM_ROOK_MAX_MOVE_OPTIONS, return) BoardPos options[],
    _In_ _Pre_satisfies_(_Curr_->type == UNIT_ROOK) const Unit* unit);

unsigned int MoveOptionsKnight(
    _Out_writes_to_(NUM_KNIGHT_MAX_MOVE_OPTIONS, return) BoardPos options[],
    _In_ _Pre_satisfies_(_Curr_->type == UNIT_KNIGHT) const Unit* unit);

unsigned int MoveOptionsBishop(
    _Out_writes_to_(NUM_BISHOP_MAX_MOVE_OPTIONS, return) BoardPos options[],
    _In_ _Pre_satisfies_(_Curr_->type == UNIT_BISHOP) const Unit* unit);

unsigned int MoveOptionsQueen(
    _Out_writes_to_(NUM_QUEEN_MAX_MOVE_OPTIONS, return) BoardPos options[],
    _In_ _Pre_satisfies_(_Curr_->type == UNIT_QUEEN) const Unit* unit);

unsigned int MoveOptionsKing(
    _Out_writes_to_(NUM_KING_MAX_MOVE_OPTIONS, return) BoardPos options[],
    _In_ _Pre_satisfies_(_Curr_->type == UNIT_KING) const Unit* unit);

unsigned int MoveOptions(
    _Out_writes_to_(NUM_MAX_MOVE_OPTIONS, return) BoardPos options[],
    _In_ const Unit* unit);

#endif // !UNIT_H