#ifndef GAMEMANAGER_H_
#define GAMEMANAGER_H_

#include <SDL2/SDL.h>
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
/**
 * State tracking enum.
 */
enum States{ INTRO, GAME, WIN, BONUSGAME, OUTRO };

public:
	/**
	 * Constructor, initializes SDL and
	 * allocates states.
	 */
	GameManager();

	/**
	 * Quits SDL and frees memory.
	 */
	~GameManager();
public:
	/**
	 * Method for handling events.
	 */
	void EventHandler(SDL_Event&);

	/**
	 * Check if the game is over.
	 */
	bool GetQuit() const;

	/**
	 * Render method for drawing on screen.
	 */
	void Render();
private:
	/**
	 * Initializes SDL.
	 */
	bool InitSDL();

	/**
	 * Allocates memory for all states.
	 */
	void Create();

	/**
	 * Saves the current information of the game.
	 */
	void Save();

	/**
	 * Loads game information from the save.
	 */
	void Load();

	/**
	 * Deletes save.
	 */
	void DeleteSave();

	/**
	 * Processes saving from the intro state.
	 */
	void SaveIntro();

	/**
	 * Processes saving from the game state.
	 */
	void SaveGame();

	/**
	 * Processes saving from the win state.
	 */
	void SaveWin();

	/**
	 * Processes saving from the bonus game state.
	 */
	void SaveBonusGame();

	/**
	 * Processes saving from the outro state.
	 */
	void SaveOutro();

	/**
	 * Render Intro and check if it's ready to switch.
	 */
	void RenderIntro();

	/**
	 * Render Game and check if it's ready to switch.
	 */
	void RenderGame();

	/**
	 * Render Win and check if it's ready to switch.
	 */
	void RenderWin();

	/**
	 * Render BonusGame and check if it's ready to switch.
	 */
	void RenderBonusGame();

	/**
	 * Render Outro and check if it's ready to switch.
	 */
	void RenderOutro();
private:
	/**
	 * Window variable from SDL.
	 */
	SDL_Window* m_Window;

	/**
	 * Renderer used for the program.
	 */
	SDL_Renderer* m_Renderer;

	/**
	 * XML save file.
	 */
	pugi::xml_document* m_SaveXML;

	/**
	 * Flag for tracking if we're ready to quit the game.
	 */
	bool m_bQuit;

	/**
	 * Current state tracker.
	 */
	States m_CurrentState;

	/**
	 * Intro state object.
	 */
	Intro* m_Intro;

	/**
	 * Game state object.
	 */
	Game* m_Game;

	/**
	 * Win state object.
	 */
	Win* m_Win;

	/**
	 * BonusGame state object.
	 */
	BonusGame* m_BonusGame;

	/**
	 * Outro state object.
	 */
	Outro* m_Outro;
};

#endif /* GAMEMANAGER_H_ */
