#include "Intro.h"

Intro::Intro(SDL_Renderer* newRenderer) : State()
{
	SetRenderer(newRenderer);

	m_TextureBackground = NULL;
	m_TextureBackground = IMG_LoadTexture(m_Renderer, "images/TitleScreen.png");
	if( m_TextureBackground == NULL )
		std::cerr << "Failed to load TextureBackground! SDL Error: " << IMG_GetError() << std::endl;

	//TODO make buttons make text
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

	//TODO button1.RenderForce button2.RenderForce() ....  text.renderforse()
}

void Intro::EventHandle(SDL_Event& e)
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
