#include "Game.h"

Game::Game() : State()
{
	m_TextureBackground = NULL;

	m_TexturePayTable = NULL;
	m_bShowPayTable = false;

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
	m_bShowPayTable = false;
	m_bIsSpinning = false;

	m_bWin = false;
	m_bBonus = false;
	m_bCashOut = false;

	m_TextureBackground = IMG_LoadTexture(m_Renderer, g_GameBackground);
	if(m_TextureBackground == NULL)
		std::cerr << "Failed to load TextureBackground! SDL Error: " << IMG_GetError() << std::endl;

	m_TexturePayTable = IMG_LoadTexture(newRenderer, g_GamePayTable);
	if(m_TexturePayTable == NULL)
		std::cerr << "Couldn't load PayTable! SDL Error: " << IMG_GetError() << std::endl;

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

	SDL_DestroyTexture(m_TexturePayTable);
	m_TexturePayTable = NULL;
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

	if(m_bShowPayTable)
	{
		SDL_Rect tempRect;
		tempRect.x = (g_ScreenWidth - g_GamePayTableWindowWidth) / 2;
		tempRect.y = (g_ScreenHeight - g_GamePayTableWindowHeight) / 2;
		tempRect.w = g_GamePayTableWindowWidth;
		tempRect.h = g_GamePayTableWindowHeight;

		SDL_RenderCopy(m_Renderer, m_TexturePayTable, NULL, &tempRect);
		SDL_RenderDrawRect(m_Renderer, &tempRect);
	}

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

	bool bShowPayTable = false;
	bool bPlay = false;
	bool bCashOut = false;
	m_Panel->EventHandler(e, bShowPayTable, bPlay, bCashOut);

	if(m_bShowPayTable != bShowPayTable)
	{
		m_bShowPayTable = bShowPayTable;
		Render(false);
	}

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
	m_Panel->Clear();
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

void Game::SetReel(std::string newResult, std::string newAnimate, unsigned int iLines)
{
	if(newResult != "")
	{
		m_Reel->SetResult(newResult);
		m_Reel->Animate(newAnimate);

		if(iLines != 0)
			m_Lines->SetResult(newResult, iLines);
		else
			m_Lines->SetAnimate(newAnimate);
	}
}

std::string Game::GetReel()
{
	return m_Reel->GetResult();
}

std::string Game::GetAnimate()
{
	return m_Lines->GetAnimate();
}

unsigned int Game::GetBet() const
{
	return m_Panel->GetBet();
}

void Game::SetBet(unsigned int newBet)
{
	m_Panel->SetBet(newBet);
}

unsigned int Game::GetLines() const
{
	return m_Panel->GetLines();
}

void Game::SetLines(unsigned int newLines)
{
	m_Panel->SetLines(newLines);
}

void Game::CalcWinning(unsigned int Paid)
{
	m_Panel->CalcWinning(Paid);
}

bool Game::CalcWinningForce()
{
	bool bResult = false;

	if(m_bIsSpinning)
	{
		m_Lines->SetResult(m_Reel->GetResult(), m_Panel->GetLines());

		if(m_Lines->HasSpecial())
			bResult = true;
		else
			m_Panel->CalcWinning(m_Lines->GetTotalWin()  * m_Panel->GetBet());
	}
	else if(m_Lines->HasSpecial())
		bResult = true;

	return bResult;
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
	m_Reel->Pause();
	m_Panel->Clear();
}











