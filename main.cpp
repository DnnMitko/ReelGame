#include "GameManager.h"

int main(int argc, char* args[])
{
	GameManager game;

	SDL_Event e;

	while(!game.getQuit())
	{
		while(SDL_PollEvent(&e) != 0)
		{
			game.eventHandler(e);
		}

		game.render();
	}

	return 0;
}
