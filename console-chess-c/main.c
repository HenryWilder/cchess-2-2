#include <Windows.h>
#include "constants.h"
#include "unit.h"
#include "board.h"
#include <stdio.h>

extern HDC hdc;

int main()
{
	SetConsoleTitleA("Console Chess C");
	printf("\x1b[?25l"); // Hide cursor
	system("CLS");

	_Bool replay = 1;

	HWND window = GetConsoleWindow();
	hdc = GetDC(window);

#if _DEBUG

	// Faux game for testing gameplay without input

	ResetBoard();

	PrintBoardDebug();

	typedef struct FauxMove { BoardPos from, to; } FauxMove;

	FauxMove fauxMoves[1] = {
		{
			.from = { .x = 6, .y = 6, },
			.to   = { .x = 5, .y = 5, },
		}
	};

	for (size_t i = 0; i < sizeof(fauxMoves) / sizeof(FauxMove); ++i)
	{
		PushMove(fauxMoves[i].from, fauxMoves[i].to);
		ApplyCurrentMove();
		PrintBoardDebug();
	}

#endif

	// Program loop
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
