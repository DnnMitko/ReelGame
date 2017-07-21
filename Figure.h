#ifndef FIGURE_H_
#define FIGURE_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <cstdlib>

#include "Constants.h"

class Figure
{
public:
	Figure();
	Figure(SDL_Renderer*);
	~Figure();
public:
	void SetX(int);
	void SetY(int);
	void Render(bool);
	void Play();
	void Pause();
	void Rand();
	void MakeSpacial();
	char GetCurFigure() const;
private:
	void Clear();
private:
	SDL_Renderer* m_Renderer;
	static SDL_Texture* m_TextureFigures;
	static SDL_Texture* m_TextureBackground;
	SDL_Rect m_RectFigure;

	int m_iX;
	int m_iY;

	char m_cCurFigure;

	bool m_bIsAnimated;

	Uint32 m_uiTimer;
};





#endif /* FIGURE_H_ */
