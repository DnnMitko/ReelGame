#ifndef GAME_H_
#define GAME_H_

#include "State.h"
#include "Button.h"

class Game : public State
{
public:
	Game();
	Game(SDL_Renderer*);
	virtual ~Game();
public:
	void Render(bool = true);
	void EventHandler(SDL_Event&);
	void SetCredits(unsigned int);
private:
	unsigned int m_uiCurrentCredits;

	SDL_Texture* m_TextureBackground;

	TTF_Font* m_FontBig;
	TTF_Font* m_FontSmall;

	Button* m_ButtonPayTable;

	Label* m_LabelBet;
	TextField* m_TextFieldBet;
	Button* m_ButtonBetMinus;
	Button* m_ButtonBetPlus;

	Label* m_LabelLines;
	TextField* m_TextFieldLines;
	Button* m_ButtonLinesMinus;
	Button* m_ButtonLinesPlus;

	Button* m_ButtonMaxBet;

	Label* m_LabelCurCredits;
	TextField* m_TextFieldCurCredits;

	Label* m_LabelTotalBet;
	TextField* m_TextFieldTotalBet;

	Label* m_LabelPaid;
	TextField* m_TextFieldPaid;

	Button* m_ButtonPlay;
};

#endif /* GAME_H_ */
