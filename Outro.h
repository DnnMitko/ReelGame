#ifndef OUTRO_H_
#define OUTRO_H_

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include <sstream>
#include "State.h"
#include "Button.h"
#include "Constants.h"

/**
 * Outro game state class inheriting State.
 * Represents a pop-up style box with information about the checkout amount.
 */
class Outro : public State
{
public:
	/**
	 * Default constructor, not meant to be used, NULLs all members.
	 */
	Outro();

	/**
	 * Second constructor, sets up SDL_Renderer* to use for future operations.
	 * Allocates memory for all members and sets up their positions and content.
	 */
	Outro(SDL_Renderer*);

	/**
	 * Virtual destructor frees all allocated memory and NULLs all members.
	 */
	virtual ~Outro();
public:
	/**
	 * Interprets events during the time this state is active.
	 * Recognizes mouse clicks on it's box and ends early if clicked.
	 */
	void EventHandler(SDL_Event&);

	/**
	 * Draws the box on screen.
	 * Bool variable is kept from State class
	 * but goes unused due to the box redrawing itself every Render call.
	 * Does nothing if either the renderer, background or fonts fail to load.
	 * Recognizes TransitionIn and TransitionOut flags to move the box each Render call.
	 */
	void Render(bool);

	/**
	 * Raises TransitionIn flag and positions elements outside the screen for future appearance.
	 */
	void PrepTransitionIn();

	/**
	 * Takes in the credit amount we're checking out with
	 * and uses a denominator to translate it into real money for displaying on the screen.
	 */
	void SetCredits(unsigned int);
private:
	/**
	 * NULLs all private members.
	 */
	void NullAll();

	/**
	 * Checks if the box is in it's final position.
	 * If so, drops the TransitionIN flag and starts the timer.
	 * If not, moves the box and all elements down by an increment.
	 */
	void TransitionIn();

	/**
	 * Checks if the box is outside the screen.
	 * If so, drops the TransitionOUT flag and raises the Switch flag.
	 * If not, moves the box and all elements up by an increment.
	 */
	void TransitionOut();
private:
	/**
	 * Holds the background image.
	 */
	SDL_Texture* m_TextureBackground;

	/**
	 * Holds the win message on the top of the box.
	 */
	Label* m_LabelWinSign;

	/**
	 * Holds the amount cashed out (as a picture).
	 */
	TextField* m_TextFieldMoney;

	/**
	 * Holds the font used for the money field.
	 */
	TTF_Font* m_FontLabel;

	/**
	 * Holds the font used for the title message.
	 */
	TTF_Font* m_FontTitle;

	/**
	 * Holds sound effect
	 */
	Mix_Chunk* m_Sound;

	/**
	 * Holds the numerical value of the cashed out amount.
	 */
	float m_fCashOutAmmount;

	/**
	 * Used to track time passed after screen is shown.
	 */
	Uint32 m_uiTimer;

	/**
	 * Used to hold the X coordinate of the box.
	 */
	int m_iX;

	/**
	 * Used to hold the Y coordinate of the box.
	 */
	int m_iY;
};

#endif /* OUTRO_H_ */
