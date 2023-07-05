#include "Utils.h"
#include "Input.h"
#include "Rendering.h"
#include "Board.h"
#include "Unit.h"

bool PromptReplay()
{
	std::cout << "Want to play again? (y/n) ";
	char input = 'y';
	std::cin >> input;
	return (input == 'y');
}

int main(void)
{
	// Rename the window
	std::cout << "\x1b]2;Console Chess 2.0\x07";

	// Hide the cursor
	std::cout << "\x1b[?25l";

	Board playSpace;


	// Reset the newlines
	std::system("CLS");

	bool replay = true;

	while (replay)
	{
		playSpace.ResetBoard();

		bool gameOver = false;

		// Game loop
		while (!gameOver)
		{
			playSpace.PlayBoard();
			gameOver = playSpace.IncrementTurn();
		}

		playSpace.GameFlipbook();

	}

	ReleaseDC(window, hdc);

	return 0;
}