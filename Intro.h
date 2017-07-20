#ifndef INTRO_H_
#define INTRO_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
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
	void PrepTransitionIn();

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
	int m_uiCredit;
	int m_uiCounterVolume;

	SDL_Texture* m_TextureBackground;

	Button* m_StartGame;
	Button* m_ResumeGame;
	Button* m_InsertCreditPlus;
	Button* m_InsertCreditMinus;
	Button* m_Info;
	Button* m_VolumePlus;
	Button* m_VolumeMinus;

	TTF_Font* m_Font;

	Label* m_LabelVolume;
	Label* m_LabelCredit;

	Label* m_LabelCredits;
	TextField* m_TextFieldCredits;

	static Mix_Chunk* m_BackgroundSound;
};

#endif /* INTRO_H_ */
