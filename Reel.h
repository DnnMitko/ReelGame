#ifndef REEL_H_
#define REEL_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include "Slot.h"

/**
 * Class for the reel in the game.
 */
class Reel
{
public:
	/**
	 * Unused default constructor.
	 * Nulls all members.
	 */
	Reel();

	/**
	 * Second constructor. Saves info on
	 * renderer and allocates memory for members.
	 */
	Reel(SDL_Renderer*);

	/**
	 * Destructor. Frees allocated memory.
	 */
	~Reel();
public:
	/**
	 * Render method that takes
	 * UpdateOnly flag.
	 */
	void Render(bool);

	/**
	 * Raises TransitionIn flag and positions elements outside the screen for future appearance.
	 */
	void PrepTransitionIn();

	/**
	 * Checks if the reel is in transition.
	 */
	bool InTransition();

	/**
	 * Raises TransitionOut flag.
	 */
	void Hide();

	/**
	 * Sets figures to show from
	 * a given string.
	 */
	void SetResult(std::string);

	/**
	 * Get the result from the reel.
	 */
	std::string GetResult();

	/**
	 * Spins the reel.
	 */
	void Spin();

	/**
	 * Check if reel has stopped.
	 */
	bool HasStopped();

	/**
	 * Animate figures from
	 * a given string.
	 */
	void Animate(std::string);

	/**
	 * Stops the animations on the reel.
	 */
	void Pause();
private:
	/**
	 * Checks if the box is in it's final position.
	 * If so, drops the TransitionIN flag.
	 * If not, moves the box and all elements down by an increment.
	 */
	void TransitionIn();

	/**
	 * Checks if the box is outside the screen.
	 * If so, drops the TransitionOUT flag.
	 * If not, moves the box and all elements up by an increment.
	 */
	void TransitionOut();
private:
	/**
	 * Renderer used.
	 */
	SDL_Renderer* m_Renderer;

	/**
	 * Texture holding the reel frame.
	 */
	SDL_Texture* m_TextureFrame;

	/**
	 * Texture holds the game background.
	 */
	SDL_Texture* m_TextureBackground;

	/**
	 * Flag for tracking if you're in
	 * the process of transitioning
	 * to the screen.
	 */
	bool m_bTransitionIn;

	/**
	 * Flag for tracking if you're in
	 * the process of transitioning
	 * off the screen.
	 */
	bool m_bTransitionOut;

	/**
	 * Flag for checking if the animations are active.
	 */
	bool m_bIsAnimated;

	/**
	 * Array of 5 slots used in the reel.
	 */
	Slot* m_Slots[5];

	/**
	 * Height of the reel.
	 */
	int m_iY;

	/**
	 * Sound effect.
	 */
	Mix_Chunk* m_Sound;
};

#endif /* REEL_H_ */
