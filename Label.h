/*
 * Label.h
 *
 *  Created on: Jul 10, 2017
 *      Author: Ivan
 */

#ifndef LABEL_H_
#define LABEL_H_

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <string>

using namespace std;

class Label
{

public:

	Label();
	virtual ~Label();

public:

	virtual int GetHeight();
	virtual int GetWidth();
	void Create(SDL_Renderer*, string &, TTF_Font*);
	virtual void Render(SDL_Renderer*, int, int);
	void Destroy();

private:

private:

	int m_iHeight;
	int m_iWidth;
	SDL_Texture* m_texture;

};

#endif /* LABEL_H_ */
