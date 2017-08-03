#include "Button.h"

SDL_Texture* Button::m_TextureButton = NULL;
Mix_Chunk* Button::m_SfxClick = NULL;

Button::Button() : TextField()
{
	m_TextureTextPressed = NULL;

	m_bIsPressed = false;
	m_bEnabled = true;
}

Button::Button(SDL_Renderer* newRenderer) : TextField(newRenderer)
{
	m_TextureTextPressed = NULL;

	m_bIsPressed = false;
	m_bEnabled = true;

	if(!m_TextureButton)
	{
		m_TextureButton = IMG_LoadTexture(m_Renderer, g_ButtonSprite);

		if(m_TextureButton == NULL)
			std::cerr << "Failed to load TextureBackground! SDL Error: " << IMG_GetError() << std::endl;
	}
	if(!m_SfxClick)
	{
		m_SfxClick = Mix_LoadWAV(g_ButtonSound);

		if(!m_SfxClick)
			std::cerr << "Failed to load button sound effect! SDL_mixer Error: " << Mix_GetError() << "\n";
	}
}

Button::~Button()
{
	SDL_DestroyTexture(m_TextureTextPressed);
	m_TextureTextPressed = NULL;

	SDL_DestroyTexture(m_TextureButton);
	m_TextureButton = NULL;

	Mix_FreeChunk(m_SfxClick);
	m_SfxClick = NULL;
}

void Button::Render(bool UpdateOnly)
{
	if(m_Renderer == NULL || m_TextureText == NULL || m_TextureTextPressed == NULL || m_TextureButton == NULL)
		return;

	if(UpdateOnly)
	{
		if(m_bHasChanged)
		{
			m_bHasChanged = false;
			Render(false);
		}
	}
	else
	{
		m_bHasChanged = false;

		SDL_Rect tempRect;
		tempRect.w = g_ButtonSpriteWidth;
		tempRect.h = g_ButtonSpriteHeight;
		tempRect.x = 0;
		if(!m_bEnabled)
			tempRect.y = g_ButtonSpriteHeight * 2;
		else if(m_bIsPressed)
			tempRect.y = g_ButtonSpriteHeight;
		else
			tempRect.y = 0;

		SDL_RenderCopy(m_Renderer, m_TextureButton, &tempRect, &m_FieldRect);

		m_TextRect.x = m_FieldRect.x + (m_FieldRect.w - m_TextRect.w) / 2;
		m_TextRect.y = m_FieldRect.y + (m_FieldRect.h - m_TextRect.h) / 2;

		if(m_bIsPressed)
			SDL_RenderCopy(m_Renderer, m_TextureTextPressed, NULL, &m_TextRect);
		else
			SDL_RenderCopy(m_Renderer, m_TextureText, NULL, &m_TextRect);
	}
}

void Button::SetText(std::string newText, TTF_Font* font, SDL_Color color)
{
	Label::SetText(newText, font, color);

	SDL_DestroyTexture(m_TextureTextPressed);

	SDL_Surface* tempSurface = TTF_RenderText_Blended(font, newText.c_str(), g_ColorWhite);

	m_TextureTextPressed = SDL_CreateTextureFromSurface(m_Renderer, tempSurface);

	if( m_TextureTextPressed == NULL )
	{
		std::cerr << "Unable to create texture from rendered text \"" << newText << "\"! SDL Error: " <<  SDL_GetError() << "\n";
	}

	SDL_FreeSurface(tempSurface);
	tempSurface = NULL;
}

bool Button::IsIn(int x, int y) const
{
	if(x < m_FieldRect.x || x > (m_FieldRect.x + m_FieldRect.w))
		return false;
	else if(y < m_FieldRect.y || y > (m_FieldRect.y + m_FieldRect.h))
		return false;

	return true;
}

void Button::Enable()
{
	m_bEnabled = true;
	m_bHasChanged = true;
}

void Button::Disable()
{
	m_bEnabled = false;
	m_bHasChanged = true;
}

void Button::Press()
{
	if(m_bEnabled)
	{
		m_bIsPressed = true;
		m_bHasChanged =  true;

		Mix_PlayChannel(-1, m_SfxClick, 0);
	}
}

void Button::Release()
{
	if(m_bEnabled)
	{
		m_bIsPressed = false;
		m_bHasChanged = true;
	}
}

bool Button::IsPressed() const
{
	return m_bIsPressed;
}














