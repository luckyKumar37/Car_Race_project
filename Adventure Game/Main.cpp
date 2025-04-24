#include "game.h"

int main()
{
	game Game;

	// main game loop
	while (Game.iswindowopen())
	{
		Game.Update();

		Game.Render();
	}

	return 0;
}