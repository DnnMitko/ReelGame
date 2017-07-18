#ifndef INTRO_H_
#define INTRO_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <sstream>
#include "State.h"
#include "Button.h"

class Intro : public State
{
public:
	Intro();
	Intro(SDL_Renderer*);
	~Intro();
public:
	void Render(bool = true);
	void EventHandler(SDL_Event&);
	unsigned int GetCredits() const;
private:
	void ReleaseAll();

	void NullAll();

	void InitStartGame();
	void InitResumeGame();
	void InitInsertCredit();
	void InitInfo();
	void InitVolume();

	void InitCredits();
	void UpdateCredits();
private:
	unsigned int m_uiCredit;

	SDL_Texture* m_TextureBackground;

	Button* m_StartGame;
	Button* m_ResumeGame;
	Button* m_InsertCredit;
	Button* m_Info;
	Button* m_VolumePlus;
	Button* m_VolumeMinus;

	TTF_Font* m_Font;

	Label* m_LabelVolume;

	Label* m_LabelCredits;
	TextField* m_TextFieldCredits;
};

#endif /* INTRO_H_ */
