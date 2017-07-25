#ifndef WIN_H_
#define WIN_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <sstream>
#include "State.h"
#include "Button.h"
#include "Constants.h"

/**
 * Win state class that shows a box with the won amount.
 * Inherits class State.
 */
class Win : public State
{
public:
	/**
	 * Unused default constructor.
	 * Nulls all members.
	 */
	Win();

	/**
	 * Second constructor.
	 * Sets renderer and allocates members.
	 */
	Win(SDL_Renderer*);

	/**
	 * Virtual destructor to free memory.
	 */
	virtual ~Win();
public:
	/**
	 * Event Handler function.
	 */
	void EventHandler(SDL_Event&);

	/**
	 * Draws the box. Bool variable goes unused,
	 * cause we redraw every frame.
	 */
	void Render(bool);

	/**
	 * Sets Y coordinates to be offscreen
	 * and raises TransitionIn flag.
	 */
	void PrepTransitionIn();

	/**
	 * Converts credits to string
	 * using stringstream and
	 * loads them to the textfield.
	 */
	void SetCredits(unsigned int);
private:
	/**
	 * Nulls all members.
	 */
	void NullAll();

	/**
	 * Checks position and repositions members.
	 */
	void TransitionIn();
	void TransitionOut();
private:
	/**
	 * Texture for background image.
	 */
	SDL_Texture* m_TextureBackground;

	/**
	 * Win text label.
	 */
	Label* m_LabelWinSign;

	/**
	 * Text field for the credit amount.
	 */
	TextField* m_TextFieldCredits;

	/**
	 * Font used for credits field.
	 */
	TTF_Font* m_FontCredits;

	/**
	 * Font used for title label.
	 */
	TTF_Font* m_FontTitle;

	/**
	 * Sound effect.
	 */
	Mix_Chunk* m_Sound;

	/**
	 * Credits won.
	 */
	unsigned int m_uiCredits;

	/**
	 * Timer.
	 */
	Uint32 m_uiTimer;

	/**
	 * X position of the box.
	 */
	int m_iX;

	/**
	 * Y position of the box.
	 */
	int m_iY;
};

#endif /* WIN_H_ */
