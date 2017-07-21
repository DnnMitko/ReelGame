#include "Label.h"

Label::Label()
{
	m_Renderer = NULL;

	m_TextureText = NULL;

	m_TextRect.x = 0;
	m_TextRect.y = 0;
	m_TextRect.w = 0;
	m_TextRect.h = 0;

	m_bHasChanged = true;
}

Label::Label(SDL_Renderer* newRenderer)
{
	m_Renderer = newRenderer;

	m_TextureText = NULL;

	m_TextRect.x = 0;
	m_TextRect.y = 0;
	m_TextRect.w = 0;
	m_TextRect.h = 0;

	m_bHasChanged = true;
}

Label::~Label()
{
	SDL_DestroyTexture(m_TextureText);
	m_TextureText = NULL;
}

int Label::GetWidth() const
{
	return m_TextRect.w;
}

int Label::GetHeight() const
{
	return m_TextRect.h;
}

void Label::SetX(int newX)
{
	m_TextRect.x = newX;

	m_bHasChanged = true;
}

void Label::SetY(int newY)
{
	m_TextRect.y = newY;

	m_bHasChanged = true;
}

void Label::Render(bool UpdateOnly)
{
	if(m_Renderer == NULL || m_TextureText == NULL)
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

		SDL_RenderCopy(m_Renderer, m_TextureText, NULL, &m_TextRect);
	}
}

void Label::SetText(std::string newText, TTF_Font* font, SDL_Color color)
{
	SDL_DestroyTexture(m_TextureText);

	m_bHasChanged = true;

	SDL_Surface* tempSurface = TTF_RenderText_Blended(font, newText.c_str(), color);

	m_TextRect.w = tempSurface->w;
	m_TextRect.h = tempSurface->h;

	m_TextureText = SDL_CreateTextureFromSurface(m_Renderer, tempSurface);

	if(m_TextureText == NULL)
	{
		std::cerr << "Unable to create texture from rendered text \"" << newText << "\"! SDL Error: " <<  SDL_GetError() << "\n";

		m_TextRect.w = 0;
		m_TextRect.h = 0;
	}

	SDL_FreeSurface(tempSurface);
	tempSurface = NULL;
}
























