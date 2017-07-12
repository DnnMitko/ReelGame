#ifndef OUTRO_H_
#define OUTRO_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <ctime>
#include "State.h"


class Outro : public State
{
public:
	Outro(SDL_Renderer*);
	~Outro();
public:
	void RenderSmart(); // umen render(prerisuva samo promenenoto)
	void RenderForce(); //vsichko,koeto ima v klasa se risuva

	void EventHandler(SDL_Event&);

	void Destroy();

	void CashOut(unsigned int);
private:
	SDL_Texture* m_TextureBackground; //suhranqvame kartinkata,koqto sum izbral
	SDL_Texture* m_TextureWin;// winovete big,super,mega

	//TODO textfield

	SDL_Rect m_PositionBackground;
};

#endif /* OUTRO_H_ */
