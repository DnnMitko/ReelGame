#ifndef BUTTON_H_
#define BUTTON_H_

#include <SDL2/SDL_image.h>
#include "TextField.h"
#include "Constants.h"

class Button: public TextField
{
public:
	Button();
	Button(SDL_Renderer*);
	virtual ~Button();
public:
	void RenderForce();

	void SetText(std::string, TTF_Font*, SDL_Color);

	bool IsIn(int, int) const;

	void Press();
	void Release();
	bool IsPressed() const;
private:
	bool m_bIsPressed;

	SDL_Texture* m_TextureTextPressed;

	static SDL_Texture* m_TextureButton;
};

#endif /* BUTTON_H_ */
