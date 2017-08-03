#ifndef STATE_H_
#define STATE_H_

#include <SDL.h>

/**
 * Abstract class, used for defining the
 * basic interface for all state classes.
 */
class State
{
public:
	/**
	 * Unused default constructor.
	 */
	State();

	/**
	 * Sets renderer information and initial flags values.
	 */
	State(SDL_Renderer*);

	/**
	 * Empty virtual destructor.
	 */
	virtual ~State();
public:
	/**
	 * Checks the switch flag.
	 */
	bool GetSwitch() const;

	/**
	 * Resets switch flag.
	 */
	void ResetSwitch();

	/**
	 * Pure virtual method for preparing the state
	 * for showing on the screen.
	 */
	virtual void PrepTransitionIn() = 0;

	/**
	 * Pure virtual method for drawing on screen.
	 * Takes in an UpdateOnly flag to save on redrawing effort.
	 */
	virtual void Render(bool) = 0;

	/**
	 * Pure virtual method for processing events.
	 */
	virtual void EventHandler(SDL_Event&) = 0;
protected:
	/**
	 * Renderer used for operations.
	 */
	SDL_Renderer* m_Renderer;

	/**
	 * Flag for switching states.
	 */
	bool m_bSwitch;

	/**
	 * Flag for being in transition.
	 * Used for being in the process of showing up
	 * on screen.
	 */
	bool m_bTransitionIn;

	/**
	 * Flag for being in transition.
	 * Used for being in the process of leaving
	 * the screen.
	 */
	bool m_bTransitionOut;
};

#endif /* STATE_H_ */
