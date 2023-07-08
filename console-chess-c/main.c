#include <stdio.h>
#include <Windows.h>
#include "constants.h"
#include "unit.h"
#include "board.h"

extern HDC hdc;

int main()
{
	SetConsoleTitleA("Console Chess C");
	printf("\x1b[?25l"); // Hide cursor
	system("CLS");

	_Bool replay = 1;

	HWND window = GetConsoleWindow();
	hdc = GetDC(window);

	Unit unit = InitUnit(0,0, UNIT_PAWN, TEAM_BLACK);

	BoardPos movesP[NUM_PAWN_MAX_MOVE_OPTIONS];
	BoardPos movesR[NUM_ROOK_MAX_MOVE_OPTIONS];
	MoveOptionsPawn(movesP, &unit);
	MoveOptionsRook(movesR, &unit);

	while (replay)
	{
		ResetBoard();

		_Bool gameOver = 0;

		// Game loop
		while (!gameOver)
		{
			PlayBoard();
			gameOver = IncrementTurn();
		}

		GameFlipbook();
	}

    ReleaseDC(window, hdc);

    return 0;
}
