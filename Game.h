#ifndef GAME_H_
#define GAME_H_

#include <string>
#include <sstream>
#include "State.h"
#include "Button.h"
#include "GamePanel.h"
#include "Reel.h"
#include "Lines.h"

/**
 * Game state class inheriting State.
 */
class Game : public State
{
public:
	/**
	 * Unused default constructor.
	 * Nulls all members.
	 */
	Game();

	/**
	 * Second constructor, used to set a
	 * renderer and initialize members.
	 */
	Game(SDL_Renderer*);

	/**
	 * Virtual destructor. Frees memory.
	 */
	virtual ~Game();
public:
	/**
	 * Render method, takes UpdateOnly flag.
	 */
	void Render(bool);

	/**
	 * Event Handler method.
	 */
	void EventHandler(SDL_Event&);

	/**
	 * Raises TransitionIn flag and prepares
	 * members for transition.
	 */
	void PrepTransitionIn();

	/**
	 * Set credits to play with.
	 */
	void SetCredits(unsigned int);

	/**
	 * Get credits.
	 */
	unsigned int GetCredits() const;

	/**
	 * Get amount paid on last roll.
	 */
	unsigned int GetPaid() const;

	/**
	 * Get total amount bet.
	 */
	unsigned int GetTotalBet() const;

	/**
	 * Set the reel figures pattern.
	 */
	void SetReel(std::string, std::string, unsigned int = 0);

	/**
	 * Get the reel figures pattern.
	 */
	std::string GetReel();

	/**
	 * Get the map for animated figures.
	 */
	std::string GetAnimate();

	/**
	 * Get the amount bet per line.
	 */
	unsigned int GetBet() const;

	/**
	 * Set the bet amount.
	 */
	void SetBet(unsigned int);

	/**
	 * Get the amount of lines.
	 */
	unsigned int GetLines() const;

	/**
	 * Set the lines amount.
	 */
	void SetLines(unsigned int);

	/**
	 * Calculate the winnings from a roll.
	 */
	void CalcWinning(unsigned int);

	/**
	 * Force calculate the winnings
	 * regardless if the roll was over.
	 * Returns true if bonus game should be triggered.
	 */
	bool CalcWinningForce();

	/**
	 * Check the win flag.
	 */
	bool GetWin() const;

	/**
	 * Reset the win flag.
	 */
	void ResetWin();

	/**
	 * Check the bonus flag.
	 */
	bool GetBonus() const;

	/**
	 * Reset the bonus flag.
	 */
	void ResetBonus();

	/**
	 * Get the cashout flag.
	 */
	bool GetCashOut() const;

	/**
	 * Reset the cashout flag.
	 */
	void ResetCashOut();

	/**
	 * Pause the reel animations and reset the bets.
	 */
	void Clear();
private:
	/**
	 * Process result from the reel.
	 */
	void ProcessResult();
private:
	/**
	 * Game background texture.
	 */
	SDL_Texture* m_TextureBackground;

	/**
	 * Texture for the PayTable.
	 */
	SDL_Texture* m_TexturePayTable;

	/**
	 * Flag for showing the pay table.
	 */
	bool m_bShowPayTable;

	/**
	 * Flag for checing if the reel is spinning.
	 */
	bool m_bIsSpinning;

	/**
	 * Flag for tracking if you won a roll.
	 */
	bool m_bWin;

	/**
	 * Flag for tracking if you got the bonus game.
	 */
	bool m_bBonus;

	/**
	 * Flag for checking if you cash out.
	 */
	bool m_bCashOut;

	/**
	 * Game panel object for user data and interface.
	 */
	GamePanel* m_Panel;

	/**
	 * Lines object for calculating results from a roll.
	 */
	Lines* m_Lines;

	/**
	 * Reel object for viewing experience.
	 */
	Reel* m_Reel;
};

#endif /* GAME_H_ */
