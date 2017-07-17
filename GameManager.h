#ifndef GAMEMANAGER_H_
#define GAMEMANAGER_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>
#include "Constants.h"
#include "Button.h"
#include "Intro.h"
#include "Outro.h"
#include "Win.h"
#include "Game.h"
#include "BonusGame.h"


class GameManager
{
enum States{ INTRO, GAME, WIN, BONUSGAME, OUTRO };

public:
	GameManager();
	~GameManager();
public:
	void EventHandler(SDL_Event&);
	bool GetQuit() const;
	void Render();
private:
	bool InitSDL();
	void Create();
private:
	SDL_Window* m_Window;
	SDL_Renderer* m_Renderer;

	bool m_bQuit;

	States m_CurrentState;

	Intro* m_Intro;
	Game* m_Game;
	Win* m_Win;
	BonusGame* m_BonusGame;
	Outro* m_Outro;
};

#endif /* GAMEMANAGER_H_ */
