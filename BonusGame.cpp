#include "BonusGame.h"

BonusGame::BonusGame() : State()
{
	m_TextureBackground = NULL;
	m_LabelWinSign = NULL;
	m_TextFieldCredits = NULL;
	m_FontCredits = NULL;
	m_FontWin = NULL;
	m_uiCredits = 0;
	m_iX = 0;
	m_iY = 0;
}

BonusGame::BonusGame(SDL_Renderer* newRenderer) : State(newRenderer)
{
	m_TextureBackground = IMG_LoadTexture(m_Renderer, g_BonusGameBackground);
	if (m_TextureBackground == NULL)
		std::cerr << "Failed to load TextureBackground! SDL Error: " << IMG_GetError() << std::endl;

	m_iX = (g_ScreenWidth - g_BonusWidth) / 2;
	m_iY = (g_ScreenHeight - g_BonusHeight) / 2;

	m_FontCredits = TTF_OpenFont(g_LabelFont, g_BonusFontSizeCredits);
	m_FontWin = TTF_OpenFont(g_WinFont, g_BonusFontSizeWin);

	m_LabelWinSign = new Label(m_Renderer);
	m_LabelWinSign->SetText("Bonus game", m_FontWin, SDL_Color{0xF0, 0xF0, 0x00, 0xFF});
	m_LabelWinSign->SetX(m_iX + (g_BonusWidth - m_LabelWinSign->GetWidth()) / 2);
	m_LabelWinSign->SetY(m_iY + (g_BonusHeight - m_LabelWinSign->GetHeight()) / 2 + g_BonusOffsetY);

	m_TextFieldCredits = new TextField(m_Renderer);
	m_TextFieldCredits->SetFieldSize(g_BonusCreditHeight, g_BonusCreditsWidth);
	m_TextFieldCredits->SetX(m_iX + (g_BonusWidth - m_TextFieldCredits->GetWidth()) / 2);
	m_TextFieldCredits->SetY(m_iY + (g_BonusHeight - m_TextFieldCredits->GetHeight()) / 2 + g_BonusCreditOffsetY);

	m_uiCredits = 0;
}

BonusGame::~BonusGame()
{
	SDL_DestroyTexture(m_TextureBackground);
	delete m_LabelWinSign;
	delete m_TextFieldCredits;
	TTF_CloseFont(m_FontCredits);
	TTF_CloseFont(m_FontWin);
	m_TextureBackground = NULL;
	m_LabelWinSign = NULL;
	m_TextFieldCredits = NULL;
	m_FontCredits = NULL;
	m_FontWin = NULL;
}

void BonusGame::EventHandler(SDL_Event& e)
{

}

void BonusGame::Render(bool UpdateOnly)
{
	if(!UpdateOnly)
	{
		if(m_Renderer == NULL || m_TextureBackground == NULL || m_FontCredits == NULL || m_FontWin == NULL)
			return;

		SDL_Rect tempRect;
		tempRect.h = g_BonusHeight;
		tempRect.w = g_BonusWidth;
		tempRect.x = m_iX;
		tempRect.y = m_iY;

		SDL_RenderCopy(m_Renderer, m_TextureBackground, NULL, &tempRect);

		SDL_SetRenderDrawColor(m_Renderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderDrawRect(m_Renderer, &tempRect);
	}

	m_LabelWinSign->Render(UpdateOnly);
	m_TextFieldCredits->Render(UpdateOnly);
}

void BonusGame::SetCredits(unsigned int credits)
{
	m_uiCredits = credits;
	std::string strCredits;
	std::stringstream ss;

	ss << "YOU WON: " << m_uiCredits;
	strCredits = ss.str();

	m_TextFieldCredits->SetText(strCredits, m_FontCredits, SDL_Color{0xFF, 0xFF, 0xFF, 0xFF});
}
