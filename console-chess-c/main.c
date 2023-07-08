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
