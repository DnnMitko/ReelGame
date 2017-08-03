#include "BonusGame.h"

BonusGame::BonusGame() : State()
{
	NullAll();
}

BonusGame::BonusGame(SDL_Renderer* newRenderer) : State(newRenderer)
{
	m_uiCredits = 0;

	// Center the box
	m_iX = (g_ScreenWidth - g_BonusWidth) / 2;
	m_iY = (g_ScreenHeight - g_BonusHeight) / 2;

	m_uiTimer = 0;

	// Reset flags
	m_bHasChosen = false;
	m_bHasStarted = false;

	// Initialize elements
	InitFonts();
	InitTitleScreen();
	InitGame();
	InitChests();
	InitSound();
}

BonusGame::~BonusGame()
{
	// Free all members
	SDL_DestroyTexture(m_TextureBackgroundGame);
	SDL_DestroyTexture(m_TextureBackgroundInit);

	Mix_FreeChunk(m_Sound);

	delete m_LabelTitleSign;
	delete m_TextFieldCredits;

	delete m_ButtonStart;

	delete m_Chest1;
	delete m_Chest2;
	delete m_Chest3;

	TTF_CloseFont(m_FontCredits);
	TTF_CloseFont(m_FontTitle);

	// Null all
	NullAll();
}

void BonusGame::EventHandler(SDL_Event& e)
{
	// If you get a mouse click and it's not in transition
	if(e.type == SDL_MOUSEBUTTONDOWN && !m_bHasChosen && !m_bTransitionIn && !m_bTransitionOut)
	{
		// Get mouse position
		int x, y;
		SDL_GetMouseState(&x, &y);

		// Check button if game hasn't started yet.
		if(!m_bHasStarted)
		{
			if(m_ButtonStart->IsIn(x, y))
				m_ButtonStart->Press();
		}
		else
		{
			// Otherwise check the chests and generate prize.
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
	// If it's a mouse release and we're not in transition.
	else if(e.type == SDL_MOUSEBUTTONUP && !m_bTransitionIn && !m_bTransitionOut)
	{
		// If we're on title screen, check the button.
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
	// Check if everything loaded properly.
	if(!m_Renderer || !m_TextureBackgroundGame || !m_TextureBackgroundInit || !m_FontCredits || !m_FontTitle)
		return;

	// Make a rectangle for the box.
	SDL_Rect tempRect;
	tempRect.h = g_BonusHeight;
	tempRect.w = g_BonusWidth;
	tempRect.x = m_iX;
	tempRect.y = m_iY;

	// Choose background to draw.
	if(m_bHasStarted)
		SDL_RenderCopy(m_Renderer, m_TextureBackgroundGame, NULL, &tempRect);
	else
		SDL_RenderCopy(m_Renderer, m_TextureBackgroundInit, NULL, &tempRect);

	// Check timer if user already made a choice.
	if(m_bHasChosen)
	{
		if(SDL_GetTicks() - m_uiTimer >= g_BonusDelay)
			m_bTransitionOut = true;
	}

	// If we're in transition,
	// make checks and adjustments accordingly.
	if(m_bTransitionIn)
		TransitionIn();
	else if(m_bTransitionOut)
		TransitionOut();

	// If we're in the title screen.
	if(!m_bHasStarted)
	{
		// Draw title elements.
		m_LabelTitleSign->Render(false);

		m_LabelCurWin->Render(false);
		m_TextFieldCurWin->Render(false);
		m_ButtonStart->Render(false);
	}
	else
	{
		// Draw game elements.
		m_LabelTitleSign->Render(false);

		m_Chest1->Render(false);
		m_Chest2->Render(false);
		m_Chest3->Render(false);

		m_TextFieldCredits->Render(false);
	}
}

void BonusGame::PrepTransitionIn()
{
	// Raise transitionIN flag.
	m_bTransitionIn = true;

	// Adjust height and reposition elements.
	m_iY = g_BonusHeightTransition;

	m_LabelTitleSign->SetY(m_iY + (g_BonusHeight - m_LabelTitleSign->GetHeight()) / 2 + g_BonusTitleOffsetY);
	m_LabelCurWin->SetY(m_iY + g_BonusHeight + g_BonusTempWinOffsetY - m_LabelCurWin->GetHeight());
	m_TextFieldCurWin->SetY(m_iY + g_BonusHeight + g_BonusTempWinOffsetY);
	m_ButtonStart->SetY(m_iY + g_BonusHeight + g_BonusStartOffsetY);
}

void BonusGame::SetCredits(unsigned int credits)
{
	// Save amount and update the textfield.
	m_uiCredits = 10 * credits;
	UpdateCurWin();
}

unsigned int BonusGame::GetCredits() const
{
	return m_uiCredits;
}

bool BonusGame::GetHasChosen() const
{
	return m_bHasChosen;
}

void BonusGame::NullAll()
{
	m_TextureBackgroundGame = NULL;
	m_TextureBackgroundInit = NULL;

	m_Sound = NULL;

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
	// If the box's in place
	if(m_iY == (g_ScreenHeight - g_BonusHeight) / 2)
	{
		// Drop the flag.
		m_bTransitionIn = false;

		// Play sound effect.
		Mix_PlayChannel(-1, m_Sound, 0);
	}
	else
	{
		// Reposition
		m_iY += g_TransitionStep;

		m_LabelTitleSign->SetY(m_iY + (g_BonusHeight - m_LabelTitleSign->GetHeight()) / 2 + g_BonusTitleOffsetY);
		m_LabelCurWin->SetY(m_iY + g_BonusHeight + g_BonusTempWinOffsetY - m_LabelCurWin->GetHeight());
		m_TextFieldCurWin->SetY(m_iY + g_BonusHeight + g_BonusTempWinOffsetY);
		m_ButtonStart->SetY(m_iY + g_BonusHeight + g_BonusStartOffsetY);
	}
}

void BonusGame::TransitionOut()
{
	// If the box is hidden.
	if(m_iY + g_BonusHeight <= 0)
	{
		// Drop the transition flag.
		m_bTransitionOut = false;

		// Raise the Switch flag.
		m_bSwitch = true;
	}
	else
	{
		// Reposition
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
	// Load and check background texture.
	m_TextureBackgroundInit = IMG_LoadTexture(m_Renderer, g_BonusGameBackgroundInit);
	if(m_TextureBackgroundInit == NULL)
		std::cerr << "Failed to load TextureBackgroundInit! SDL Error: " << IMG_GetError() << std::endl;

	// Load title label.
	m_LabelTitleSign = new Label(m_Renderer);
	m_LabelTitleSign->SetText(g_BonusTitle, m_FontTitle, g_ColorYellow);
	m_LabelTitleSign->SetX(m_iX + (g_BonusWidth - m_LabelTitleSign->GetWidth()) / 2);
	m_LabelTitleSign->SetY(m_iY + (g_BonusHeight - m_LabelTitleSign->GetHeight()) / 2 + g_BonusTitleOffsetY);

	// Load current winnings label.
	m_LabelCurWin = new Label(m_Renderer);
	m_LabelCurWin->SetText(g_BonusTempWinMessage, m_FontCredits, g_ColorYellow);
	m_LabelCurWin->SetX(m_iX + g_BonusTempWinOffsetX + (g_BonusTempWinFieldWidth - m_LabelCurWin->GetWidth()) / 2);
	m_LabelCurWin->SetY(m_iY + g_BonusHeight + g_BonusTempWinOffsetY - m_LabelCurWin->GetHeight());

	// Load current winnings text field.
	m_TextFieldCurWin = new TextField(m_Renderer);
	m_TextFieldCurWin->SetX(m_iX + g_BonusTempWinOffsetX);
	m_TextFieldCurWin->SetY(m_iY + g_BonusHeight + g_BonusTempWinOffsetY);
	m_TextFieldCurWin->SetFieldSize(g_BonusTempWinFieldHeight, g_BonusTempWinFieldWidth);
	UpdateCurWin();

	// Load Start button
	m_ButtonStart = new Button(m_Renderer);
	m_ButtonStart->SetX(m_iX + g_BonusWidth + g_BonusStartOffsetX);
	m_ButtonStart->SetY(m_iY + g_BonusHeight + g_BonusStartOffsetY);
	m_ButtonStart->SetFieldSize(g_BonusStartHeight, g_BonusStartWidth);
	m_ButtonStart->SetText("Start", m_FontCredits, g_ColorBlack);
}

void BonusGame::InitFonts()
{
	// Load and check fonts.
	m_FontCredits = TTF_OpenFont(g_FontLabel, g_BonusFontSizeCredits);
	if(m_FontCredits == NULL)
		std::cerr << "Failed to load Label Font! SDL Error: " << TTF_GetError() << std::endl;

	m_FontTitle = TTF_OpenFont(g_FontTitle, g_BonusFontSizeWin);
	if(m_FontTitle == NULL)
		std::cerr << "Failed to load Title Font! SDL Error: " << TTF_GetError() << std::endl;
}

void BonusGame::InitGame()
{
	// Load and check background texture.
	m_TextureBackgroundGame = IMG_LoadTexture(m_Renderer, g_BonusGameBackground);
	if(m_TextureBackgroundGame == NULL)
		std::cerr << "Failed to load TextureBackground! SDL Error: " << IMG_GetError() << std::endl;

	// Load chest winnings field.
	m_TextFieldCredits = new TextField(m_Renderer);
	m_TextFieldCredits->SetFieldSize(g_BonusCreditHeight, g_BonusCreditsWidth);
	m_TextFieldCredits->SetX(m_iX + (g_BonusWidth - m_TextFieldCredits->GetWidth()) / 2);
	m_TextFieldCredits->SetY(m_iY + (g_BonusHeight - m_TextFieldCredits->GetHeight()) / 2 + g_BonusCreditOffsetY);
	m_TextFieldCredits->SetText(g_BonusSubTitle, m_FontCredits, g_ColorWhite);
}
void BonusGame::InitChests()
{
	// Load and position chests.
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

void BonusGame::InitSound()
{
	// Load sound.
	m_Sound = Mix_LoadWAV(g_BonusSound);
}

void BonusGame::UpdateChestWin(int iWinnings)
{
	std::string strCredits;
	std::stringstream ss;

	// Make the chest winnings in a string and show it.
	ss << g_BonusWinMessage << iWinnings;
	strCredits = ss.str();

	m_TextFieldCredits->SetText(strCredits, m_FontCredits, g_ColorWhite);
}

void BonusGame::UpdateCurWin()
{
	std::string strCredits;
	std::stringstream ss;

	// Make the current winnings to a string and show it.
	ss << m_uiCredits;
	strCredits = ss.str();

	m_TextFieldCurWin->SetText(strCredits, m_FontCredits, g_ColorWhite);
}

void BonusGame::GenPrize()
{
	// Generate a prize.
	int iWinnings = (rand() % (g_BonusUpperLimit - g_BonusLowerLimit + 1) + g_BonusLowerLimit) * 1000;
	UpdateChestWin(iWinnings);

	// Add it to the current winnings.
	m_uiCredits += iWinnings;

	// Start the timer.
	m_uiTimer = SDL_GetTicks();
}

void BonusGame::ResetGame()
{
	// Close all chests.
	m_Chest1->Close();
	m_Chest2->Close();
	m_Chest3->Close();

	// Reset flags.
	m_bHasChosen = false;
	m_bHasStarted = false;

	// Reset the text on the chest winnings field.
	m_TextFieldCredits->SetText(g_BonusSubTitle, m_FontCredits, g_ColorWhite);

	// Reposition game elements.
	m_iY = (g_ScreenHeight - g_BonusHeight) / 2;
	m_LabelTitleSign->SetY(m_iY + (g_BonusHeight - m_LabelTitleSign->GetHeight()) / 2 + g_BonusTitleOffsetY);
	m_Chest1->SetY(m_iY + g_BonusChestOffsetY);
	m_Chest2->SetY(m_iY + g_BonusChestOffsetY);
	m_Chest3->SetY(m_iY + g_BonusChestOffsetY);
	m_TextFieldCredits->SetY(m_iY + (g_BonusHeight - m_TextFieldCredits->GetHeight()) / 2 + g_BonusCreditOffsetY);
}











