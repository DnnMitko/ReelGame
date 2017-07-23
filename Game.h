#ifndef GAME_H_
#define GAME_H_

#include <string>
#include <sstream>
#include "State.h"
#include "Button.h"
#include "GamePanel.h"

class Game : public State
{
public:
	Game();
	Game(SDL_Renderer*);
	virtual ~Game();
public:
	void Render(bool = true);
	void EventHandler(SDL_Event&);
	void PrepTransitionIn();

	void SetCredits(unsigned int);
	unsigned int GetCredits() const;

	unsigned int GetTotalBet() const;

	unsigned int GetPaid() const;

	void CalcWinning(unsigned int);

	bool GetWin() const;
	void ResetWin();

	bool GetBonus() const;
	void ResetBonus();

	GamePanel* GetGamePanel() { return m_Panel; }

	void Clear();
private:
	SDL_Texture* m_TextureBackground;

	GamePanel* m_Panel;
};

#endif /* GAME_H_ */
