#ifndef TEXTFIELD_H_
#define TEXTFIELD_H_

#include "Label.h"

class TextField : public Label
{
public:
	TextField();
	TextField(SDL_Renderer*);
	virtual ~TextField();
public:
	int GetWidth() const;
	int GetHeight() const;

	void SetX(int);
	void SetY(int);

	virtual void Render(bool = true);

	virtual void SetText(std::string, TTF_Font*, SDL_Color);

	void SetFieldSize(int, int);
protected:
	SDL_Rect m_FieldRect;
};

#endif /* TEXTFIELD_H_ */
