#include "BonusGame.h"

BonusGame::BonusGame() : State()
{
	NullAll();
}

BonusGame::BonusGame(SDL_Renderer* newRenderer) : State(newRenderer)
{
	m_uiCredits = 0;

	m_iX = (g_ScreenWidth - g_BonusWidth) / 2;
	m_iY = (g_ScreenHeight - g_BonusHeight) / 2;

	m_uiTimer = 0;

	m_bHasChosen = false;
	m_bHasStarted = false;

	InitFonts();
	InitTitleScreen();
	InitGame();
	InitChests();
}

BonusGame::~BonusGame()
{
	SDL_DestroyTexture(m_TextureBackgroundGame);
	SDL_DestroyTexture(m_TextureBackgroundInit);

	delete m_LabelTitleSign;
	delete m_TextFieldCredits;

	delete m_ButtonStart;

	delete m_Chest1;
	delete m_Chest2;
	delete m_Chest3;

	TTF_CloseFont(m_FontCredits);
	TTF_CloseFont(m_FontTitle);

	NullAll();
}

void BonusGame::EventHandler(SDL_Event& e)
{
	if(e.type == SDL_MOUSEBUTTONDOWN && !m_bHasChosen && !m_bTransitionIn && !m_bTransitionOut)
	{
		int x, y;
		SDL_GetMouseState(&x, &y);

		if(!m_bHasStarted)
		{
			if(m_ButtonStart->IsIn(x, y))
				m_ButtonStart->Press();
		}
		else
		{
			if(m_Chest1->IsIn(x, y))
			{
				m_Chest1->Open();
				m_bHasChosen = true;

				GenPrize();
			}
			else if(m_Chest2->IsIn(x, y))
			{
				m_Chest2->Open();
				m_bHasChosen = true;

				GenPrize();
			}
			else if(m_Chest3->IsIn(x, y))
			{
				m_Chest3->Open();
				m_bHasChosen = true;

				GenPrize();
			}
		}
	}
	else if(e.type == SDL_MOUSEBUTTONUP && !m_bTransitionIn && !m_bTransitionOut)
	{
		if(!m_bHasStarted)
		{
			int x, y;
			SDL_GetMouseState(&x, &y);

			if(m_ButtonStart->IsIn(x, y) && m_ButtonStart->IsPressed())
			{
				m_bHasStarted = true;

				Render(false);
			}

			m_ButtonStart->Release();
		}
	}
}

void BonusGame::Render(bool UpdateOnly)
{
	if(!m_Renderer || !m_TextureBackgroundGame || !m_TextureBackgroundInit || !m_FontCredits || !m_FontTitle)
		return;

	SDL_Rect tempRect;
	tempRect.h = g_BonusHeight;
	tempRect.w = g_BonusWidth;
	tempRect.x = m_iX;
	tempRect.y = m_iY;

	if(m_bHasStarted)
		SDL_RenderCopy(m_Renderer, m_TextureBackgroundGame, NULL, &tempRect);
	else
		SDL_RenderCopy(m_Renderer, m_TextureBackgroundInit, NULL, &tempRect);

	if(m_bHasChosen)
	{
		if(SDL_GetTicks() - m_uiTimer >= g_BonusDelay)
			m_bTransitionOut = true;
	}

	if(m_bTransitionIn)
		TransitionIn();

	else if(m_bTransitionOut)
		TransitionOut();

	if(!m_bHasStarted)
	{
		m_LabelTitleSign->Render(false);

		m_LabelCurWin->Render(false);
		m_TextFieldCurWin->Render(false);
		m_ButtonStart->Render(false);
	}
	else
	{
		m_LabelTitleSign->Render(false);

		m_Chest1->Render(false);
		m_Chest2->Render(false);
		m_Chest3->Render(false);

		m_TextFieldCredits->Render(false);
	}
}

void BonusGame::PrepTransitionIn()
{
	m_bTransitionIn = true;

	m_iY = g_BonusHeightTransition;

	m_LabelTitleSign->SetY(m_iY + (g_BonusHeight - m_LabelTitleSign->GetHeight()) / 2 + g_BonusTitleOffsetY);
	m_LabelCurWin->SetY(m_iY + g_BonusHeight + g_BonusTempWinOffsetY - m_LabelCurWin->GetHeight());
	m_TextFieldCurWin->SetY(m_iY + g_BonusHeight + g_BonusTempWinOffsetY);
	m_ButtonStart->SetY(m_iY + g_BonusHeight + g_BonusStartOffsetY);
}

void BonusGame::SetCredits(unsigned int credits)
{
	m_uiCredits = 10 * credits;
	UpdateCurWin();
}

unsigned int BonusGame::GetCredits() const
{
	return m_uiCredits;
}

void BonusGame::NullAll()
{
	m_TextureBackgroundGame = NULL;
	m_TextureBackgroundInit = NULL;

	m_LabelTitleSign = NULL;
	m_TextFieldCredits = NULL;

	m_Chest1 = NULL;
	m_Chest2 = NULL;
	m_Chest3 = NULL;

	m_FontCredits = NULL;
	m_FontTitle = NULL;

	m_uiCredits = 0;

	m_uiTimer = 0;

	m_LabelCurWin = NULL;
	m_TextFieldCurWin = NULL;
	m_ButtonStart = NULL;

	m_bHasChosen = false;
	m_bHasStarted = false;

	m_iX = 0;
	m_iY = 0;
}

void BonusGame::TransitionIn()
{
	if(m_iY == (g_ScreenHeight - g_BonusHeight) / 2)
	{
		m_bTransitionIn = false;
	}
	else
	{
		m_iY += g_TransitionStep;

		m_LabelTitleSign->SetY(m_iY + (g_BonusHeight - m_LabelTitleSign->GetHeight()) / 2 + g_BonusTitleOffsetY);
		m_LabelCurWin->SetY(m_iY + g_BonusHeight + g_BonusTempWinOffsetY - m_LabelCurWin->GetHeight());
		m_TextFieldCurWin->SetY(m_iY + g_BonusHeight + g_BonusTempWinOffsetY);
		m_ButtonStart->SetY(m_iY + g_BonusHeight + g_BonusStartOffsetY);
	}
}

void BonusGame::TransitionOut()
{
	if(m_iY + g_BonusHeight <= 0)
	{
		m_bTransitionOut = false;
		m_bSwitch = true;
	}
	else
	{
		m_iY -= g_TransitionStep;

		m_LabelTitleSign->SetY(m_iY + (g_BonusHeight - m_LabelTitleSign->GetHeight()) / 2 + g_BonusTitleOffsetY);
		m_Chest1->SetY(m_iY + g_BonusChestOffsetY);
		m_Chest2->SetY(m_iY + g_BonusChestOffsetY);
		m_Chest3->SetY(m_iY + g_BonusChestOffsetY);
		m_TextFieldCredits->SetY(m_iY + (g_BonusHeight - m_TextFieldCredits->GetHeight()) / 2 + g_BonusCreditOffsetY);
	}
}

void BonusGame::InitTitleScreen()
{
	m_TextureBackgroundInit = IMG_LoadTexture(m_Renderer, g_BonusGameBackgroundInit);
	if (m_TextureBackgroundInit == NULL)
		std::cerr << "Failed to load TextureBackgroundInit! SDL Error: " << IMG_GetError() << std::endl;

	m_LabelTitleSign = new Label(m_Renderer);
	m_LabelTitleSign->SetText(g_BonusTitle, m_FontTitle, SDL_Color{0xF0, 0xF0, 0x00, 0xFF});
	m_LabelTitleSign->SetX(m_iX + (g_BonusWidth - m_LabelTitleSign->GetWidth()) / 2);
	m_LabelTitleSign->SetY(m_iY + (g_BonusHeight - m_LabelTitleSign->GetHeight()) / 2 + g_BonusTitleOffsetY);

	m_LabelCurWin = new Label(m_Renderer);
	m_LabelCurWin->SetText(g_BonusTempWinMessage, m_FontCredits, SDL_Color{0xF0, 0xF0, 0x00, 0xFF});
	m_LabelCurWin->SetX(m_iX + g_BonusTempWinOffsetX + (g_BonusTempWinFieldWidth - m_LabelCurWin->GetWidth()) / 2);
	m_LabelCurWin->SetY(m_iY + g_BonusHeight + g_BonusTempWinOffsetY - m_LabelCurWin->GetHeight());

	m_TextFieldCurWin = new TextField(m_Renderer);
	m_TextFieldCurWin->SetX(m_iX + g_BonusTempWinOffsetX);
	m_TextFieldCurWin->SetY(m_iY + g_BonusHeight + g_BonusTempWinOffsetY);
	m_TextFieldCurWin->SetFieldSize(g_BonusTempWinFieldHeight, g_BonusTempWinFieldWidth);
	UpdateCurWin();

	m_ButtonStart = new Button(m_Renderer);
	m_ButtonStart->SetX(m_iX + g_BonusWidth + g_BonusStartOffsetX);
	m_ButtonStart->SetY(m_iY + g_BonusHeight + g_BonusStartOffsetY);
	m_ButtonStart->SetFieldSize(g_BonusStartHeight, g_BonusStartWidth);
	m_ButtonStart->SetText("Start", m_FontCredits, SDL_Color{0x00, 0x00, 0x00, 0xFF});
}

void BonusGame::InitFonts()
{
	m_FontCredits = TTF_OpenFont(g_FontLabel, g_BonusFontSizeCredits);
	if(m_FontCredits == NULL)
		std::cerr << "Failed to load Label Font! SDL Error: " << TTF_GetError() << std::endl;

	m_FontTitle = TTF_OpenFont(g_FontTitle, g_BonusFontSizeWin);
	if(m_FontTitle == NULL)
		std::cerr << "Failed to load Title Font! SDL Error: " << TTF_GetError() << std::endl;
}

void BonusGame::InitGame()
{
	m_TextureBackgroundGame = IMG_LoadTexture(m_Renderer, g_BonusGameBackground);
	if (m_TextureBackgroundGame == NULL)
		std::cerr << "Failed to load TextureBackground! SDL Error: " << IMG_GetError() << std::endl;

	m_TextFieldCredits = new TextField(m_Renderer);
	m_TextFieldCredits->SetFieldSize(g_BonusCreditHeight, g_BonusCreditsWidth);
	m_TextFieldCredits->SetX(m_iX + (g_BonusWidth - m_TextFieldCredits->GetWidth()) / 2);
	m_TextFieldCredits->SetY(m_iY + (g_BonusHeight - m_TextFieldCredits->GetHeight()) / 2 + g_BonusCreditOffsetY);
	m_TextFieldCredits->SetText(g_BonusSubTitle, m_FontCredits, SDL_Color{0xFF, 0xFF, 0xFF, 0xFF});
}
void BonusGame::InitChests()
{
	m_Chest1 = new Chest(m_Renderer);
	m_Chest1->SetX(m_iX + g_BonusChest1OffsetX);
	m_Chest1->SetY(m_iY + g_BonusChestOffsetY);

	m_Chest2 = new Chest(m_Renderer);
	m_Chest2->SetX(m_iX + g_BonusChest2OffsetX);
	m_Chest2->SetY(m_iY + g_BonusChestOffsetY);

	m_Chest3 = new Chest(m_Renderer);
	m_Chest3->SetX(m_iX + g_BonusChest3OffsetX);
	m_Chest3->SetY(m_iY + g_BonusChestOffsetY);
}

void BonusGame::UpdateChestWin(int iWinnings)
{
	std::string strCredits;
	std::stringstream ss;

	ss << g_BonusWinMessage << iWinnings;
	strCredits = ss.str();

	m_TextFieldCredits->SetText(strCredits, m_FontCredits, SDL_Color{0xFF, 0xFF, 0xFF, 0xFF});
}

void BonusGame::UpdateCurWin()
{
	std::string strCredits;
	std::stringstream ss;

	ss << m_uiCredits;
	strCredits = ss.str();

	m_TextFieldCurWin->SetText(strCredits, m_FontCredits, SDL_Color{0xFF, 0xFF, 0xFF, 0xFF});
}

void BonusGame::GenPrize()
{
	int iWinnings = (rand() % (g_BonusUpperLimit - g_BonusLowerLimit + 1) + g_BonusLowerLimit) * 1000;
	UpdateChestWin(iWinnings);

	m_uiCredits += iWinnings;

	m_uiTimer = SDL_GetTicks();
}

void BonusGame::ResetGame()
{
	m_Chest1->Close();
	m_Chest2->Close();
	m_Chest3->Close();

	m_bHasChosen = false;
	m_bHasStarted = false;

	m_TextFieldCredits->SetText(g_BonusSubTitle, m_FontCredits, SDL_Color{0xFF, 0xFF, 0xFF, 0xFF});

	m_iY = (g_ScreenHeight - g_BonusHeight) / 2;
	m_LabelTitleSign->SetY(m_iY + (g_BonusHeight - m_LabelTitleSign->GetHeight()) / 2 + g_BonusTitleOffsetY);
	m_Chest1->SetY(m_iY + g_BonusChestOffsetY);
	m_Chest2->SetY(m_iY + g_BonusChestOffsetY);
	m_Chest3->SetY(m_iY + g_BonusChestOffsetY);
	m_TextFieldCredits->SetY(m_iY + (g_BonusHeight - m_TextFieldCredits->GetHeight()) / 2 + g_BonusCreditOffsetY);
}











