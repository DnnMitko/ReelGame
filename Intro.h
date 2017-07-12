#ifndef INTRO_H_
#define INTRO_H_

#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<iostream>
#include"State.h"
#include"Button.h"

class Intro : public State
{
public:
	Intro(SDL_Renderer*);
	~Intro();
public:
	void RenderSmart();
	void RenderForce();

	void EventHandle(SDL_Event&);

	void Destroy();
private:
	void ReleaseAllButton();
private:
	unsigned int m_uiCredit;

	SDL_Texture* m_TextureBackground;

//	SDL_Texture* m_TextureButtonStartGame;
//	SDL_Texture* m_TextureButtonResumeGame;
//	SDL_Texture* m_TextureButonCashOut;
//	SDL_Texture* m_TextureButtonInsertCredit;
//	SDL_Texture* m_TextureButtonInfo;

	//TODO add button textf..credit
};

#endif /* INTRO_H_ */
