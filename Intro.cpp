#include "Intro.h"

Intro::Intro(SDL_Renderer* newRenderer) : State()
{
	m_uiCredit = 0;

	SetRenderer(newRenderer);

	m_TextureBackground = NULL;
	m_TextureBackground = IMG_LoadTexture(m_Renderer, "images/TitleScreen.png");
	if( m_TextureBackground == NULL )
		std::cerr << "Failed to load TextureBackground! SDL Error: " << IMG_GetError() << std::endl;

	m_StartGame = new Button(m_Renderer);
	m_ResumeGame = new Button(m_Renderer);
	m_InsertCredit = new Button(m_Renderer);
	m_Info = new Button(m_Renderer);

	m_Font = TTF_OpenFont(g_LabelFont, g_IntroFontSize);

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
	Destroy();
}

void Intro::RenderSmart()
{
	m_StartGame->RenderSmart();
	m_ResumeGame->RenderSmart();
	m_InsertCredit->RenderSmart();
	m_Info->RenderSmart();
}

void Intro::RenderForce()
{
	m_uiCredit = 0;

	SDL_RenderCopy(m_Renderer, m_TextureBackground, NULL, NULL);

	m_StartGame->RenderForce();
	m_ResumeGame->RenderForce();
	m_InsertCredit->RenderForce();
	m_Info->RenderForce();

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

void Intro::Destroy()
{
	SDL_DestroyTexture(m_TextureBackground);
	m_TextureBackground = NULL;

	delete m_StartGame;
	delete m_ResumeGame;
	delete m_InsertCredit;
	delete m_Info;

}

void Intro::ReleaseAllButton()
{
	m_StartGame->Release();
	m_ResumeGame->Release();
	m_InsertCredit->Release();
	m_Info->Release();
}
