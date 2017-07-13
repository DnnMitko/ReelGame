#ifndef LABEL_H_
#define LABEL_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <iostream>

class Label
{
public:
	Label();
	Label(SDL_Renderer*);
	virtual ~Label();
public:
	virtual int GetWidth() const;
	virtual int GetHeight() const;

	virtual void SetX(int);
	virtual void SetY(int);

	virtual void RenderForce();
	virtual void RenderSmart();

	void SetText(std::string, TTF_Font*, SDL_Color);
protected:
	SDL_Renderer* m_Renderer;

	SDL_Rect m_TextRect;

	SDL_Texture* m_TextureText;

	bool m_bHasChanged;
};

#endif /* LABEL_H_ */
