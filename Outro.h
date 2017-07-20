#ifndef OUTRO_H_
#define OUTRO_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <sstream>
#include "State.h"
#include "Button.h"
#include "Constants.h"

class Outro : public State
{
public:
	Outro();
	Outro(SDL_Renderer*);
	virtual ~Outro();
public:
	void EventHandler(SDL_Event&);
	void Render(bool = true);
	void PrepTransitionIn();

	void SetCredits(unsigned int);
private:
	void NullAll();

	void TransitionIn();
	void TransitionOut();
private:
	SDL_Texture* m_TextureBackground;
	Label* m_LabelWinSign;
	TextField* m_TextFieldMoney;

	TTF_Font* m_FontMoney;
	TTF_Font* m_FontTitle;

	float m_fCashOutAmmount;

	Uint32 m_uiTimer;

	int m_iX;
	int m_iY;
};

#endif /* OUTRO_H_ */
