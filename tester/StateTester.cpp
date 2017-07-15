#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <cstdio>
#include "Intro.h"
#include "Outro.h"
#include "Game.h"
#include "Win.h"

SDL_Window* m_Window;
SDL_Renderer* m_Renderer;

bool Init();
void Close();

int main(int argc, char* args[])
{
	if(!Init())
		return 1;

	//Intro* test = new Intro(m_Renderer);
	Game* test = new Game(m_Renderer);
	//Win* test = new Win(m_Renderer);
	//Outro* test = new Outro(m_Renderer);

	SDL_Event e;
	bool quit = false;

	test->SetCredits(1234567);

	test->Render(false);

	while(!quit)
	{
		while(SDL_PollEvent(&e) != 0)
		{
			if(e.type == SDL_QUIT)
				quit = true;
			else
				test->EventHandler(e);
		}

		test->Render();

		SDL_RenderPresent(m_Renderer);
	}

	delete test;
	Close();
	return 0;
}

bool Init()
{
	bool bSuccess = true;

	if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("Couldn't initialize SDL! Error: %s\n", SDL_GetError());
		bSuccess = false;
	}
	else
	{
		if(!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
			printf("Warning: Linear texture filtering not enabled!");

		m_Window = SDL_CreateWindow("Sunny Beach Holiday", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, g_ScreenWidth, g_ScreenHeight, SDL_WINDOW_SHOWN);
		if(m_Window == NULL)
		{
			printf("Couldn't create window! Error: %s\n", SDL_GetError());
			bSuccess = false;
		}
		else
		{
			m_Renderer = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if(m_Renderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				bSuccess = false;
			}
			else
			{
				if(TTF_Init() == -1)
				{
					printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
					bSuccess = false;
				}

				int iFormatFlags = IMG_INIT_PNG;
				if(!(IMG_Init(iFormatFlags) & iFormatFlags))
				{
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					bSuccess = false;
				}

				if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
				{
					printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
					bSuccess = false;
				}
			}
		}
	}

	return bSuccess;
}

void Close()
{
	//TODO Destroy Game, BonusGame, Intro, Outro objects

	SDL_DestroyRenderer(m_Renderer);
	SDL_DestroyWindow(m_Window);

	m_Renderer = NULL;
	m_Window = NULL;

	IMG_Quit();
	TTF_Quit();
	Mix_Quit();
	SDL_Quit();
}
