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

	virtual void Render(bool = true) = 0;

	virtual void EventHandler(SDL_Event&) = 0;
protected:
	bool m_bSwitch;
	SDL_Renderer* m_Renderer;
};

#endif /* STATE_H_ */
