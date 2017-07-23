#ifndef SLOT_H_
#define SLOT_H_

#include <SDL2/SDL.h>
#include "Figure.h"
#include "Constants.h"

class Slot
{
public:
	Slot();
	Slot(SDL_Renderer*);
	~Slot();
public:
	void Render(bool);

	void SetX(int);
	void SetY(int);

	void Spin(bool);
	bool HasStopped() const;

	void Animate(std::string);
	void Stop();

	std::string GetResult() const;
private:
	void GenNext(bool);

	void ProcessRolling(bool&);
	void ProcessPuttingInPlace(bool&);

	void CoverUp();
	void CopyUp();
private:
	SDL_Renderer* m_Renderer;

	SDL_Texture* m_TextureBackground;

	Figure* m_Figures[4];

	std::string m_strResult;
	int m_iPos;

	bool m_bIsRolling;
	bool m_bPutInPlace;

	int m_iX;
	int m_iY;

	Uint32 m_uiTimer;
};

#endif /* SLOT_H_ */
