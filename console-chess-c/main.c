#include <Windows.h>
#include "input.h"
#include "constants.h"
#include "unit.h"
#include "board.h"
#include "output.h"
#include <stdio.h>

extern HDC hdc;

int main()
{
	SetConsoleTitleA("Console Chess C");
	printf("\x1b[?25l"); // Hide cursor
	system("CLS");

	_Bool replay = 1;

	inputHandle = GetStdHandle(STD_INPUT_HANDLE);
	SetConsoleMode(inputHandle, ENABLE_EXTENDED_FLAGS | ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT);

	HWND window = GetConsoleWindow();
	hdc = GetDC(window);

	InitBrushes();

#if _DEBUG && 0

	// Faux game for testing gameplay without input

	ResetBoard();

	PrintBoardDebug();

	typedef struct FauxMove { BoardPos from, to; } FauxMove;

	FauxMove fauxMoves[] = {
		{
			.from = { .x = 6, .y = 6, },
			.to   = { .x = 5, .y = 5, },
		},
		{
			.from = { .x = 5, .y = 5, },
			.to   = { .x = 5, .y = 1, },
		},
		{
			.from = { .x = 5, .y = 1, },
			.to   = { .x = 5, .y = 0, },
		},
		{
			.from = { .x = 5, .y = 0, },
			.to   = { .x = 5, .y = 4, },
		}
	};

	for (size_t i = 0; i < sizeof(fauxMoves) / sizeof(FauxMove); ++i)
	{
		PushMove(fauxMoves[i].from, fauxMoves[i].to);
		ApplyCurrentMove();
		IncrementTurn();
	}

	printf("REVERSING\n");

	for (size_t i = 0; i < sizeof(fauxMoves) / sizeof(FauxMove); ++i)
	{
		UnapplyCurrentMove();
		PrintBoardDebug();
		DecrementTurn();
	}

	return;

#endif

	// Program loop
	while (replay)
	{
		ResetBoard();

		_Bool gameOver = 0;

		// Game loop
		while (!gameOver)
		{
			RedrawBoard();
			PlayBoard();
			gameOver = IncrementTurn();
		}

		GameFlipbook();
	}

    ReleaseDC(window, hdc);

    return 0;
}
