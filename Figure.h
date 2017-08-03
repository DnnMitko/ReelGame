#ifndef FIGURE_H_
#define FIGURE_H_

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <cstdlib>

#include "Constants.h"

/**
 * Class Figure for figures on the reel.
 */
class Figure
{
public:
	/**
	 * Unused default constructor.
	 * Nulls all members.
	 */
	Figure();

	/**
	 * Second constructor. Saves information
	 * on renderer and loads member data.
	 */
	Figure(SDL_Renderer*);

	/**
	 * Frees memory from members.
	 */
	~Figure();
public:
	/**
	 * Sets horizontal position.
	 */
	void SetX(int);

	/**
	 * Sets vertical position.
	 */
	void SetY(int);

	/**
	 * Gets current vertical position.
	 */
	int GetY() const;

	/**
	 * Method for drawing the figure.
	 * Takes in UpdateOnly flag.
	 */
	void Render(bool);

	/**
	 * Animate the figure.
	 */
	void Play();

	/**
	 * Stop the animation of the figure.
	 */
	void Pause();

	/**
	 * Randomizes the figure.
	 */
	void Rand();

	/**
	 * Sets figure based on given figure ID.
	 */
	void SetFigure(char);

	/**
	 * Copies data from another figure.
	 */
	void Copy(Figure*);

	/**
	 * Clears the figure by drawing a background
	 * section on top of it.
	 */
	void Clear();
private:
	/**
	 * Draws the figure.
	 */
	void Draw();
private:
	/**
	 * Renderer used by the figure.
	 */
	SDL_Renderer* m_Renderer;

	/**
	 * Static member for the figure texture.
	 */
	static SDL_Texture* m_TextureFigures;

	/**
	 * Static member for the game background.
	 * Used for clearing.
	 */
	static SDL_Texture* m_TextureBackground;

	/**
	 * Rectangle for which figure from the
	 * figure texture to draw.
	 */
	SDL_Rect m_RectFigure;

	/**
	 * X position of the figure.
	 */
	int m_iX;

	/**
	 * Y position of the figure.
	 */
	int m_iY;

	/**
	 * Flag for checking if the figure is animated.
	 */
	bool m_bIsAnimated;

	/**
	 * Timer variable.
	 */
	Uint32 m_uiTimer;
};





#endif /* FIGURE_H_ */
