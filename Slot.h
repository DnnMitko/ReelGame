#ifndef SLOT_H_
#define SLOT_H_

#include <SDL2/SDL.h>
#include "Figure.h"
#include "Constants.h"

/**
 * Class for a slot in the reel.
 */
class Slot
{
public:
	/**
	 * Unused default constructor.
	 * Nulls all members.
	 */
	Slot();

	/**
	 * Second constructor.
	 * Saves info on renderer and
	 * initializes members.
	 */
	Slot(SDL_Renderer*);

	/**
	 * Frees allocated memory for members.
	 */
	~Slot();
public:
	/**
	 * Method for drawing the slot.
	 * Takes in an UpdateOnly flag.
	 */
	void Render(bool);

	/**
	 * Set up horizontal position.
	 */
	void SetX(int);

	/**
	 * Set up vertical position.
	 */
	void SetY(int);

	/**
	 * Sets the slot to spin.
	 * Takes in a HasSpecial flag to know if it should
	 * try generating special figures for this slot.
	 */
	void Spin(bool);

	/**
	 * Check if slot has stopped spinning.
	 */
	bool HasStopped() const;

	/**
	 * Animates figures from the slot
	 * based on the information from a string.
	 */
	void Animate(std::string);

	/**
	 * Stops the animation of the figures.
	 */
	void Stop();

	/**
	 * Sets figures to show.
	 * Takes a string with the
	 * information about which figures to use.
	 */
	void SetResult(std::string);

	/**
	 * Gets the current figures as a string.
	 */
	std::string GetResult() const;

	/**
	 * Sets spin time.
	 */
	void SetDelay(unsigned int);
private:
	/**
	 * Generates the next figures to stop on.
	 * Takes a flag to tell it if it should
	 * try generating special symbols.
	 */
	void GenNext(bool);

	/**
	 * Processes rolling the figures down.
	 * Takes a reference to the UpdateOnly flag from Render.
	 */
	void ProcessRolling(bool&);

	/**
	 * After rolling is done, this method
	 * sets the generated figures in place.
	 * Takes a reference to the UpdateOnly
	 * flag from Render.
	 */
	void ProcessPuttingInPlace(bool&);

	/**
	 * Cover one figure sized blocks on top and on bottom of the slot
	 * with cutouts from the game background.
	 */
	void CoverUp();

	/**
	 * Copies the position and figure of the figures
	 * in the slot in upward order and resets positioning
	 * of the first one.
	 */
	void CopyUp();
private:
	/**
	 * Renderer used for operations.
	 */
	SDL_Renderer* m_Renderer;

	/**
	 * texture holding the game background to use
	 * for covering up.
	 */
	SDL_Texture* m_TextureBackground;

	/**
	 * An array of 4 Figure objects.
	 */
	Figure* m_Figures[4];

	/**
	 * A string holding information on the current
	 * fogures shown on the slot.
	 */
	std::string m_strResult;

	/**
	 * Integer used to track progress on
	 * putting figures in place at the end of
	 * rolling in the ProcessPuttingInPlace method.
	 */
	int m_iPos;

	/**
	 * Flag for rolling state of the slot.
	 */
	bool m_bIsRolling;

	/**
	 * Flag for checking if we're in the process of putting
	 * the generated figures in place at the end of a roll.
	 */
	bool m_bPutInPlace;

	/**
	 * X position of the slot.
	 */
	int m_iX;

	/**
	 * Y position of the slot.
	 */
	int m_iY;

	/**
	 * Timer variable for tracking time intervals.
	 */
	Uint32 m_uiTimer;

	/**
	 * Holds how long slot will spin.
	 */
	unsigned int m_Delay;
};

#endif /* SLOT_H_ */
