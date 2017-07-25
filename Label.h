#ifndef LABEL_H_
#define LABEL_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <iostream>

/**
 * Class for text labels.
 */
class Label
{
public:
	/**
	 * Unused default constructor.
	 * Nulls all members.
	 */
	Label();

	/**
	 * Second constructor. Sets up
	 * renderer for future operations.
	 */
	Label(SDL_Renderer*);

	/**
	 * Virtual destructor.
	 * Frees allocated memory.
	 */
	virtual ~Label();
public:
	/**
	 * Get label width.
	 */
	virtual int GetWidth() const;

	/**
	 * Get label height.
	 */
	virtual int GetHeight() const;

	/**
	 * Set X position.
	 */
	virtual void SetX(int);

	/**
	 * Set Y position.
	 */
	virtual void SetY(int);

	/**
	 * Method for drawing the label.
	 * Takes in an UpdateOnly flag.
	 */
	virtual void Render(bool);

	/**
	 * Set text to be displayed with the Label.
	 */
	virtual void SetText(std::string, TTF_Font*, SDL_Color);
protected:
	/**
	 * Renderer used.
	 */
	SDL_Renderer* m_Renderer;

	/**
	 * Rectangle holding the sizes an position of the label.
	 */
	SDL_Rect m_TextRect;

	/**
	 * Texture of the loaded text.
	 */
	SDL_Texture* m_TextureText;

	/**
	 * Flag tracking changes for the Render method.
	 */
	bool m_bHasChanged;
};

#endif /* LABEL_H_ */
