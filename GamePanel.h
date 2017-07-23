#ifndef GAMEPANEL_H_
#define GAMEPANEL_H_

#include <SDL2/SDL.h>
#include <iostream>
#include <string>
#include <sstream>
#include "Button.h"
#include "pugixml.hpp"
#include <sstream>
#include <string>
#include <cstring>

using namespace std;

class GamePanel
{
public:
	GamePanel();
	GamePanel(SDL_Renderer*);
	~GamePanel();
public:
	void Render(bool = true);
	void EventHandler(SDL_Event&, bool&);

	void SetCredits(unsigned int);
	unsigned int GetCredits() const;

	unsigned int GetTotalBet() const;

	unsigned int GetPaid() const;

	void CalcWinning(unsigned int);

	bool GetWin() const;
	void ResetWin();

	bool GetBonus() const;
	void ResetBonus();

	void Clear();
	string Convert(unsigned int);
	void Recovery();
private:
	void NullAll();

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

	bool m_bWin;
	bool m_bBonus;

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
