#ifndef GAME_H_
#define GAME_H_

#include <string>
#include <sstream>
#include "State.h"
#include "Button.h"
#include "GamePanel.h"
#include "Reel.h"
#include "Lines.h"

class Game : public State
{
public:
	Game();
	Game(SDL_Renderer*);
	virtual ~Game();
public:
	void Render(bool);
	void EventHandler(SDL_Event&);
	void PrepTransitionIn();

	void SetCredits(unsigned int);
	unsigned int GetCredits() const;

	unsigned int GetPaid() const;

	unsigned int GetTotalBet() const;

	std::string GetReel();
	std::string GetAnimate();
	unsigned int GetBet();
	unsigned int GetLines();

	void CalcWinning(unsigned int);
	bool CalcWinningForce();

	bool GetWin() const;
	void ResetWin();

	bool GetBonus() const;
	void ResetBonus();

	bool GetCashOut() const;
	void ResetCashOut();

	void Clear();
private:
	void TransitionIn();
	void TransitionOut();
private:
	SDL_Texture* m_TextureBackground;

	bool m_bIsSpinning;

	bool m_bWin;
	bool m_bBonus;
	bool m_bCashOut;

	GamePanel* m_Panel;
	Lines* m_Lines;
	Reel* m_Reel;
};

#endif /* GAME_H_ */
