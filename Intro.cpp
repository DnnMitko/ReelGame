/*
 * Intro.cpp
 *
 *  Created on: Jul 11, 2017
 *      Author: polia
 */

#include "Intro.h"

Intro::Intro()
{
	// TODO Auto-generated constructor stub

}

Intro::~Intro()
{
	// TODO Auto-generated destructor stub
}

bool Intro::isFlag() const
{
	return m_bFlag;
}

bool Intro::isSwitch() const
{
	return m_bSwitch;
}

void Intro::setSwitch(bool bSwitch)
{
	m_bSwitch = bSwitch;
}

void Intro::Render()
{
}

void Intro::RenderInit(SDL_Renderer* Renderer)
{
	TextureBackground = IMG_LoadTexture(Renderer,"TitleScreen");
	if ( TextureBackground == NULL)
		std::cerr << "Problem to load TextureBackground";
}

void Intro::EventHandle(SDL_Event& e)
{
}

unsigned int Intro::getUiCredit() const
{
	return m_uiCredit;
}
