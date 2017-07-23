#include "GameManager.h"

GameManager::GameManager()
{
	srand(time(NULL));

	m_Window = NULL;
	m_Renderer = NULL;
	if(!InitSDL())
		m_bQuit = true;
	else
	{
		m_bQuit = false;

		Create();

		m_CurrentState = INTRO;
		m_Intro->Render(false);
	}
}

GameManager::~GameManager()
{
	delete m_Intro;
	delete m_Game;
	delete m_Win;
	delete m_BonusGame;
	delete m_Outro;

	m_Intro = NULL;
	m_Game = NULL;
	m_Win = NULL;
	m_BonusGame = NULL;
	m_Outro = NULL;

	SDL_DestroyRenderer(m_Renderer);
	SDL_DestroyWindow(m_Window);
	m_Renderer = NULL;
	m_Window = NULL;

	IMG_Quit();
	TTF_Quit();
	Mix_Quit();
	SDL_Quit();
}

void GameManager::EventHandler(SDL_Event& e)
{
	if( e.type == SDL_QUIT )
	{
		m_bQuit = true;
		// TODO Recovery
	}
	else
	{
		switch(m_CurrentState)
		{
		case INTRO:
			m_Intro->EventHandler(e);
			break;

		case GAME:
			m_Game->EventHandler(e);
			break;

		case WIN:
			m_Win->EventHandler(e);
			break;

		case BONUSGAME:
			m_BonusGame->EventHandler(e);
			break;

		case OUTRO:
			m_Outro->EventHandler(e);
			break;
		}
	}
}

bool GameManager::GetQuit() const
{
	return m_bQuit;
}

void GameManager::Render()
{
	switch(m_CurrentState)
	{
	case INTRO:
		RenderIntro();
		break;

	case GAME:
		RenderGame();
		break;

	case WIN:
		RenderWin();
		break;

	case BONUSGAME:
		RenderBonusGame();
		break;

	case OUTRO:
		RenderOutro();
		break;
	}

	SDL_RenderPresent(m_Renderer);
}

bool GameManager::InitSDL()
{
	bool bSuccess = true;

	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
	{
		std::cerr << "Couldn't initialize SDL! Error: " << SDL_GetError() << "\n";
		bSuccess = false;
	}
	else
	{
		if(!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
			std::cerr << "Warning: Linear texture filtering not enabled!\n";

		m_Window = SDL_CreateWindow("Sunny Beach Holiday", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, g_ScreenWidth, g_ScreenHeight, SDL_WINDOW_SHOWN);
		if(m_Window == NULL)
		{
			std::cerr << "Couldn't create window! Error: " << SDL_GetError() << "\n";
			bSuccess = false;
		}
		else
		{
			m_Renderer = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if(m_Renderer == NULL)
			{
				std::cerr << "Renderer could not be created! SDL Error: " <<  SDL_GetError() << "\n";
				bSuccess = false;
			}
			else
			{
				if(TTF_Init() == -1)
				{
					std::cerr << "SDL_ttf could not initialize! SDL_ttf Error: " << TTF_GetError() << "\n";
					bSuccess = false;
				}

				int iFormatFlags = IMG_INIT_PNG;
				if(!(IMG_Init(iFormatFlags) & iFormatFlags))
				{
					std::cerr << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << "\n";
					bSuccess = false;
				}

				if( Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
				{
					std::cerr << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << "\n";
					bSuccess = false;
				}
			}
		}
	}

	return bSuccess;
}

void GameManager::Create()
{
	m_Intro = new Intro(m_Renderer);
	m_Game = new Game(m_Renderer);
	m_Win = new Win(m_Renderer);
	m_BonusGame = new BonusGame(m_Renderer);
	m_Outro = new Outro(m_Renderer);
}

void GameManager::RenderIntro()
{
	if(m_Intro->GetSwitch())
	{
		m_Intro->ResetSwitch();

		if(m_Intro->GetCredits() > 0)
		{
			m_Game->SetCredits(m_Intro->GetCredits());

			m_CurrentState = GAME;

			m_Game->Clear();
			m_Game->PrepTransitionIn();
			m_Game->Render(false);
		}
	}
	else
		m_Intro->Render(true);
}

void GameManager::RenderGame()
{
	if(m_Game->GetSwitch())
	{
		m_Game->ResetSwitch();

		if(m_Game->GetWin())
		{
			m_Game->ResetWin();

			m_Win->SetCredits(m_Game->GetPaid());

			m_Game->Render(true);

			m_CurrentState = WIN;

			m_Win->PrepTransitionIn();
			m_Win->Render(false);
		}
		else if(m_Game->GetBonus())
		{
			m_Game->ResetBonus();

			m_BonusGame->ResetGame();

			m_BonusGame->SetCredits(m_Game->GetTotalBet());

			m_Game->Render(true);

			m_CurrentState = BONUSGAME;

			m_BonusGame->PrepTransitionIn();
			m_BonusGame->Render(false);
		}
		else if(m_Game->GetCashOut())
		{
			m_Game->ResetCashOut();

			m_Outro->SetCredits(m_Game->GetCredits());

			m_Game->Render(true);

			m_CurrentState = OUTRO;

			m_Outro->PrepTransitionIn();
			m_Outro->Render(false);
		}
		else
		{
			m_CurrentState = INTRO;

			m_Intro->PrepTransitionIn();
			m_Intro->Render(false);
		}
	}
	else
		m_Game->Render(true);
}

void GameManager::RenderWin()
{
	if(m_Win->GetSwitch())
	{
		m_Win->ResetSwitch();

		m_CurrentState = GAME;
		m_Game->Render(false);
	}
	else
	{
		m_Game->Render(false);
		m_Win->Render(true);
	}
}

void GameManager::RenderBonusGame()
{
	if(m_BonusGame->GetSwitch())
	{
		m_BonusGame->ResetSwitch();

		m_CurrentState = GAME;
		m_Game->CalcWinning(m_BonusGame->GetCredits());
		m_Game->Render(false);
	}
	else
	{
		m_Game->Render(false);
		m_BonusGame->Render(true);
	}
}

void GameManager::RenderOutro()
{
	if(m_Outro->GetSwitch())
	{
		m_Outro->ResetSwitch();

		m_CurrentState = INTRO;
		m_Intro->Render(false);
	}
	else
	{
		m_Game->Render(false);
		m_Outro->Render(true);
	}
}





























