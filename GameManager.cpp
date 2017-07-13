#include "GameManager.h"

GameManager::GameManager()
{
	m_Window = NULL;
	m_Renderer = NULL;
	if(!Init())
		m_bQuit = true;
	else
	{
		m_bQuit = false;

		m_Intro = new Intro(m_Renderer);
		m_Intro->Render(false);
	}
}

GameManager::~GameManager()
{
	Close();
}

void GameManager::EventHandler(SDL_Event& e)
{
	if( e.type == SDL_QUIT )
	{
		m_bQuit = true;
		// TODO Recovery
	}
	else
		m_Intro->EventHandler(e);
	//else TODO
}

bool GameManager::GetQuit() const
{
	return m_bQuit;
}

void GameManager::Render()
{
	//TODO
	m_Intro->Render();

	SDL_RenderPresent(m_Renderer);
}

bool GameManager::Init()
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

void GameManager::Close()
{
	//TODO Destroy Game, BonusGame, Intro, Outro objects
	delete m_Intro;

	SDL_DestroyRenderer(m_Renderer);
	SDL_DestroyWindow(m_Window);

	m_Renderer = NULL;
	m_Window = NULL;

	IMG_Quit();
	TTF_Quit();
	Mix_Quit();
	SDL_Quit();
}











