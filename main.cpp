#include "GameManager.h"

int main(int argc, char* args[])
{
	GameManager game;

	SDL_Event e;

	while(!game.GetQuit())
	{
		while(SDL_PollEvent(&e) != 0)
		{
			game.EventHandler(e);
		}

		game.Render();
	}

	return 0;
}
