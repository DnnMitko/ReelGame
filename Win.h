#ifndef WIN_H_
#define WIN_H_

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include <sstream>
#include "State.h"
#include "Button.h"
#include "Constants.h"

class Win : public State
{
public:
	Win();
	Win(SDL_Renderer*);
	virtual ~Win();
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

#endif /* WIN_H_ */
