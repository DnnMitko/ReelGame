#include "Intro.h"

Intro::Intro() : State()
{
	NullAll();
}

Intro::Intro(SDL_Renderer* newRenderer) : State(newRenderer)
{
	m_uiCredit = 0;
	m_uiCounterVolume = 0;

	m_TextureBackground = NULL;
	m_TextureBackground = IMG_LoadTexture(m_Renderer, "images/TitleScreen.png");
	if( m_TextureBackground == NULL )
		std::cerr << "Failed to load TextureBackground! SDL Error: " << IMG_GetError() << std::endl;

	m_Font = TTF_OpenFont(g_FontLabel, g_IntroFontSize);
	if( m_Font == NULL )
		std::cerr << "Failed to load Label Font! SDL Error: " << IMG_GetError() << std::endl;

	m_BackgroundSound = Mix_LoadMUS(g_BackgroundSound);
	if(!m_BackgroundSound)
		std::cerr << "Failed to load Background music! SDL_mixer Error: " << Mix_GetError() << "\n";
	else
		Mix_PlayMusic(m_BackgroundSound, -1);

	InitStartGame();
	InitResumeGame();
	InitInsertCredit();
	InitInfo();
	InitVolume();
	InitCredits();
}

Intro::~Intro()
{
	SDL_DestroyTexture(m_TextureBackground);

	TTF_CloseFont(m_Font);

	Mix_FreeMusic(m_BackgroundSound);

	delete m_StartGame;
	delete m_ResumeGame;

	delete m_LabelCredit;
	delete m_InsertCreditMinus;
	delete m_InsertCreditPlus;

	delete m_Info;

	delete m_LabelVolume;
	delete m_VolumePlus;
	delete m_VolumeMinus;

	delete m_LabelCredits;
	delete m_TextFieldCredits;

	NullAll();
}

void Intro::Render(bool UpdateOnly)
{
	if(!m_Renderer || !m_TextureBackground || !m_Font)
		return;

	if(!UpdateOnly)
	{
		m_uiCredit = 0;
		UpdateCredits();

		SDL_RenderCopy(m_Renderer, m_TextureBackground, NULL, NULL);
	}

	m_StartGame->Render(UpdateOnly);
	m_ResumeGame->Render(UpdateOnly);

	m_LabelCredit->Render(UpdateOnly);
	m_InsertCreditMinus->Render(UpdateOnly);
	m_InsertCreditPlus->Render(UpdateOnly);

	m_Info->Render(UpdateOnly);

	m_LabelVolume->Render(UpdateOnly);
	m_VolumePlus->Render(UpdateOnly);
	m_VolumeMinus->Render(UpdateOnly);

	m_LabelCredits->Render(UpdateOnly);
	m_TextFieldCredits->Render(UpdateOnly);
}

void Intro::EventHandler(SDL_Event& e)
{
	int x;
	int y;

	if(e.type == SDL_MOUSEBUTTONDOWN)
	{
		SDL_GetMouseState(&x, &y);

		if (m_StartGame->IsIn(x, y))
			m_StartGame->Press();
		else if (m_ResumeGame->IsIn(x, y))
			m_ResumeGame->Press();
		else if (m_InsertCreditPlus->IsIn(x, y))
			m_InsertCreditPlus->Press();
		else if (m_InsertCreditMinus->IsIn(x,y))
			m_InsertCreditMinus->Press();
		else if (m_Info->IsIn(x, y))
			m_Info->Press();
		else if (m_VolumePlus->IsIn(x, y))
			m_VolumePlus->Press();
		else if (m_VolumeMinus->IsIn(x,y))
			m_VolumeMinus->Press();
	}
	else if (e.type == SDL_MOUSEBUTTONUP)
	{
		m_uiCounterVolume = 0;
		SDL_GetMouseState(&x, &y);

		if(m_StartGame->IsIn(x, y) && m_StartGame->IsPressed())
		{
			m_bSwitch = true;
		}

		else if(m_ResumeGame->IsIn(x, y) && m_ResumeGame->IsPressed())
		{
			//TODO
		}

		else if(m_InsertCreditPlus->IsIn(x, y) && m_InsertCreditPlus->IsPressed())
		{
			m_uiCredit += g_IntroCreditIncrement;
			UpdateCredits();
		}
		else if(m_InsertCreditMinus->IsIn(x,y) && m_InsertCreditMinus->IsPressed())
		{
			if(m_uiCredit > 0)
			{
				m_uiCredit -= g_IntroCreditIncrement;
				UpdateCredits();
			}
		}
		else if(m_Info->IsIn(x,y) && m_Info->IsPressed())
		{
			// TODO
		}
		else if (m_VolumePlus->IsIn(x, y) && m_VolumePlus->IsPressed())
		{
			//TODO
		}
		else if (m_VolumeMinus->IsIn(x, y) && m_VolumeMinus->IsPressed())
		{
			//TODO
		}
		ReleaseAll();
	}
}

void Intro::PrepTransitionIn()
{
	//TODO
}

unsigned int Intro::GetCredits() const
{
	return m_uiCredit;
}

void Intro::ReleaseAll()
{
	m_StartGame->Release();
	m_ResumeGame->Release();
	m_InsertCreditPlus->Release();
	m_InsertCreditMinus->Release();
	m_Info->Release();
	m_VolumePlus->Release();
	m_VolumeMinus->Release();
}

void Intro::NullAll()
{
	m_uiCredit = 0;

	m_TextureBackground = NULL;

	m_Font = NULL;

	m_StartGame = NULL;
	m_ResumeGame = NULL;

	m_LabelCredit = NULL;
	m_InsertCreditPlus = NULL;
	m_InsertCreditMinus = NULL;

	m_Info = NULL;

	m_LabelVolume = NULL;
	m_VolumePlus = NULL;
	m_VolumeMinus = NULL;

	m_LabelCredits = NULL;
	m_TextFieldCredits = NULL;

	m_BackgroundSound = NULL;
}

void Intro::InitStartGame()
{
	m_StartGame = new Button(m_Renderer);
	m_StartGame->SetX((g_ScreenWidth - g_IntroButtonWidth) / 2);
	m_StartGame->SetY(g_IntroFirstButtonY);
	m_StartGame->SetFieldSize(g_IntroButtonHeight, g_IntroButtonWidth);
	m_StartGame->SetText(g_IntroButtonNewGame, m_Font, SDL_Color{0x00, 0x00, 0x00, 0xFF});
}

void Intro::InitResumeGame()
{
	m_ResumeGame = new Button(m_Renderer);
	m_ResumeGame->SetX((g_ScreenWidth - g_IntroButtonWidth) / 2);
	m_ResumeGame->SetY(g_IntroFirstButtonY + g_IntroButtonHeight + 10);
	m_ResumeGame->SetFieldSize(g_IntroButtonHeight, g_IntroButtonWidth);
	m_ResumeGame->SetText(g_IntroButtonResumeGame, m_Font, SDL_Color{0x00, 0x00, 0x00, 0xFF});
}

void Intro::InitInsertCredit()
{
	m_InsertCreditMinus = new Button(m_Renderer);
	m_InsertCreditMinus->SetX((g_ScreenWidth - g_IntroButtonWidth) / 2);
	m_InsertCreditMinus->SetY(g_IntroFirstButtonY + 2* (g_IntroButtonHeight + 10));
	m_InsertCreditMinus->SetFieldSize(g_IntroButtonHeight, g_IntroButtonWidth / 4);
	m_InsertCreditMinus->SetText(g_IntroButtonMinus, m_Font, SDL_Color{0x00, 0x00, 0x00, 0xFF});

	m_InsertCreditPlus = new Button(m_Renderer);
	m_InsertCreditPlus->SetX(g_IntroButtonVolumePlusX);
	m_InsertCreditPlus->SetY(g_IntroFirstButtonY + 2* (g_IntroButtonHeight + 10));
	m_InsertCreditPlus->SetFieldSize(g_IntroButtonHeight, g_IntroButtonWidth / 4);
	m_InsertCreditPlus->SetText(g_IntroButtonPlus, m_Font, SDL_Color{0x00, 0x00, 0x00, 0xFF});

	m_LabelCredit = new Label(m_Renderer);
	m_LabelCredit->SetText(g_IntroButtonInsertCredit, m_Font, SDL_Color{0x00, 0x00, 0x00, 0xFF});
	m_LabelCredit->SetX(g_IntroLabelCreditX);
	m_LabelCredit->SetY(g_IntroLabelCreditY);
}

void Intro::InitInfo()
{
	m_Info = new Button(m_Renderer);
	m_Info->SetX((g_ScreenWidth - g_IntroButtonWidth) / 2);
	m_Info->SetY(g_IntroFirstButtonY + 3* (g_IntroButtonHeight + 10));
	m_Info->SetFieldSize(g_IntroButtonHeight, g_IntroButtonWidth);
	m_Info->SetText(g_IntroButtonInfo, m_Font, SDL_Color{0x00, 0x00, 0x00, 0xFF});
}

void Intro::InitVolume()
{
	m_VolumePlus = new Button(m_Renderer);
	m_VolumePlus->SetX(g_IntroButtonVolumePlusX);
	m_VolumePlus->SetY(g_IntroFirstButtonY + 4* (g_IntroButtonHeight + 10));
	m_VolumePlus->SetFieldSize(g_IntroButtonHeight, g_IntroButtonWidth / 4);
	m_VolumePlus->SetText(g_IntroButtonPlus, m_Font, SDL_Color{0x00, 0x00, 0x00, 0xFF});

	m_VolumeMinus = new Button(m_Renderer);
	m_VolumeMinus->SetX((g_ScreenWidth - g_IntroButtonWidth) / 2);
	m_VolumeMinus->SetY(g_IntroFirstButtonY + 4* (g_IntroButtonHeight + 10));
	m_VolumeMinus->SetFieldSize(g_IntroButtonHeight, g_IntroButtonWidth / 4);
	m_VolumeMinus->SetText(g_IntroButtonMinus, m_Font, SDL_Color{0x00, 0x00, 0x00, 0xFF});

	m_LabelVolume = new Label(m_Renderer);
	m_LabelVolume->SetText(g_IntroLabelVolume, m_Font, SDL_Color{0x00, 0x00, 0x00, 0xFF});
	m_LabelVolume->SetX(g_IntroLabelButtonX);
	m_LabelVolume->SetY(g_IntroLabelButtonY);
}

void Intro::InitCredits()
{
	m_LabelCredits = new Label(m_Renderer);
	m_LabelCredits->SetText(g_IntroLabelCredits, m_Font, SDL_Color{0x00, 0x00, 0x00, 0xFF});
	m_LabelCredits->SetX(g_ScreenWidth - g_IntroCreditsWidth + (g_IntroCreditsWidth - m_LabelCredits->GetWidth()) / 2);
	m_LabelCredits->SetY(g_ScreenHeight - g_IntroCreditsHeight - m_LabelCredits->GetHeight());

	m_TextFieldCredits = new TextField(m_Renderer);
	m_TextFieldCredits->SetX(g_ScreenWidth - g_IntroCreditsWidth);
	m_TextFieldCredits->SetY(g_ScreenHeight - g_IntroCreditsHeight);
	m_TextFieldCredits->SetFieldSize(g_IntroCreditsHeight, g_IntroCreditsWidth);
	UpdateCredits();
}

void Intro::UpdateCredits()
{
	std::stringstream ss;
	std::string tempStr;

	ss << m_uiCredit;
	tempStr = ss.str();

	m_TextFieldCredits->SetText(tempStr, m_Font, SDL_Color{0xFF, 0xFF, 0xFF, 0xFF});
}













