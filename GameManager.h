#ifndef GAMEMANAGER_H_
#define GAMEMANAGER_H_

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include "Constants.h"
#include "Button.h"
#include "Intro.h"
#include "Outro.h"
#include "Win.h"
#include "Game.h"
#include "BonusGame.h"
#include "pugixml.hpp"


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

	void Save();
	void SaveIntro();
	void SaveGame();
	void SaveWin();
	void SaveBonusGame();
	void SaveOutro();

	void RenderIntro();
	void RenderGame();
	void RenderWin();
	void RenderBonusGame();
	void RenderOutro();
private:
	SDL_Window* m_Window;
	SDL_Renderer* m_Renderer;

	pugi::xml_document* m_SaveXML;

	bool m_bQuit;

	States m_CurrentState;

	Intro* m_Intro;
	Game* m_Game;
	Win* m_Win;
	BonusGame* m_BonusGame;
	Outro* m_Outro;
};

#endif /* GAMEMANAGER_H_ */
