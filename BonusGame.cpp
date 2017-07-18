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

	m_Chest1 = new Chest(m_Renderer);
	m_Chest1->SetX(45 + m_iX);
	m_Chest1->SetY(94 + m_iY);

	m_Chest2 = new Chest(m_Renderer);
	m_Chest2->SetX(242 + m_iX);
	m_Chest2->SetY(94 + m_iY);

	m_Chest3 = new Chest(m_Renderer);
	m_Chest3->SetX(439 + m_iX);
	m_Chest3->SetY(94 + m_iY);

	m_uiCredits = 0;

	m_uiTimer = 0;

	m_bHasChosen = false;
}

BonusGame::~BonusGame()
{
	SDL_DestroyTexture(m_TextureBackground);

	delete m_LabelTitleSign;
	delete m_TextFieldCredits;

	delete m_Chest1;
	delete m_Chest2;
	delete m_Chest3;

	TTF_CloseFont(m_FontCredits);
	TTF_CloseFont(m_FontTitle);

	NullAll();
}

void BonusGame::EventHandler(SDL_Event& e)
{
	if(e.type == SDL_MOUSEBUTTONDOWN && !m_bHasChosen)
	{
		int x, y;
		SDL_GetMouseState(&x, &y);

		if(m_Chest1->IsIn(x, y))
		{
			m_Chest1->Open();
			m_bHasChosen = true;

			m_uiCredits += rand() % 28001 + 2000;
			UpdateCredits();

			m_uiTimer = SDL_GetTicks();
		}
		else if(m_Chest2->IsIn(x, y))
		{
			m_Chest2->Open();
			m_bHasChosen = true;

			m_uiCredits += rand() % 28001 + 2000;
			UpdateCredits();

			m_uiTimer = SDL_GetTicks();
		}
		else if(m_Chest3->IsIn(x, y))
		{
			m_Chest3->Open();
			m_bHasChosen = true;

			m_uiCredits += rand() % 28001 + 2000;
			UpdateCredits();

			m_uiTimer = SDL_GetTicks();
		}
	}
}

void BonusGame::Render(bool UpdateOnly)
{
	if(m_Renderer == NULL || m_TextureBackground == NULL || m_FontCredits == NULL || m_FontTitle == NULL)
		return;

	if(!UpdateOnly)
	{
		SDL_Rect tempRect;
		tempRect.h = g_BonusHeight;
		tempRect.w = g_BonusWidth;
		tempRect.x = m_iX;
		tempRect.y = m_iY;

		SDL_RenderCopy(m_Renderer, m_TextureBackground, NULL, &tempRect);
	}

	m_LabelTitleSign->Render(UpdateOnly);

	m_Chest1->Render(UpdateOnly);
	m_Chest2->Render(UpdateOnly);
	m_Chest3->Render(UpdateOnly);

	m_TextFieldCredits->Render(UpdateOnly);

	if(m_bHasChosen)
	{
		if(SDL_GetTicks() - m_uiTimer >= 3000)
			m_bSwitch = true;
	}
}

void BonusGame::SetCredits(unsigned int credits)
{
	m_uiCredits = 10 * credits;
}

unsigned int BonusGame::GetCredits() const
{
	return m_uiCredits;
}

void BonusGame::NullAll()
{
	m_TextureBackground = NULL;

	m_LabelTitleSign = NULL;
	m_TextFieldCredits = NULL;

	m_Chest1 = NULL;
	m_Chest2 = NULL;
	m_Chest3 = NULL;

	m_FontCredits = NULL;
	m_FontTitle = NULL;

	m_uiCredits = 0;

	m_uiTimer = 0;

	m_bHasChosen = false;

	m_iX = 0;
	m_iY = 0;
}

void BonusGame::UpdateCredits()
{
	std::string strCredits;
	std::stringstream ss;

	ss << "YOU WON: " << m_uiCredits;
	strCredits = ss.str();

	m_TextFieldCredits->SetText(strCredits, m_FontCredits, SDL_Color{0xFF, 0xFF, 0xFF, 0xFF});
}

void BonusGame::ResetGame()
{
	m_Chest1->Close();
	m_Chest2->Close();
	m_Chest3->Close();

	m_bHasChosen = false;

	m_TextFieldCredits->SetText("Choose your treasure!", m_FontCredits, SDL_Color{0xFF, 0xFF, 0xFF, 0xFF});
}











