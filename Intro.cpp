#include "Intro.h"

Intro::Intro() : State()
{
	m_uiCredit = 0;

	m_TextureBackground = NULL;

	m_StartGame = NULL;
	m_ResumeGame = NULL;
	m_InsertCredit = NULL;
	m_Info = NULL;

	m_Font = NULL;
}

Intro::Intro(SDL_Renderer* newRenderer) : State(newRenderer)
{
	m_uiCredit = 0;

	m_TextureBackground = NULL;
	m_TextureBackground = IMG_LoadTexture(m_Renderer, "images/TitleScreen.png");
	if( m_TextureBackground == NULL )
		std::cerr << "Failed to load TextureBackground! SDL Error: " << IMG_GetError() << std::endl;

	m_StartGame = new Button(m_Renderer);
	m_ResumeGame = new Button(m_Renderer);
	m_InsertCredit = new Button(m_Renderer);
	m_Info = new Button(m_Renderer);

	m_Font = TTF_OpenFont(g_LabelFont, g_IntroFontSize);
	if( m_Font == NULL )
		std::cerr << "Failed to load Label Font! SDL Error: " << IMG_GetError() << std::endl;

	SDL_Color BlackColor = {0x00, 0x00, 0x00, 0xFF};
	m_StartGame->SetText(g_ButtonNewGame, m_Font, BlackColor);
	m_ResumeGame->SetText(g_ButtonResumeGame, m_Font, BlackColor);
	m_InsertCredit->SetText(g_ButtonInsertCredit, m_Font, BlackColor);
	m_Info->SetText(g_ButtonInfo, m_Font, BlackColor);

	m_StartGame->SetFieldSize(g_IntroButtonHeight, g_IntroButtonWidth);
	m_ResumeGame->SetFieldSize(g_IntroButtonHeight, g_IntroButtonWidth);
	m_InsertCredit->SetFieldSize(g_IntroButtonHeight, g_IntroButtonWidth);
	m_Info->SetFieldSize(g_IntroButtonHeight, g_IntroButtonWidth);

	int x = (g_ScreenWidth - g_IntroButtonWidth) / 2;

	m_StartGame->SetX(x);
	m_ResumeGame->SetX(x);
	m_InsertCredit->SetX(x);
	m_Info->SetX(x);

	m_StartGame->SetY(g_IntroFirstButtonY);
	m_ResumeGame->SetY(g_IntroFirstButtonY + g_IntroButtonHeight + 10);
	m_InsertCredit->SetY(g_IntroFirstButtonY + 2* (g_IntroButtonHeight + 10));
	m_Info->SetY(g_IntroFirstButtonY + 3* (g_IntroButtonHeight + 10));

}

Intro::~Intro()
{
	SDL_DestroyTexture(m_TextureBackground);
	m_TextureBackground = NULL;

	TTF_CloseFont(m_Font);
	m_Font = NULL;

	delete m_StartGame;
	delete m_ResumeGame;
	delete m_InsertCredit;
	delete m_Info;
}

void Intro::Render(bool UpdateOnly)
{
	if(!UpdateOnly)
	{
		m_uiCredit = 0;

		SDL_RenderCopy(m_Renderer, m_TextureBackground, NULL, NULL);
	}

	m_StartGame->Render(UpdateOnly);
	m_ResumeGame->Render(UpdateOnly);
	m_InsertCredit->Render(UpdateOnly);
	m_Info->Render(UpdateOnly);
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

		else if (m_InsertCredit->IsIn(x, y))
			m_InsertCredit->Press();

		else if (m_Info->IsIn(x, y))
			m_Info->Press();
	}
	else if (e.type == SDL_MOUSEBUTTONUP)
	{
		SDL_GetMouseState(&x, &y);
		// TODO if (button1.IsIn(x, y) && button1.isPressed() ) { button1.release(); button1.Deistvie() } else if button2..

		if(m_StartGame->IsIn(x, y) && m_StartGame->IsPressed())
		{
			m_bSwitch = true;
		}

		else if(m_ResumeGame->IsIn(x, y) && m_ResumeGame->IsPressed())
		{
			m_bSwitch = true;
		}

		else if(m_InsertCredit->IsIn(x, y) && m_ResumeGame->IsPressed())
		{
			m_uiCredit += 50;
		}
		else if(m_Info->IsIn(x,y) && m_Info->IsPressed())
		{
			// TODO
		}
		ReleaseAllButton();
	}

}

void Intro::ReleaseAllButton()
{
	m_StartGame->Release();
	m_ResumeGame->Release();
	m_InsertCredit->Release();
	m_Info->Release();
}
