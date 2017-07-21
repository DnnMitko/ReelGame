#ifndef INFO_H_
#define INFO_H_

#include <SDL2/SDL.h>
#include "Button.h"

class Info
{
public:
	Info();
	Info(SDL_Renderer*);
	~Info();
public:
	void Render();
	void EventHandler(SDL_Event&);

	bool GetHide() const;

	void Reset();
private:
	SDL_Renderer* m_Rednerer;

	SDL_Texture* m_TextrureScreens[2];

	TTF_Font* m_Font;

	Button* m_ButtonNext;
	Button* m_ButtonExit;

	bool m_bShowFirst;

	bool m_bHide;

	int m_iX;
	int m_iY;
};

#endif /* INFO_H_ */
