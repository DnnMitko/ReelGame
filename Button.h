#ifndef BUTTON_H_
#define BUTTON_H_

#include <SDL_image.h>
#include <SDL_mixer.h>
#include "TextField.h"
#include "Constants.h"

/**
 * Class for buttons. Inherits TextField.
 */
class Button: public TextField
{
public:
	/**
	 * Unused default constructor.
	 * Nulls all members.
	 */
	Button();

	/**
	 * Second constructor. Saves information for
	 * renderer and allocates memory for members.
	 */
	Button(SDL_Renderer*);

	/**
	 * Virtual destructor. Frees all alocated memory.
	 */
	virtual ~Button();
public:
	/**
	 * Render function. Takes in an UpdateOnly flag.
	 */
	void Render(bool);

	/**
	 * Sets text shown on the button.
	 * Takes in a string, a font and a color.
	 */
	void SetText(std::string, TTF_Font*, SDL_Color);

	/**
	 * Checks if given coordinates are within the button.
	 */
	bool IsIn(int, int) const;

	/**
	* Marks button as enabled.
	*/
	void Enable();

	/**
	* Marks button as disabled.
	*/
	void Disable();

	/**
	 * Marks button as pressed.
	 */
	void Press();

	/**
	 * Marks button as released.
	 */
	void Release();

	/**
	 * Returns if the button is pressed.
	 */
	bool IsPressed() const;
private:
	/**
	 * IsPressed flag for button state.
	 */
	bool m_bIsPressed;

	/**
	 * Flag for botton enabling.
	 */
	bool m_bEnabled;

	/**
	 * Copy of the text message on the button in white.
	 * Used for display on a pressed button.
	 */
	SDL_Texture* m_TextureTextPressed;

	/**
	 * Static member for the button texture.
	 */
	static SDL_Texture* m_TextureButton;

	/**
	 * Static member for the sound effect.
	 */
	static Mix_Chunk* m_SfxClick;
};

#endif /* BUTTON_H_ */
