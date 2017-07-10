#ifndef GAMEMANAGER_H_
#define GAMEMANAGER_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <cstdio>

#include "Constants.h"

class GameManager
{
public:
	GameManager();
	~GameManager();
public:
	void eventHandler(SDL_Event&);
	bool getQuit() const;
	void render();
private:
	bool init();
	void close();
private:
	SDL_Window* m_Window;
	SDL_Renderer* m_Renderer;

	bool m_bQuit;

	// TODO Add Game, BonusGame, Intro, Outro objects
};

#endif /* GAMEMANAGER_H_ */
