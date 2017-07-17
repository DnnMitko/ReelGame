#include "BonusGame.h"

BonusGame::BonusGame() : State()
{
	NullAll();
}

BonusGame::BonusGame(SDL_Renderer* newRenderer) : State(newRenderer)
{
	m_TextureBackground = IMG_LoadTexture(m_Renderer, g_BonusGameBackground);
	if (m_TextureBackground == NULL)
		std::cerr << "Failed to load TextureBackground! SDL Error: " << IMG_GetError() << std::endl;

	m_iX = (g_ScreenWidth - g_BonusWidth) / 2;
	m_iY = (g_ScreenHeight - g_BonusHeight) / 2;

	m_FontCredits = TTF_OpenFont(g_FontLabel, g_BonusFontSizeCredits);
	if(m_FontCredits == NULL)
		std::cerr << "Failed to load Label Font! SDL Error: " << TTF_GetError() << std::endl;

	m_FontTitle = TTF_OpenFont(g_FontTitle, g_BonusFontSizeWin);
	if(m_FontTitle == NULL)
		std::cerr << "Failed to load Title Font! SDL Error: " << TTF_GetError() << std::endl;

	m_LabelTitleSign = new Label(m_Renderer);
	m_LabelTitleSign->SetText("Bonus game", m_FontTitle, SDL_Color{0xF0, 0xF0, 0x00, 0xFF});
	m_LabelTitleSign->SetX(m_iX + (g_BonusWidth - m_LabelTitleSign->GetWidth()) / 2);
	m_LabelTitleSign->SetY(m_iY + (g_BonusHeight - m_LabelTitleSign->GetHeight()) / 2 + g_BonusOffsetY);

	m_TextFieldCredits = new TextField(m_Renderer);
	m_TextFieldCredits->SetFieldSize(g_BonusCreditHeight, g_BonusCreditsWidth);
	m_TextFieldCredits->SetX(m_iX + (g_BonusWidth - m_TextFieldCredits->GetWidth()) / 2);
	m_TextFieldCredits->SetY(m_iY + (g_BonusHeight - m_TextFieldCredits->GetHeight()) / 2 + g_BonusCreditOffsetY);
	m_TextFieldCredits->SetText("Choose your treasure!", m_FontCredits, SDL_Color{0xFF, 0xFF, 0xFF, 0xFF});

	m_uiCredits = 0;
}

BonusGame::~BonusGame()
{
	SDL_DestroyTexture(m_TextureBackground);

	delete m_LabelTitleSign;
	delete m_TextFieldCredits;

	TTF_CloseFont(m_FontCredits);
	TTF_CloseFont(m_FontTitle);

	NullAll();
}

void BonusGame::EventHandler(SDL_Event& e)
{

}

void BonusGame::Render(bool UpdateOnly)
{
	if(!UpdateOnly)
	{
		if(m_Renderer == NULL || m_TextureBackground == NULL || m_FontCredits == NULL || m_FontTitle == NULL)
			return;

		SDL_Rect tempRect;
		tempRect.h = g_BonusHeight;
		tempRect.w = g_BonusWidth;
		tempRect.x = m_iX;
		tempRect.y = m_iY;

		SDL_RenderCopy(m_Renderer, m_TextureBackground, NULL, &tempRect);
	}

	m_LabelTitleSign->Render(UpdateOnly);
	m_TextFieldCredits->Render(UpdateOnly);
}

void BonusGame::SetCredits(unsigned int credits)
{//TODO
	/*m_uiCredits = credits;
	std::string strCredits;
	std::stringstream ss;

	ss << "YOU WON: " << m_uiCredits;
	strCredits = ss.str();

	m_TextFieldCredits->SetText(strCredits, m_FontCredits, SDL_Color{0xFF, 0xFF, 0xFF, 0xFF});*/
}

void BonusGame::NullAll()
{
	m_TextureBackground = NULL;

	m_LabelTitleSign = NULL;
	m_TextFieldCredits = NULL;

	m_FontCredits = NULL;
	m_FontTitle = NULL;

	m_uiCredits = 0;

	m_iX = 0;
	m_iY = 0;
}
