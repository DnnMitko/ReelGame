#include "Game.h"

Game::Game() : State()
{
	m_TextureBackground = NULL;

	m_bIsSpinning = false;

	m_bWin = false;
	m_bBonus = false;
	m_bCashOut = false;

	m_Panel = NULL;
	m_Reel = NULL;
	m_Lines = NULL;
}

Game::Game(SDL_Renderer* newRenderer) : State(newRenderer)
{
	m_bIsSpinning = false;

	m_bWin = false;
	m_bBonus = false;
	m_bCashOut = false;

	m_TextureBackground = IMG_LoadTexture(m_Renderer, g_GameBackground);
	if(m_TextureBackground == NULL)
		std::cerr << "Failed to load TextureBackground! SDL Error: " << IMG_GetError() << std::endl;

	m_Panel = new GamePanel(m_Renderer);

	m_Reel = new Reel(m_Renderer);

	m_Lines = new Lines();
}

Game::~Game()
{
	delete m_Panel;
	m_Panel = NULL;

	delete m_Reel;
	m_Reel = NULL;

	delete m_Lines;
	m_Lines = NULL;

	SDL_DestroyTexture(m_TextureBackground);
	m_TextureBackground = NULL;
}

void Game::Render(bool UpdateOnly)
{
	if(!m_Renderer || !m_TextureBackground)
		return;

	if(m_Panel->InTransition() || m_Reel->InTransition() || !m_Reel->HasStopped())
		UpdateOnly = false;

	if(!UpdateOnly)
		SDL_RenderCopy(m_Renderer, m_TextureBackground, NULL, NULL);

	m_Reel->Render(UpdateOnly);
	m_Panel->Render(UpdateOnly);

	if(m_bIsSpinning && m_Reel->HasStopped())
	{
		m_bIsSpinning = false;

		m_Lines->SetResult(m_Reel->GetResult(), m_Panel->GetLines());

		if(m_Lines->HasSpecial())
		{
			m_bBonus = true;
			m_bSwitch = true;
		}
		else
		{
			m_Panel->CalcWinning(m_Lines->GetTotalWin()  * m_Panel->GetBet());

			if(m_Lines->GetTotalWin() != 0)
			{
				m_bWin = true;
				m_bSwitch = true;
			}

			if(m_Lines->GetTotalWin() == 0 && m_Panel->GetCredits() == 0)
			{
				SDL_Delay(g_GameLoseDelay);
				m_bTransitionOut = true;

				m_Panel->Hide();
				m_Reel->Hide();
			}
		}

		m_Reel->Animate(m_Lines->GetAnimate());
	}

	if(!m_Panel->InTransition() && !m_Reel->InTransition())
	{
		m_bTransitionIn = false;

		if(m_bTransitionOut)
		{
			m_bTransitionOut = false;
			m_bSwitch = true;
		}
	}
}

void Game::EventHandler(SDL_Event& e)
{
	if(m_Panel->InTransition() || m_Reel->InTransition() || m_bIsSpinning)
		return;

	bool bPlay = false;
	bool bCashOut = false;
	m_Panel->EventHandler(e, bPlay, bCashOut);

	if(bPlay)
	{
		m_bIsSpinning = true;
		m_Reel->Spin();
	}
	else if(bCashOut)
	{
		m_bCashOut = true;
		m_bTransitionOut = true;

		m_Panel->Hide();
		m_Reel->Hide();
	}
}

void Game::PrepTransitionIn()
{
	m_bTransitionIn = true;

	m_Reel->PrepTransitionIn();
	m_Panel->PrepTransitionIn();
}

void Game::SetCredits(unsigned int newCredits)
{
	m_Panel->SetCredits(newCredits);
}

unsigned int Game::GetCredits() const
{
	return m_Panel->GetCredits();
}

unsigned int Game::GetPaid() const
{
	return m_Panel->GetPaid();
}

unsigned int Game::GetTotalBet() const
{
	return m_Panel->GetTotalBet();
}

void Game::CalcWinning(unsigned int Paid)
{
	m_Panel->CalcWinning(Paid);
}

bool Game::GetWin() const
{
	return m_bWin;
}

void Game::ResetWin()
{
	m_bWin = false;
}

bool Game::GetBonus() const
{
	return m_bBonus;
}

void Game::ResetBonus()
{
	m_bBonus = false;
}

bool Game::GetCashOut() const
{
	return m_bCashOut;
}

void Game::ResetCashOut()
{
	m_bCashOut = false;
}

void Game::Clear()
{
	m_Panel->Clear();
}











