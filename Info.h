#ifndef INFO_H_
#define INFO_H_

#include <SDL2/SDL.h>
#include "Button.h"

/**
 * Class for the info box in intro.
 */
class Info
{
public:
	/**
	 * Unused default constructor.
	 * Nulls all members.
	 */
	Info();

	/**
	 * Second constructor. Saves info on
	 * renderer and allocates memory for members.
	 */
	Info(SDL_Renderer*);

	/**
	 * Frees allocated memory.
	 */
	~Info();
public:
	/**
	 * Render method that takes
	 * UpdateOnly flag.
	 */
	void Render(bool);

	/**
	 * Event handler method.
	 */
	void EventHandler(SDL_Event&);

	/**
	 * Checks the hide flag.
	 */
	bool GetHide() const;

	/**
	 * Resets the box to the first screen.
	 */
	void Reset();
private:
	/**
	 * Renderer used.
	 */
	SDL_Renderer* m_Rednerer;

	/**
	 * Texture array for the two pages' textures.
	 */
	SDL_Texture* m_TextrureScreens[2];

	/**
	 * Font used for the buttons.
	 */
	TTF_Font* m_Font;

	/**
	 * Next/Previous button.
	 */
	Button* m_ButtonNext;

	/**
	 * Exit/Close button.
	 */
	Button* m_ButtonExit;

	/**
	 * Flag tracking changes to info box.
	 */
	bool m_bHasChanged;

	/**
	 * Flag tracking which page is shown.
	 */
	bool m_bShowFirst;

	/**
	 * Flag for recognizing when the info box is closed.
	 */
	bool m_bHide;

	/**
	 * X position coordinate.
	 */
	int m_iX;

	/**
	 * Y position coordinate.
	 */
	int m_iY;
};

#endif /* INFO_H_ */
