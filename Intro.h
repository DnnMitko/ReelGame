/*
 * Intro.h
 *
 *  Created on: Jul 11, 2017
 *      Author: polia
 */

#ifndef INTRO_H_
#define INTRO_H_
#include<SDL2/SDL.h>
#include<iostream>
#include<SDL2/SDL_image.h>
class Intro
{
public:
	Intro();
	virtual ~Intro();
	void Render();
	void RenderInit(SDL_Renderer*);
	void EventHandle(SDL_Event& );
	bool isFlag() const;
	bool isSwitch() const;
	void setSwitch(bool bSwitch);
	unsigned int getUiCredit() const;

private:
	unsigned int m_uiCredit;
	bool m_bSwitch;
	// m_bFlag  true = start , false = resume;
	bool m_bFlag;
	SDL_Texture* TextureBackground;
};

#endif /* INTRO_H_ */
