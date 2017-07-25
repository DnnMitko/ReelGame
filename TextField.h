#ifndef TEXTFIELD_H_
#define TEXTFIELD_H_

#include "Label.h"

/**
 * TextField class inheriting Label.
 */
class TextField : public Label
{
public:
	/**
	 * Unused default constructor.
	 */
	TextField();

	/**
	 * Second constructors.
	 * Sets renderer for future use.
	 */
	TextField(SDL_Renderer*);

	/**
	 * Virtual destructor.
	 */
	virtual ~TextField();
public:
	/**
	 * Get method for the field width.
	 */
	int GetWidth() const;

	/**
	 * Get method for the field height.
	 */
	int GetHeight() const;

	/**
	 * Set X position.
	 */
	void SetX(int);

	/**
	 * Set Y position.
	 */
	void SetY(int);

	/**
	 * Render method for drawing the text field and label center on it.
	 */
	virtual void Render(bool);

	/**
	 * Set text to show on the field.
	 */
	virtual void SetText(std::string, TTF_Font*, SDL_Color);

	/**
	 * Set height and width for the field.
	 */
	void SetFieldSize(int, int);
protected:
	/**
	 * Rectangle holding data for the text field.
	 */
	SDL_Rect m_FieldRect;
};

#endif /* TEXTFIELD_H_ */
