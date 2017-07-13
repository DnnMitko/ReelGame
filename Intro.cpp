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

	m_Font = TTF_OpenFont(g_LabelFont,g_IntroFontSize);

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

	m_StartGame->SetY(300);

}

Intro::~Intro()
{
	Destroy();
}

void Intro::RenderSmart()
{
	// TODO button1.renderSmart() , button2.renderSmart() ....text.rendersmart()
}

void Intro::RenderForce()
{
	SDL_RenderCopy(m_Renderer, m_TextureBackground, NULL, NULL);

	m_StartGame->RenderForce();
	// m_ResumeGame->RenderForce();

	//TODO button1.RenderForce button2.RenderForce() ....  text.renderforse()
}

void Intro::EventHandler(SDL_Event& e)
{
	int x;
	int y;
	SDL_GetMouseState(&x, &y);
	if(e.type == SDL_MOUSEBUTTONDOWN)
	{
		// TODO if (button1.IsIn(x, y) button1.press(); else if (button2.IsIn(x,y) ....
	}
	else if (e.type == SDL_MOUSEBUTTONUP)
	{
		// TODO if (button1.IsIn(x, y) && button1.isPressed() ) { button1.release(); button1.Deistvie() } else if button2..

		ReleaseAllButton();
	}

}

void Intro::Destroy()
{
	SDL_DestroyTexture(m_TextureBackground);
	m_TextureBackground = NULL;

	//TODO destroy buttons
}

void Intro::ReleaseAllButton()
{
	//TODO button1.release(); ...
}
