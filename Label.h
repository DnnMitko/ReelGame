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
	// Constructors, destructor and operators
	Label(int = 0, int = 0);
	virtual ~Label();

public:
	// Public functions
	virtual int getHeight();
	virtual int getWidth();

	// Generate texture from text and font
	void Create(SDL_Renderer*, string &, TTF_Font*);

	// Render texture on given coordinates
	virtual void Render(SDL_Renderer*, int, int);

private:
	// Private functions

private:
	// Private variables
	int m_iHeight;
	int m_iWidth;
//	SDL_Texture* labelTexture;
};

#endif /* LABEL_H_ */
