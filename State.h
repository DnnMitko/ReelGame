#ifndef STATE_H_
#define STATE_H_

#include <SDL2/SDL.h>

class State
{
public:
	State();
	State(SDL_Renderer*);
	virtual ~State();
public:
	bool GetSwitch() const;
	void ResetSwitch();

	virtual void PrepTransitionIn() = 0;

	virtual void Render(bool) = 0;

	virtual void EventHandler(SDL_Event&) = 0;
protected:
	SDL_Renderer* m_Renderer;

	bool m_bSwitch;
	bool m_bTransitionIn;
	bool m_bTransitionOut;
};

#endif /* STATE_H_ */
