/*
 * Label.cpp
 *
 *  Created on: Jul 10, 2017
 *      Author: Ivan
 */

#include "Label.h"

Label::Label(int height, int width)
{
	m_iHeight = height;
	m_iWidth = width;
}

Label::~Label()
{

}

int Label::getHeight()
{
	return m_iHeight;
}

int Label::getWidth()
{
	return m_iWidth;
}

void Label::Create(SDL_Renderer*, string& allocator, TTF_Font*)
{
	// TODO code here
}

void Label::Render(SDL_Renderer*, int x, int y)
{
	// TODO code here
}
