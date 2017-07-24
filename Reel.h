#ifndef REEL_H_
#define REEL_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include "Slot.h"

class Reel
{
public:
	Reel();
	Reel(SDL_Renderer*);
	~Reel();
public:
	void Render(bool);

	void PrepTransitionIn();
	bool InTransition();
	void Hide();

	void SetResult(std::string);
	std::string GetResult();

	void Spin();
	bool HasStopped();

	void Animate(std::string);
	void Pause();
private:
	void TransitionIn();
	void TransitionOut();
private:
	SDL_Renderer* m_Renderer;

	SDL_Texture* m_TextureFrame;
	SDL_Texture* m_TextureBackground;

	bool m_bTransitionIn;
	bool m_bTransitionOut;

	bool m_bIsAnimated;

	Slot* m_Slots[5];

	int m_iY;

	Mix_Chunk* m_Sound;
};

#endif /* REEL_H_ */
