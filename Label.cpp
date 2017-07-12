/*
 * Label.cpp
 *
 *  Created on: Jul 10, 2017
 *      Author: Ivan
 */

#include "Label.h"

Label::Label()
{
	m_texture = NULL;
	m_iHeight = 0;
	m_iWidth = 0;
}

Label::~Label()
{
	Destroy();
}

int Label::GetHeight()
{
	return m_iHeight;
}

int Label::GetWidth()
{
	return m_iWidth;
}

void Label::Create(SDL_Renderer* renderer, string& text, TTF_Font* font)
{
	// TODO code here
}

void Label::Render(SDL_Renderer* renderer, int x, int y)
{
	SDL_Rect rect;
	rect.x = x;
	rect.y = y;
	rect.w = m_iWidth;
	rect.h = m_iHeight;

	SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
	SDL_RenderCopy(renderer, m_texture, NULL, &rect);
}

void Label::Destroy()
{
	SDL_DestroyTexture(m_texture);
	m_texture = NULL;
	m_iWidth = 0;
	m_iHeight = 0;
}
