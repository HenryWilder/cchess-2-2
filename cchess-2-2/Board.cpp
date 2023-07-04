#include <string>
#include "Board.h"
#include "Unit.h"

#define CURSOR_TO_POSITION(x,y) "\x1b[" #x ";" #y "f"

constexpr const char* cursorRestore = "\x1b[u";

void RestoreCursor()
{
    std::cout << cursorRestore;
}
void MoveCursorTo(int x, int y)
{
    std::cout << "\x1b[" << x << ";" << y << "f";
}
void MoveCursorToZero()
{
    std::cout << "\x1b[0;0f";
}

UnitColor Board::CurrentTeam()
{
    return (UnitColor)IsEven(turn);
}

UnitColor Board::OpponentTeam()
{
    return (UnitColor)IsEven(turn);
}

Unit* Board::GetTeamUnitAtPos(Coord pos, UnitColor team)
{
    const std::vector<Unit*>& teamArray = GetTeamArrayReadOnly(team);

    // Look at all black units
    for (Unit* checkUnit : teamArray)
    {
        bool isPositionMatching = checkUnit->GetLocation() == pos;

        if (isPositionMatching)
        {
            return checkUnit;
        }
    }

    return nullptr;
}

Unit* Board::GetUnitAtPos(Coord pos)
{
    Unit* out = GetTeamUnitAtPos(pos, UnitColor::Black);
    return (out != nullptr) ? out : GetTeamUnitAtPos(pos, UnitColor::White);
}

bool Board::IsTeamAtPos(Coord pos, UnitColor team)
{
    const std::vector<Unit*>& teamArray = GetTeamArrayReadOnly(team);

    for (const Unit* checkUnit : teamArray)
    {
        if (checkUnit->GetLocation() == pos)
        {
            return true;
            break;
        }
    }

    return false;
}

bool Board::IsUnitAtPos(Coord pos)
{
    return IsTeamAtPos(pos, UnitColor::Black) || IsTeamAtPos(pos, UnitColor::White);
}

void Board::ResetBoard()
{
    this->turn = 0;

    unsigned char unitID = 0;

    // Black units

    for (Unit* unit : blackUnits)
    {
        delete unit;
    }
    blackUnits.clear();

    // Construct
    for (int x = 0; x < width; ++x)
    {
        ConstructNewUnit({ x,1 }, Piece::Pawn, UnitColor::Black, unitID);
    }

    BuildRoyalty(0, UnitColor::Black, unitID);

    // White units

    for (Unit* unit : whiteUnits)
    {
        delete unit;
    }
    whiteUnits.clear();

    // Construct
    for (int x = 0; x < width; ++x)
    {
        ConstructNewUnit({ x,height - 2 }, Piece::Pawn, UnitColor::White, unitID);
    }

    BuildRoyalty(height - 1, UnitColor::White, unitID);

    PrintBoard();
}

void Board::DrawBoardSpaceColored(Coord pos, COLORREF color, bool effect)
{
    Unit* unit = GetUnitAtPos(pos); // Find the unit at the space

    if ((unit != nullptr) && (!unit->IsHidden()))
    {
        frameBuffer::DrawSpriteWithBackgroundNOW(pos, unit->GetSpritePointer(), bool(unit->GetColor()), color, effect);
    }
    else frameBuffer::DrawGridSpaceNOW(pos, color);
}

void Board::DrawBoardSpaceColored(Coord pos, Color color, bool effect)
{
    DrawBoardSpaceColored(pos, CRef(color), effect);
}

void Board::DrawBoardSpaceReset(Coord pos)
{
    // Draws the space with the background color being the color of the space
    DrawBoardSpaceColored(pos, frameBuffer::SpacePatternAtPos(pos));
}

//
//
// GAMEPLAY
//
//

Coord Board::WaitForClick(Phase turnPhase, const PieceMoves* pMoves, const sprite::Sprite* sprite, bool team)
{
    InitInput();

    Coord prevMouseCoord = { 0,0 };
    Coord currMouseCoord = { 0,0 };

    COLORREF prevSpaceColor = frameBuffer::Get(PixelSpace(prevMouseCoord));

    while (true)
    {
        PingInput(); // Update the mouse location

        currMouseCoord = g_mouse.ReadMouseHover();

        bool isMouseCoordChanged = prevMouseCoord != prevMouseCoord;

        if (isMouseCoordChanged)
        {
            bool isPrevMouseCoordValid = ValidPos(prevMouseCoord);
            bool isCurrMouseCoordValid = ValidPos(currMouseCoord);

            // Previously hovered space is dirty
            if (isPrevMouseCoordValid)
            {
                // Reset the old space's color
                DrawBoardSpaceColored(prevMouseCoord, prevSpaceColor);
            }

            // Update the temporary mouse position variable
            prevMouseCoord = currMouseCoord;

            // Currently hovering a space that needs to be rendered
            if (isCurrMouseCoordValid)
            {
                // Store the color of the new space before we recolor it
                prevSpaceColor = frameBuffer::Get(PixelSpace(currMouseCoord));

                bool isMovePhase = (turnPhase == Phase::Move);
                bool isHoveredMoveValid = (pMoves != nullptr) && (pMoves->MoveIsValid(currMouseCoord));

                if (isMovePhase && isHoveredMoveValid)
                {
                    // Draw transparent image of our piece at the move we are hovering over
                    frameBuffer::DrawSpriteWithBackgroundNOW(currMouseCoord, sprite, team, prevSpaceColor, true);
                }
                else
                {
                    // Color the new space
                    DrawBoardSpaceColored(currMouseCoord, RGB(127, 127, 255));
                }
            }
        }

        bool isMouseClicked = g_mouse.CheckMouseState();

        // Actual input and not just waiting
        if (isMouseClicked)
        {
            DrawBoardSpaceColored(currMouseCoord, prevSpaceColor); // Reset space color
            break;
        }
    }
    return g_mouse.GetMouseClickCoord();
}

void Board::MovePiece(Unit* unit, Coord moveTo)
{
    unit->Hide();
    //DrawBoardSpaceReset(unit->GetLocation()); // Sanity check

    Ghost unitGhost(
        unit->GetLocation(),
        unit->GetSpritePointer(),
        (bool)unit->GetColor());

    unitGhost.Glide(moveTo);

    Unit* enemyToTake = GetUnitAtPos(moveTo);

    if (enemyToTake != nullptr) // The piece will have already trimmed any positions which have a teammate in them
        RemoveUnit(enemyToTake);

    unit->Move(moveTo); // Move the piece before unhiding

    unit->UnHide();

    Pawn* pawn = dynamic_cast<Pawn*>(unit);

    if (pawn != nullptr) // Is a pawn
    {
        Coord passantPos = { moveTo.x, moveTo.y - pawn->GetForward() }; // Subtract because we are looking for the *other pawn's* direction
        Pawn* passantPawn = dynamic_cast<Pawn*>(GetUnitAtPos(passantPos));
        if (passantPawn != nullptr && passantPawn->GetColor() != pawn->GetColor() && passantPawn->en_pasant)
        {
            RemoveUnit(passantPawn);
            DrawBoardSpaceReset(passantPos);
        }

        if (unit->GetLocation().y == space::game::sideTileCount || unit->GetLocation().y == 0) // On the other side of the board
        {
            unsigned char id = unit->GetID();
            ConstructNewUnit(unit->GetLocation(), Piece::Queen, unit->GetColor(), id);
            RemoveUnit(unit);
        }
    }

    DrawBoardSpaceReset(moveTo); // Redraw the space we've moved to now that we're no longer hidden
}

void Board::DrawPossibleMoves(PieceMoves* moves, const UnitColor team)
{
    // Draw the available positions
    for (unsigned char i = 0; i < moves->numAvailableMoves; ++i)
    {
        Coord pMove = moves->available[i]; // The move we are currently looking at/drawing
        Unit* pEnemy = GetUnitAtPos(pMove); // The (potential) enemy at that space

        sprite::Pltt spaceColor = sprite::Pltt::Select_Available; // Default with selection color

        if (pEnemy != nullptr)
        {
            if (pEnemy->GetColor() != team) // Unit exists at the space and is an enemy
                spaceColor = sprite::Pltt::Select_TakePiece; // Change the color to "TakePiece"
            else
                spaceColor = sprite::Pltt::NoSelect_Teammate; // Change the color to "TakePiece"
        }

        DrawBoardSpaceColored(pMove, sprite::PaletteColor(spaceColor)); // Color the space
    }
}

void Board::UnDrawPossibleMoves(PieceMoves* moves)
{
    // Reset the potential positions
    for (unsigned char i = 0; i < moves->numAvailableMoves; ++i) {
        DrawBoardSpaceReset(moves->available[i]);
    }
}

bool Board::SelectPhase(const UnitColor team, Coord& input, Unit*& unit, PieceMoves* moves)
{
    //ClearTextLine(0);

    //std::cout << "Which piece would you like to move?\n";

    input = WaitForClick(Phase::Select);

    //ClearTextLine(1);

    if (input.x > width || input.y > height) // Out of bounds
    {
        //std::cout << "OUT OF BOUNDS";
        return false;
    }
    else
    {
        unit = GetUnitAtPos(input); 

        if (unit == nullptr) // No unit at selection
        {
            //std::cout << "That space is empty.";
            return false;
        }
        else if (unit->GetColor() != team) // Wrong team
        {
            //std::cout << "You are on team " << TEAM_NAME(team) << ".\n" << "Please choose a " << TEAM_NAME(team) << " piece.";
            return false;
        }
        else return true; // Unit exists & is correct team
    }
}
bool Board::HandleSelection(Coord input, Unit*& unit, PieceMoves* moves)
{
    unit->AvailableMoves(moves);

    if (moves->numAvailableMoves == 0)
    {
        return false;
    }
    else
    {
        // Draw the selection square
        DrawBoardSpaceColored(input, sprite::PaletteColor(sprite::Pltt::Select_Unit));

        // Draw all legal moves that can be made by this piece
        DrawPossibleMoves(moves, unit->GetColor());

        return true;
    }
}
int Board::MovePhase(Coord& input, Coord& output, Unit*& unit, PieceMoves* moves, const UnitColor team)
{
    output = WaitForClick(Phase::Move, moves, unit->GetSpritePointer(), (bool)team);

    if (output.x > width || output.y > height) // Out of bounds
    {
        return 0;
    }
    else
    {
        Unit* checkUnit = GetUnitAtPos(output);

        if (checkUnit != nullptr && checkUnit->GetColor() == team) // Change selection
        {
            DrawBoardSpaceReset(input);
            UnDrawPossibleMoves(moves);
            input = output;
            unit = checkUnit;
            return 2;
        }
        else if (!(moves->MoveIsValid(output))) // Not a legal move
        {
            return 0;
        }
        else return 1;
    }
}
bool Board::WrapUpTurn(Coord& input, Coord& output, Unit*& unit, PieceMoves* moves)
{
    UnDrawPossibleMoves(moves); // Clear the move highlighting

    DrawBoardSpaceReset(input); // Clear the old space

    MovePiece(unit, output); // Move the piece

    return true;
}

Unit* Board::FindKingFromTeam(UnitColor team)
{
    const std::vector<Unit*>& teamArray = GetTeamArray(team);

    // Find the king in the team array
    for (Unit* unit : teamArray) {
        if (unit->GetPieceType() == Piece::King) return unit;
    }

    return nullptr; // Defaults to current position
}

void Board::PlayBoard()
{
    const UnitColor team = CurrentTeam();
    Coord input; // User input for start position
    Coord output; // User input for end position
    Unit* unit = nullptr; // Unit at the user-input coorinates
    PieceMoves moves{}; // What moves can be made by the unit
    bool hasMoved = false;

    Phase turnPhase = Phase::Select;

    while (!hasMoved)
    {
        // State machine
        switch (turnPhase) {
        default: // Select
            if (SelectPhase(team, input, unit, &moves)) turnPhase = Phase::Move;
            else break; // Failed, retry

        case Phase::HandleSelect:
            if (HandleSelection(input, unit, &moves)) turnPhase = Phase::Move;
            else { // HandleSelect phase cannot reconsile on its own and must resort to retrying the Select phase.
                turnPhase = Phase::Select;
                break;
            }

        case Phase::Move:
            switch (MovePhase(input, output, unit, &moves, team))
            {
            default: // Failed (0)
                break;
            case 1: // Went well
                turnPhase = Phase::Wrapup;
                break;
            case 2: // Player changed their selection
                turnPhase = Phase::HandleSelect;
                break;
            }
            if (turnPhase != Phase::Wrapup) break; // We want to break out of the state machine if the return was unsuccessful

        case Phase::Wrapup:
            WrapUpTurn(input, output, unit, &moves);
            hasMoved = true;
            break;
        }
    }
}

void Board::PrintBoard()
{
    Coord space;
    // Cycle through all rows
    for (space.y = 0; space.y < space::game::sideTileCount; ++space.y)
    {
        // Cycle through all columns
        for (space.x = 0; space.x < space::game::sideTileCount; ++space.x)
        {
            DrawBoardSpaceReset(space);
        }
    }

    frameBuffer::Draw(); // Render the board
}

/*
* 
//
// MODIFIED NOVEMBER 28
// WAS NOT WORKING BEFORE, PROBABLY NOT WORKING STILL. HAS BEEN COMMENTED FOR CLARIFICATION.
//

// @Possible issue due to this not being in the .h file? but it gave errors when it WAS in there...
namespace Render
{
// This makes working with colors SOOO much easier
struct ConsoleColor
{
public: // Constructors

// Empty color
ConsoleColor()
{
char temp[21] = {
'\x1b', '[', '3', '8', ';', '2', ';', // Escape & color declairation
'0', '0', '0', ';', // Red (7-9)
'0', '0', '0', ';', // Green (11-13)
'0', '0', '0', ';', // Blue (15-17)
'm', '\0'
};

for (unsigned int i = 0; i < 21; ++i)
{
m_colorCode[i] = temp[i];
}
}

// Construct a color from RGB inputs
ConsoleColor(int r, int g, int b, bool b_isBackground = true)
{
ConsoleColor(); // Not sure if this is a bad way to do it...
Set(r, g, b); // I hope this is allowed
SetColorLayer(b_isBackground); // If the line above works then this should too
}

private:
// Color layout
char m_colorCode[21];

// Convert an input int value to a char[3] and apply it to the appropriate color component
// This function is private to keep it from being used by outside functions that might not know the correct startIndex values.
// It should only be used internally by the ConsoleColor type.
void SetRGBComp(int value, int startIndex)
{
m_colorCode[startIndex] = '0' + ((value / 100) % 10);
m_colorCode[startIndex + 1] = '0' + ((value / 10) % 10);
m_colorCode[startIndex + 2] = '0' + value % 10;
}

public:
// Changes whether this is a background color or a foreground color
void SetColorLayer(bool b_isBackground)
{
m_colorCode[2] = (b_isBackground ? '4' : '3');
}

// Convert the color to background
void BG()
{
SetColorLayer(1);
}

// Convert the color to foreground
void FG()
{
SetColorLayer(0);
}

// Set the color
void Set(int r, int g, int b)
{
SetRGBComp(r, 7);
SetRGBComp(g, 11);
SetRGBComp(b, 15);
}

// Return the charset
const char* Get()
{
return reinterpret_cast<const char*>(&m_colorCode);
}

// Apply the color to the console
void Apply()
{
std::cout << Get();
}
};

// Reset colors
const char* BG_RESET = "\x1b[49;0m";
const char* FG_RESET = "\x1b[39;0m";

// Resets both the foreground & background color at once
void ResetColor()
{
std::cout << "\x1b[49;0m\x1b[39;0m";
}

// Custom colors
ConsoleColor BG_BLACK = ConsoleColor(20, 20, 20); // Board space
ConsoleColor FG_BLACK = ConsoleColor(236, 167, 95, false); // Game piece

ConsoleColor BG_WHITE = ConsoleColor(256, 256, 256); // Board space
ConsoleColor FG_WHITE = ConsoleColor(252, 219, 166, false); // Game piece

// Space/piece selection colors
ConsoleColor BG_SELECT = ConsoleColor(44, 200, 37);
ConsoleColor FG_SELECT = ConsoleColor(155, 235, 135, false); 

// Edge coordinate text color
ConsoleColor FG_COORD = ConsoleColor(100, 100, 100, false);
}

using namespace Render; // We're about to use this namespace a LOT


void Board::PrintBoard() // @TODO: Something is severely wrong with this function, as nothing is being rendered. I'm not sure what the issue is though.
{
// Cycle through all rows
for (int y = 0; y < height; ++y)
{
// Cycle through all columns
for (int x = 0; x < width; ++x)
{
Unit* found = GetUnitAtPos({ x,y }); // Does exactly as the name implies

ResetColor(); // @TODO: Fixes a weird bug that happens sometimes. Something to look in to.

((((x + y) % 2) == 0) ? BG_WHITE : BG_BLACK).Apply(); // Space coloration

std::cout << " "; // Empty space for cursor

{
char unitSymbol = ' '; // Defaults as empty until overwritten

// Find any pieces occupying the space
if (found != nullptr) // "If there is a piece here"
{
(bool(found->GetColor()) ? FG_WHITE : FG_BLACK).Apply(); // Set space foreground to match unit color

unitSymbol = found->GetSymbol(); // Overwrite the empty space with the unit symbol
}

std::cout << unitSymbol; // Draws whatever unit (or lack of a unit) is in the space
}
}

ResetColor(); // @TODO: Again, we should really look into why this is needed

FG_COORD.Apply(); // Coord text coloration

std::cout << " " << height - y << '\n'; // Print y-coord and newline
}

ResetColor(); // @TODO: omfg this is upsetting

FG_COORD.Apply(); // Coord text coloration

// At this point we are below the bottom of the board, so we create a new loop for the x-coordinates
for (int x = 0; x < width; ++x)
{
std::cout << " " << NumToLetter(x) << " "; // Print x-coord
}

ResetColor(); // Ok this one is actually on purpose. At this point we've reached the end of the chessboard and we want the user input to be the regular colors.

std::cout << '\n'; // Go to the next line (to make it look nice when the player is promted for input)
}
*/
//
// End of November 28 modification & clarification.
//
//

std::vector<Unit*>& Board::GetTeamArray(UnitColor team)
{
    return (team == UnitColor::Black) ? blackUnits : whiteUnits;
}

const std::vector<Unit*>& Board::GetTeamArrayReadOnly(UnitColor team) const
{
    return (team == UnitColor::Black) ? blackUnits : whiteUnits;
}

void Board::ConstructNewUnit(Coord pos, Piece type, UnitColor color, unsigned char& unitID)
{
    Unit* newUnit;
    switch (type)
    {
    default:
    case Piece::Pawn:
        newUnit = new Pawn();
        break;

    case Piece::Knight:
        newUnit = new Knight();
        break;

    case Piece::Rook:
        newUnit = new Rook();
        break;

    case Piece::Bishop:
        newUnit = new Bishop();
        break;

    case Piece::Queen:
        newUnit = new Queen();
        break;

    case Piece::King:
        newUnit = new King();
        break;
    }
    newUnit->Init(pos, color, this, unitID++);
    AddUnit(newUnit);
}

void Board::BuildRoyalty(int y, UnitColor col, unsigned char& unitID)
{
    constexpr Piece order[width] = {
        Piece::Rook,
        Piece::Knight,
        Piece::Bishop,
        Piece::Queen,
        Piece::King,
        Piece::Bishop,
        Piece::Knight,
        Piece::Rook,
    };

    Coord coord(0, y);
    for (int x = 0; x < width; ++x)
    {
        coord.x = x;
        ConstructNewUnit(coord, order[x], col, unitID); // Increments unitID
    }
}

void Board::AddUnit(Unit* unit)
{
    GetTeamArray(unit->GetColor()).push_back(unit);
}

void Board::RemoveUnit(Unit* unit)
{
    unsigned char id = unit->GetID();

    unsigned int i = 0;

    Coord unitSpace = unit->GetLocation(); // For resetting the space after we've destroyed the unit

    std::vector<Unit*>& teamArray = GetTeamArray(unit->GetColor());

    for (i; i < teamArray.size(); ++i)
        if (teamArray[i]->GetID() == id)
            break;

    teamArray.erase(teamArray.begin() + i);

    DrawBoardSpaceReset(unitSpace);
}

void Board::ResetEnPasant()
{
    std::vector<Unit*>& teamArray = GetTeamArray(CurrentTeam());

    for (Unit* unit : teamArray)
    {
        Pawn* pawn = dynamic_cast<Pawn*>(unit);
        if (pawn != nullptr && pawn->en_pasant)
        {
            pawn->en_pasant = false;
            break; // Only one pawn can have moved in a turn
        }
    }
}

void Board::StoreBoardState()
{
    Coord coord;
    for (coord.y = 0; coord.y < space::game::sideTileCount; ++coord.y) {
        for (coord.x = 0; coord.x < space::game::sideTileCount; ++coord.x)
        {
            Unit* unit = GetUnitAtPos(coord);
            m_history[turn][coord] = MakeUnitData(unit);
        }
    }
}

bool Board::IncrementTurn()
{
    King* king = dynamic_cast<King*>(FindKingFromTeam(CurrentTeam()));

    if (king == nullptr) // Game over
    {
        return true;
    }
    else
    {
        if (!king->SpaceIsSafeFromCheck()) DrawBoardSpaceColored(king->GetLocation(), RGB(255, 80, 80)); // King in check
        else  DrawBoardSpaceReset(king->GetLocation()); // King not in check

        StoreBoardState();

        ++turn;

        // Start the next turn

        ResetEnPasant(); 

        king = dynamic_cast<King*>(FindKingFromTeam(CurrentTeam()));

        if (king == nullptr) // Game over
        {
            return true;
        }
        else
        {
            if (!king->SpaceIsSafeFromCheck()) DrawBoardSpaceColored(king->GetLocation(), RGB(255, 80, 80)); // King in check
            else  DrawBoardSpaceReset(king->GetLocation()); // King not in check
            return false; // Game is not over
        }
    }
}

UnitData BoardStateMemory::operator[](Coord coord) const
{
    return m_stateData[coord.y][coord.x];
}
UnitData& BoardStateMemory::operator[](Coord coord)
{
    return m_stateData[coord.y][coord.x];
}

void Board::DrawBoardState(int state)
{
    system("CLS");
    std::cout << "\x1b[?25l"; // Hide the cursor

    BoardStateMemory& gameState = m_history[state];

    for (int y = 0; y < space::game::sideTileCount; ++y) {
        for (int x = 0; x < space::game::sideTileCount; ++x)
        {
            Coord space = { x, y };
            UnitData data = gameState[space];
            if (data.piece == Piece::Null)
            {
                frameBuffer::DrawBoardPattern1SpaceNOW(space);
                return;
            }

            if (data.piece != Piece::Null)
            {
                const sprite::Sprite* sprite = sprite::unit::all[(size_t)data.piece];
                frameBuffer::DrawSpriteWithBackgroundNOW(space, sprite, (bool)data.color, frameBuffer::SpacePatternAtPos(space));
            }
        }
    }
}

int Board::FlipbookWFClick(int state)
{
    // Initialization
    Coord arrowPosR;
    arrowPosR.x = space::game::sideTileCount / 2;
    arrowPosR.y = space::game::sideTileCount + 1;
    Coord arrowPosL = arrowPosR;
    arrowPosL.x -= 1;

    bool b_lArrow = false;
    bool b_rArrow = false;

    if (state > 0)
    {
        b_lArrow = true;
        frameBuffer::DrawSymbolSkippingBuffer(arrowPosL, '<', 0);
    }
    if (state < this->turn - 1)
    {
        b_rArrow = true;
        frameBuffer::DrawSymbolSkippingBuffer(arrowPosR, '>', 0);
    }

    InitInput();

    Coord mouseCoordLast = { 0,0 };
    Coord mouseCoordCurrent = { 0,0 };

    while (true)
    {
        PingInput(); // Update the mouse location

        mouseCoordCurrent = g_mouse.ReadMouseHover();

        if (mouseCoordLast != mouseCoordCurrent) // If the mouse location has changed
        {
            // Draw transparent image of our piece at the move we are hovering over
            if (b_lArrow)
            {
                if (mouseCoordCurrent == arrowPosL) frameBuffer::DrawSymbolSkippingBuffer(arrowPosL, '<', 1);
                if (mouseCoordLast == arrowPosL) frameBuffer::DrawSymbolSkippingBuffer(arrowPosL, '<', 0);
            }
            if (b_rArrow)
            {
                if (mouseCoordCurrent == arrowPosR) frameBuffer::DrawSymbolSkippingBuffer(arrowPosR, '>', 1);
                if (mouseCoordLast == arrowPosR) frameBuffer::DrawSymbolSkippingBuffer(arrowPosR, '>', 0);
            }
            mouseCoordLast = mouseCoordCurrent; // Update the temporary mouse position variable
        }

        if (g_mouse.CheckMouseState()) break; // Click is true
    }
    // Click on button confirmed
    Coord whereClicked = g_mouse.GetMouseClickCoord();
    if (whereClicked == arrowPosL) return -1;
    else if (whereClicked == arrowPosR) return 1;
    else return 0;
}

void Board::GameFlipbook()
{
    int state = 0;
    while (true)
    {
        DrawBoardState(state);

        int update = 0;

        while (update == 0 && ((state + update) >= 0) && ((state + update) <= turn)) {
            update = FlipbookWFClick(state);
        }
        state += update;
    }
}

UnitData MakeUnitData(Unit* unit)
{
    UnitData result;

    if (unit != nullptr)
    {
        result.color = unit->GetColor();
        result.piece = unit->GetPieceType();
    }
    else
    {
        result.color = UnitColor(0);
        result.piece = Piece::Null;
    }

    return result;
}
