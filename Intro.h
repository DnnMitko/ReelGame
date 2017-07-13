#ifndef INTRO_H_
#define INTRO_H_

#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<SDL2/SDL_ttf.h>
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

	void EventHandler(SDL_Event&);

	void Destroy();
private:
	void ReleaseAllButton();
private:
	unsigned int m_uiCredit;

	SDL_Texture* m_TextureBackground;

	Button* m_StartGame;
	Button* m_ResumeGame;
	Button* m_InsertCredit;
	Button* m_Info;

	TTF_Font* m_Font;

	//TODO add button textf..credit
};

#endif /* INTRO_H_ */
