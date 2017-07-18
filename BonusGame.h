#ifndef BONUSGAME_H_
#define BONUSGAME_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <sstream>
#include <cstdlib>
#include "State.h"
#include "Button.h"
#include "Constants.h"
#include "Chest.h"

class BonusGame : public State
{
public:
	BonusGame();
	BonusGame(SDL_Renderer*);
	virtual ~BonusGame();
public:
	void EventHandler(SDL_Event&);
	void Render(bool = true);
	void SetCredits(unsigned int);
	unsigned int GetCredits() const;
	void ResetGame();
private:
	void NullAll();

	void InitTitleScreen();
	void InitFonts();
	void InitGame();
	void InitChests();

	void UpdateChestWin(int);
	void UpdateCurWin();

	void GenPrize();
private:
	SDL_Texture* m_TextureBackgroundGame;
	SDL_Texture* m_TextureBackgroundInit;

	Label* m_LabelTitleSign;
	TextField* m_TextFieldCredits;

	Chest* m_Chest1;
	Chest* m_Chest2;
	Chest* m_Chest3;

	TTF_Font* m_FontCredits;
	TTF_Font* m_FontTitle;

	unsigned int m_uiCredits;

	Uint32 m_uiTimer;

	Label* m_LabelCurWin;
	TextField* m_TextFieldCurWin;
	Button* m_ButtonStart;

	bool m_bHasChosen;
	bool m_bHasStarted;

	int m_iX;
	int m_iY;
};

#endif /* BONUSGAME_H_ */
