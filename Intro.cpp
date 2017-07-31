#include "Intro.h"

Intro::Intro() : State()
{
	NullAll();
}

Intro::Intro(SDL_Renderer* newRenderer) : State(newRenderer)
{
	m_uiCredit = 0;

	m_bShowInfo = false;
	m_bResume = false;

	m_TextureBackground = NULL;
	m_TextureBackground = IMG_LoadTexture(m_Renderer, "images/TitleScreen.png");
	if( m_TextureBackground == NULL )
		std::cerr << "Failed to load TextureBackground! SDL Error: " << IMG_GetError() << std::endl;

	m_Font = TTF_OpenFont(g_FontLabel, g_IntroFontSize);
	if( m_Font == NULL )
		std::cerr << "Failed to load Label Font! SDL Error: " << IMG_GetError() << std::endl;

	m_iY = g_IntroFirstButtonY;

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

	delete m_ButtonStart;
	delete m_ButtonResume;

	delete m_LabelCredit;
	delete m_ButtonCreditMinus;
	delete m_ButtonCreditPlus;

	delete m_ButtonInfo;

	delete m_LabelVolume;
	delete m_ButtonVolumePlus;
	delete m_ButtonVolumeMinus;

	delete m_LabelCredits;
	delete m_TextFieldCredits;

	delete m_Info;

	NullAll();
}

void Intro::Render(bool UpdateOnly)
{
	if(!m_Renderer || !m_TextureBackground || !m_Font)
		return;

	if(m_bTransitionIn)
		TransitionIn();
	else if(m_bTransitionOut)
		TransitionOut();

	if(m_bTransitionIn || m_bTransitionOut)
		UpdateOnly = false;

	if(!UpdateOnly)
		SDL_RenderCopy(m_Renderer, m_TextureBackground, NULL, NULL);

	m_ButtonStart->Render(UpdateOnly);
	m_ButtonResume->Render(UpdateOnly);

	m_LabelCredit->Render(UpdateOnly);
	m_ButtonCreditMinus->Render(UpdateOnly);
	m_ButtonCreditPlus->Render(UpdateOnly);

	m_ButtonInfo->Render(UpdateOnly);

	m_LabelVolume->Render(UpdateOnly);
	m_ButtonVolumePlus->Render(UpdateOnly);
	m_ButtonVolumeMinus->Render(UpdateOnly);

	m_LabelCredits->Render(UpdateOnly);
	m_TextFieldCredits->Render(UpdateOnly);

	if(m_bShowInfo)
		m_Info->Render(UpdateOnly);
}

void Intro::EventHandler(SDL_Event& e)
{
	if(m_bTransitionIn || m_bTransitionOut)
		return;

	int x;
	int y;

	if(m_bShowInfo)
	{
		m_Info->EventHandler(e);

		if(m_Info->GetHide())
		{
			m_Info->Reset();
			m_bShowInfo = false;

			Render(false);
		}
	}
	else if(e.type == SDL_MOUSEBUTTONDOWN)
	{
		SDL_GetMouseState(&x, &y);

		if (m_ButtonStart->IsIn(x, y) && m_uiCredit > 0)
			m_ButtonStart->Press();
		else if (m_ButtonResume->IsIn(x, y))
			m_ButtonResume->Press();
		else if (m_ButtonCreditPlus->IsIn(x, y))
			m_ButtonCreditPlus->Press();
		else if (m_ButtonCreditMinus->IsIn(x,y) && m_uiCredit != 0)
			m_ButtonCreditMinus->Press();
		else if (m_ButtonInfo->IsIn(x, y))
			m_ButtonInfo->Press();
		else if (m_ButtonVolumePlus->IsIn(x, y))
			m_ButtonVolumePlus->Press();
		else if (m_ButtonVolumeMinus->IsIn(x,y)&& m_iVolume != 0)
			m_ButtonVolumeMinus->Press();
	}
	else if (e.type == SDL_MOUSEBUTTONUP)
	{
		SDL_GetMouseState(&x, &y);

		if(m_ButtonStart->IsIn(x, y) && m_ButtonStart->IsPressed())
		{
			m_bTransitionOut = true;
		}

		else if(m_ButtonResume->IsIn(x, y) && m_ButtonResume->IsPressed())
		{
			m_bTransitionOut = true;
			m_bResume = true;
		}

		else if(m_ButtonCreditPlus->IsIn(x, y) && m_ButtonCreditPlus->IsPressed())
		{
			m_uiCredit += g_IntroCreditIncrement;
			UpdateCredits();
		}
		else if(m_ButtonCreditMinus->IsIn(x,y) && m_ButtonCreditMinus->IsPressed())
		{
			if(m_uiCredit > 0)
			{
				m_uiCredit -= g_IntroCreditIncrement;
				UpdateCredits();
			}
		}
		else if(m_ButtonInfo->IsIn(x,y) && m_ButtonInfo->IsPressed())
		{
			m_bShowInfo = true;
		}
		else if (m_ButtonVolumePlus->IsIn(x, y) && m_ButtonVolumePlus->IsPressed())
		{
			if(m_iVolume < 128)
			{
				m_iVolume += g_IntroVolumeIncrement;
				Mix_Volume(-1, m_iVolume);
				Mix_VolumeMusic(m_iVolume);
			}
		}
		else if (m_ButtonVolumeMinus->IsIn(x, y) && m_ButtonVolumeMinus->IsPressed())
		{
			if(m_iVolume > 0)
			{
				m_iVolume -= g_IntroVolumeIncrement;
				Mix_Volume(-1, m_iVolume);
				Mix_VolumeMusic(m_iVolume);
			}
		}

		ReleaseAll();
	}
}

void Intro::PrepTransitionIn()
{
	m_bTransitionIn = true;

	m_iY = g_ScreenWidth;
	Reposition();

	m_uiCredit = 0;
	UpdateCredits();
}

unsigned int Intro::GetCredits() const
{
	return m_uiCredit;
}

bool Intro::GetResume() const
{
	return m_bResume;
}

void Intro::ResetResume()
{
	m_bResume = false;
}

void Intro::ReleaseAll()
{
	m_ButtonStart->Release();
	m_ButtonResume->Release();
	m_ButtonCreditPlus->Release();
	m_ButtonCreditMinus->Release();
	m_ButtonInfo->Release();
	m_ButtonVolumePlus->Release();
	m_ButtonVolumeMinus->Release();
}

void Intro::NullAll()
{
	m_uiCredit = 0;

	m_bResume = false;

	m_TextureBackground = NULL;

	m_Font = NULL;

	m_ButtonStart = NULL;
	m_ButtonResume = NULL;

	m_LabelCredit = NULL;
	m_ButtonCreditPlus = NULL;
	m_ButtonCreditMinus = NULL;

	m_ButtonInfo = NULL;

	m_LabelVolume = NULL;
	m_ButtonVolumePlus = NULL;
	m_ButtonVolumeMinus = NULL;

	m_LabelCredits = NULL;
	m_TextFieldCredits = NULL;

	m_BackgroundSound = NULL;
	m_iVolume = 0;

	m_Info = NULL;
	m_bShowInfo = false;
}

void Intro::InitStartGame()
{
	m_ButtonStart = new Button(m_Renderer);
	m_ButtonStart->SetX((g_ScreenWidth - g_IntroButtonWidth) / 2);
	m_ButtonStart->SetY(m_iY);
	m_ButtonStart->SetFieldSize(g_IntroButtonHeight, g_IntroButtonWidth);
	m_ButtonStart->SetText(g_IntroButtonNewGame, m_Font, g_ColorBlack);
}

void Intro::InitResumeGame()
{
	m_ButtonResume = new Button(m_Renderer);
	m_ButtonResume->SetX((g_ScreenWidth - g_IntroButtonWidth) / 2);
	m_ButtonResume->SetY(m_iY + g_IntroButtonHeight + g_IntroButtonMargin);
	m_ButtonResume->SetFieldSize(g_IntroButtonHeight, g_IntroButtonWidth);
	m_ButtonResume->SetText(g_IntroButtonResumeGame, m_Font, g_ColorBlack);
}

void Intro::InitInsertCredit()
{
	m_ButtonCreditMinus = new Button(m_Renderer);
	m_ButtonCreditMinus->SetX((g_ScreenWidth - g_IntroButtonWidth) / 2);
	m_ButtonCreditMinus->SetY(m_iY + 2 * (g_IntroButtonHeight + g_IntroButtonMargin));
	m_ButtonCreditMinus->SetFieldSize(g_IntroButtonHeight, g_IntroButtonWidth / 4);
	m_ButtonCreditMinus->SetText(g_IntroButtonMinus, m_Font, g_ColorBlack);

	m_ButtonCreditPlus = new Button(m_Renderer);
	m_ButtonCreditPlus->SetX((g_ScreenWidth - g_IntroButtonWidth) / 2 + g_IntroButtonWidth - g_IntroButtonWidth / 4);
	m_ButtonCreditPlus->SetY(m_iY + 2 * (g_IntroButtonHeight + g_IntroButtonMargin));
	m_ButtonCreditPlus->SetFieldSize(g_IntroButtonHeight, g_IntroButtonWidth / 4);
	m_ButtonCreditPlus->SetText(g_IntroButtonPlus, m_Font, g_ColorBlack);

	m_LabelCredit = new Label(m_Renderer);
	m_LabelCredit->SetText(g_IntroLabelInsertCredit, m_Font, g_ColorBlack);
	m_LabelCredit->SetX((g_ScreenWidth - m_LabelCredit->GetWidth()) / 2);
	m_LabelCredit->SetY(m_iY + 2 * (g_IntroButtonHeight + g_IntroButtonMargin)
						+ (g_IntroButtonHeight - m_LabelCredit->GetHeight()) / 2);
}

void Intro::InitInfo()
{
	m_ButtonInfo = new Button(m_Renderer);
	m_ButtonInfo->SetX((g_ScreenWidth - g_IntroButtonWidth) / 2);
	m_ButtonInfo->SetY(m_iY + 3* (g_IntroButtonHeight + g_IntroButtonMargin));
	m_ButtonInfo->SetFieldSize(g_IntroButtonHeight, g_IntroButtonWidth);
	m_ButtonInfo->SetText(g_IntroButtonInfo, m_Font, g_ColorBlack);

	m_Info = new Info(m_Renderer);
}

void Intro::InitVolume()
{
	m_BackgroundSound = Mix_LoadMUS(g_BackgroundSound);
	if(!m_BackgroundSound)
		std::cerr << "Failed to load Background music! SDL_mixer Error: " << Mix_GetError() << "\n";
	else
	{
		Mix_PlayMusic(m_BackgroundSound, -1);
		m_iVolume = g_IntroVolumeStart;
		Mix_Volume(-1, m_iVolume);
		Mix_VolumeMusic(m_iVolume);
	}

	m_ButtonVolumePlus = new Button(m_Renderer);
	m_ButtonVolumePlus->SetX((g_ScreenWidth - g_IntroButtonWidth) / 2 + g_IntroButtonWidth - g_IntroButtonWidth / 4);
	m_ButtonVolumePlus->SetY(m_iY + 4 * (g_IntroButtonHeight + g_IntroButtonMargin));
	m_ButtonVolumePlus->SetFieldSize(g_IntroButtonHeight, g_IntroButtonWidth / 4);
	m_ButtonVolumePlus->SetText(g_IntroButtonPlus, m_Font, g_ColorBlack);

	m_ButtonVolumeMinus = new Button(m_Renderer);
	m_ButtonVolumeMinus->SetX((g_ScreenWidth - g_IntroButtonWidth) / 2);
	m_ButtonVolumeMinus->SetY(m_iY + 4 * (g_IntroButtonHeight + g_IntroButtonMargin));
	m_ButtonVolumeMinus->SetFieldSize(g_IntroButtonHeight, g_IntroButtonWidth / 4);
	m_ButtonVolumeMinus->SetText(g_IntroButtonMinus, m_Font, g_ColorBlack);

	m_LabelVolume = new Label(m_Renderer);
	m_LabelVolume->SetText(g_IntroLabelVolume, m_Font, g_ColorBlack);
	m_LabelVolume->SetX((g_ScreenWidth - m_LabelVolume->GetWidth()) / 2);
	m_LabelVolume->SetY(m_iY + 4 * (g_IntroButtonHeight + g_IntroButtonMargin)
						+ (g_IntroButtonHeight - m_LabelCredit->GetHeight()) / 2);
}

void Intro::InitCredits()
{
	m_LabelCredits = new Label(m_Renderer);
	m_LabelCredits->SetText(g_IntroLabelCredits, m_Font, g_ColorBlack);
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

	m_TextFieldCredits->SetText(tempStr, m_Font, g_ColorWhite);
}

void Intro::TransitionIn()
{
	if(m_iY == g_IntroFirstButtonY)
		m_bTransitionIn = false;
	else
	{
		m_iY -= g_TransitionStep;

		Reposition();
	}
}

void Intro::TransitionOut()
{
	if(m_iY >= g_ScreenHeight)
	{
		m_bTransitionOut = false;
		m_bSwitch = true;
	}
	else
	{
		m_iY += g_TransitionStep;

		Reposition();
	}
}

void Intro::Reposition()
{
	m_ButtonStart->SetY(m_iY);

	m_ButtonResume->SetY(m_iY + g_IntroButtonHeight + g_IntroButtonMargin);

	m_ButtonCreditMinus->SetY(m_iY + 2* (g_IntroButtonHeight + g_IntroButtonMargin));
	m_ButtonCreditPlus->SetY(m_iY + 2* (g_IntroButtonHeight + g_IntroButtonMargin));
	m_LabelCredit->SetY(m_iY + 2 * (g_IntroButtonHeight + g_IntroButtonMargin)
						+ (g_IntroButtonHeight - m_LabelCredit->GetHeight()) / 2);

	m_ButtonInfo->SetY(m_iY + 3* (g_IntroButtonHeight + g_IntroButtonMargin));

	m_ButtonVolumePlus->SetY(m_iY + 4* (g_IntroButtonHeight + g_IntroButtonMargin));
	m_ButtonVolumeMinus->SetY(m_iY + 4* (g_IntroButtonHeight + g_IntroButtonMargin));
	m_LabelVolume->SetY(m_iY + 4 * (g_IntroButtonHeight + g_IntroButtonMargin)
						+ (g_IntroButtonHeight - m_LabelCredit->GetHeight()) / 2);
}












