#ifndef CHEST_H_
#define CHEST_H_

#include <SDL2/SDL.h>
#include "Button.h"

class Chest
{
public:
	Chest();
	Chest(SDL_Renderer*);
	~Chest();
public:
	void SetX(int);
	void SetY(int);

	void Render(bool = true);

	bool IsIn(int, int);

	void Open();
	void Close();
private:
	SDL_Renderer* m_Renderer;

	SDL_Rect m_FieldRect;

	static SDL_Texture* m_TextureChestClosed;
	static SDL_Texture* m_TextureChestOpen;

	bool m_bHasChanged;
	bool m_bIsOpened;
};

#endif /* CHEST_H_ */
