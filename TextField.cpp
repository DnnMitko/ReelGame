#include "TextField.h"

TextField::TextField() : Label()
{
	m_FieldRect.x = 0;
	m_FieldRect.y = 0;
	m_FieldRect.w = 0;
	m_FieldRect.h = 0;
}

TextField::TextField(SDL_Renderer* newRenderer) : Label(newRenderer)
{
	m_FieldRect.x = 0;
	m_FieldRect.y = 0;
	m_FieldRect.w = 0;
	m_FieldRect.h = 0;
}

TextField::~TextField()
{
}

int TextField::GetWidth() const
{
	return m_FieldRect.w;
}

int TextField::GetHeight() const
{
	return m_FieldRect.h;
}

void TextField::SetX(int newX)
{
	m_FieldRect.x = newX;

	m_bHasChanged = true;
}

void TextField::SetY(int newY)
{
	m_FieldRect.y = newY;

	m_bHasChanged = true;
}

void TextField::Render(bool UpdateOnly)
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

		SDL_SetRenderDrawColor(m_Renderer, 0x00, 0x00, 0x00, 0xFF);
		SDL_RenderFillRect(m_Renderer, &m_FieldRect);

		SDL_SetRenderDrawColor(m_Renderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderDrawRect(m_Renderer, &m_FieldRect);

		m_TextRect.x = m_FieldRect.x + (m_FieldRect.w - m_TextRect.w) / 2;
		m_TextRect.y = m_FieldRect.y + (m_FieldRect.h - m_TextRect.h) / 2;

		SDL_RenderCopy(m_Renderer, m_TextureText, NULL, &m_TextRect);
	}
}

void TextField::SetText(std::string newText, TTF_Font* font, SDL_Color color)
{
	Label::SetText(newText, font, color);
}

void TextField::SetFieldSize(int newH, int newW)
{
	m_FieldRect.h = newH;
	m_FieldRect.w = newW;

	m_bHasChanged = true;
}
