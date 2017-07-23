#ifndef GAMEPANEL_H_
#define GAMEPANEL_H_

#include <SDL2/SDL.h>
#include <string>
#include <sstream>
#include "Button.h"

class GamePanel
{
public:
	GamePanel();
	GamePanel(SDL_Renderer*);
	~GamePanel();
public:
	void Render(bool);
	void EventHandler(SDL_Event&, bool&, bool&);

	void PrepTransitionIn();
	bool InTransition();
	void Hide();

	void SetCredits(unsigned int);
	unsigned int GetCredits() const;

	unsigned int GetBet() const;
	unsigned int GetLines() const;

	unsigned int GetPaid() const;

	unsigned int GetTotalBet() const;

	void CalcWinning(unsigned int);

	void Clear();
private:
	void NullAll();

	void TransitionIn();
	void TransitionOut();
	void Reposition();

	void InitPayTable(int);
	void InitBet(int);
	void InitLines(int);
	void InitMaxBet(int);
	void InitCurCredits(int);
	void InitTotalBet(int);
	void InitPaid(int);
	void InitPlay(int);
	void InitCashOut(int);

	void UpdateBet();
	void UpdateLines();
	void UpdateCurCredits();
	void UpdateTotalBet();
	void UpdatePaid();

	void ReleaseAll();
private:
	SDL_Renderer* m_Renderer;

	bool m_bTransitionIn;
	bool m_bTransitionOut;

	int m_iY;

	unsigned int m_uiCurCredits;
	unsigned int m_uiBet;
	unsigned int m_uiLines;
	unsigned int m_uiTotalBet;
	unsigned int m_uiPaid;

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

	Button* m_ButtonCashOut;
};

#endif /* GAMEPANEL_H_ */
