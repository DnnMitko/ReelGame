#ifndef BONUSGAME_H_
#define BONUSGAME_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <sstream>
#include "State.h"
#include "Button.h"
#include "Constants.h"

class BonusGame : public State
{
public:
	BonusGame();
	BonusGame(SDL_Renderer*);
	virtual ~BonusGame();
public:
	void EventHandler(SDL_Event&);
	void Render(bool = true);
	void SetCredits(unsigned int);
private:
	SDL_Texture* m_TextureBackground;
	Label* m_LabelWinSign;
	TextField* m_TextFieldCredits;
	TTF_Font* m_FontCredits;
	TTF_Font* m_FontWin;

	unsigned int m_uiCredits;
	int m_iX;
	int m_iY;
};

#endif /* BONUSGAME_H_ */
