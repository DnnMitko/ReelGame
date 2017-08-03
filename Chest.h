#ifndef CHEST_H_
#define CHEST_H_

#include <SDL.h>
#include "Button.h"

/**
 * Chest class used in BonusGame
 */
class Chest
{
public:
	/**
	 * Unused empty constructor
	 */
	Chest();

	/**
	 * Constructor used to assign Renderer and
	 * load textures if needed.
	 */
	Chest(SDL_Renderer*);

	/**
	 * Destructor used to free allocated memory.
	 */
	~Chest();
public:
	/**
	 * Set where, horizontaly, we want the object to be drawn.
	 */
	void SetX(int);

	/**
	 * Set where, vertical, we want the object to be drawn.
	 */
	void SetY(int);

	/**
	 * Draws the chest. Takes flag UpdateOnly, which dictates
	 * should the chest be drawn, or just look for updates.
	 */
	void Render(bool);

	/**
	 * Check if given coordinates are within the chest.
	 */
	bool IsIn(int, int);

	/**
	 * Open the chest.
	 */
	void Open();

	/**
	 * Close the chest.
	 */
	void Close();
private:
	/**
	 * Renderer used to draw the chest and load the textures.
	 */
	SDL_Renderer* m_Renderer;

	/**
	 * Holds position and size of the chest.
	 */
	SDL_Rect m_FieldRect;

	/**
	 * Static members for holding the chest textures.
	 */
	static SDL_Texture* m_TextureChestClosed;
	static SDL_Texture* m_TextureChestOpen;

	/**
	 * Flag for tracking changes in the chest.
	 */
	bool m_bHasChanged;

	/**
	 * Flag for tracking chest state.
	 */
	bool m_bIsOpened;
};

#endif /* CHEST_H_ */
