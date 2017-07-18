#include "Game.h"

Game::Game() : State()
{
	m_TextureBackground = NULL;
	m_Panel = NULL;
}

Game::Game(SDL_Renderer* newRenderer) : State(newRenderer)
{
	m_TextureBackground = IMG_LoadTexture(m_Renderer, g_GameBackground);
	if(m_TextureBackground == NULL)
		std::cerr << "Failed to load TextureBackground! SDL Error: " << IMG_GetError() << std::endl;

	m_Panel = new GamePanel(m_Renderer);
}

Game::~Game()
{
	delete m_Panel;
	m_Panel = NULL;

	SDL_DestroyTexture(m_TextureBackground);
	m_TextureBackground = NULL;
}

void Game::Render(bool UpdateOnly)
{
	if(!m_Renderer || !m_TextureBackground)
		return;

	if(!UpdateOnly)
	{
		SDL_RenderCopy(m_Renderer, m_TextureBackground, NULL, NULL);
	}

	m_Panel->Render(UpdateOnly);
}

void Game::EventHandler(SDL_Event& e)
{
	m_Panel->EventHandler(e, m_bSwitch);
}

void Game::SetCredits(unsigned int newCredits)
{
	m_Panel->SetCredits(newCredits);
}

unsigned int Game::GetCredits() const
{
	return m_Panel->GetCredits();
}

unsigned int Game::GetTotalBet() const
{
	return m_Panel->GetTotalBet();
}

unsigned int Game::GetPaid() const
{
	return m_Panel->GetPaid();
}

void Game::CalcWinning(unsigned int Paid)
{
	m_Panel->CalcWinning(Paid);
}

bool Game::GetWin() const
{
	return m_Panel->GetWin();
}

bool Game::GetBonus() const
{
	return m_Panel->GetBonus();
}

void Game::ResetWin()
{
	m_Panel->ResetWin();
}

void Game::ResetBonus()
{
	m_Panel->ResetBonus();
}

void Game::Clear()
{
	m_Panel->Clear();
}











