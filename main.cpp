#include "Game.h"

int main()
{
	Game game = Game();

	bool success = game.init();
	if (!success)
	{
		std::cout << "Failed to load the game\n";
		return -1;
	}
	game.gameLoop();
	game.terminate();

	return 0;
}
