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
#include "Info.h"

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

	TTF_Font* m_Font;

	Button* m_ButtonStart;
	Button* m_ButtonResume;

	Label* m_LabelCredit;
	Button* m_ButtonCreditPlus;
	Button* m_ButtonCreditMinus;

	Button* m_ButtonInfo;

	Label* m_LabelVolume;
	Button* m_ButtonVolumePlus;
	Button* m_ButtonVolumeMinus;

	Label* m_LabelCredits;
	TextField* m_TextFieldCredits;

	Mix_Music* m_BackgroundSound;
	int m_iVolume;

	Info* m_Info;
	bool m_bShowInfo;
};

#endif /* INTRO_H_ */
