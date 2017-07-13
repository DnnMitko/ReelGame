#ifndef STATE_H_
#define STATE_H_

#include <SDL2/SDL.h>

class State
{
public:
	State();
	virtual ~State();
public:
	bool GetSwitch() const;
	void ResetSwitch();

	void SetRenderer(SDL_Renderer*);

	virtual void RenderSmart() = 0;
	virtual void RenderForce() = 0;

	virtual void EventHandler(SDL_Event&) = 0;

	virtual void Destroy() = 0;
protected:
	bool m_bSwitch;
	SDL_Renderer* m_Renderer;
};

#endif /* STATE_H_ */
