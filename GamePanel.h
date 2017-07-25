#ifndef GAMEPANEL_H_
#define GAMEPANEL_H_

#include <SDL2/SDL.h>
#include <string>
#include <sstream>
#include "Button.h"

/**
 * GamePanel class for the menu in game.
 */
class GamePanel
{
public:
	/**
	 * Default constructor, not meant to be used, NULLs all members.
	 */
	GamePanel();

	/**
	 * Second constructor, sets up SDL_Renderer* to use for future operations.
	 * Allocates memory for all members and sets up their positions and content.
	 */
	GamePanel(SDL_Renderer*);

	/**
	 * Destructor. Frees all allocated memory and NULLs all members.
	 */
	~GamePanel();
public:
	/**
	 * Draws the menu on screen.
	 * Bool variable used as UpdateOnly flag. Tells the method should it draw all
	 * elements or just redraw those who have chaged.
	 * Does nothing if either the renderer or fonts fail to load.
	 * Recognizes TransitionIn and TransitionOut flags to move the box each Render call.
	 */
	void Render(bool);

	/**
	 * Interprets events during the time this state is active.
	 * Recognizes mouse clicks on it's buttons.
	 * Takes the event and 3 referenced flags from game.
	 * One tells if Play was pressed, one if cash out was pressed
	 * and one if pay table was toggled.
	 */
	void EventHandler(SDL_Event&, bool&, bool&, bool&);

	/**
	 * Raises TransitionIn flag and positions elements outside the screen for future appearance.
	 */
	void PrepTransitionIn();

	/**
	 * Checks if the panel is currently in transition.
	 */
	bool InTransition();

	/**
	 * Raises transitionOut flag which starts hiding the menu.
	 */
	void Hide();

	/**
	 * Set method for credits.
	 */
	void SetCredits(unsigned int);

	/**
	 * Get method for credits.
	 */
	unsigned int GetCredits() const;

	/**
	 * Get method for bet.
	 */
	unsigned int GetBet() const;

	/**
	 * Set method for bet.
	 */
	void SetBet(unsigned int);

	/**
	 * Get method for lines.
	 */
	unsigned int GetLines() const;

	/**
	 * Set method for lines.
	 */
	void SetLines(unsigned int);

	/**
	 * Get method for amount won.
	 */
	unsigned int GetPaid() const;

	/**
	 * Get method for the total bet.
	 */
	unsigned int GetTotalBet() const;

	/**
	 * Takes in the amount won and
	 * updated the text fields for paid
	 * and current credits with the winnings.
	 */
	void CalcWinning(unsigned int);

	/**
	 * Clears all fields except current credits.
	 */
	void Clear();
private:
	/**
	 * NULLs all members.
	 */
	void NullAll();

	/**
	 * Checks if the menu is in it's final position.
	 * If so, drops the TransitionIN flag.
	 * If not, moves the menu and all it's elements up by an increment.
	 */
	void TransitionIn();

	/**
	 * Checks if the box is outside the screen.
	 * If so, drops the TransitionOUT flag.
	 * If not, moves the menu and all it's elements down by an increment.
	 */
	void TransitionOut();

	/**
	 * Repositions all elements by the Y coordinate.
	 */
	void Reposition();

	/**
	 * Allocates memory for paytable button
	 * and positions it.
	 */
	void InitPayTable(int);

	/**
	 * Allocates memory for every
	 * object associated with bet
	 * (label, text field and +/- buttons)
	 * and positions them.
	 */
	void InitBet(int);

	/**
	 * Allocates memory for every
	 * object associated with lines
	 * (label, text field and +/- buttons)
	 * and positions them.
	 */
	void InitLines(int);

	/**
	 * Allocates memory for maxbet button
	 * and positions it.
	 */
	void InitMaxBet(int);

	/**
	 * Allocates memory for every
	 * object associated with current credits
	 * (label and text field) and positions them.
	 */
	void InitCurCredits(int);

	/**
	 * Allocates memory for every
	 * object associated with total bet
	 * (label and text field) and positions them.
	 */
	void InitTotalBet(int);

	/**
	 * Allocates memory for every
	 * object associated with paid amount
	 * (label and text field) and positions them.
	 */
	void InitPaid(int);

	/**
	 * Allocates memory for play button
	 * and positions it.
	 */
	void InitPlay(int);

	/**
	 * Allocates memory for cashout button
	 * and positions it.
	 */
	void InitCashOut(int);

	/**
	 * Updates textfield for bet with
	 * current bet amount.
	 */
	void UpdateBet();

	/**
	 * Updates textfield for lines with
	 * current lines amount.
	 */
	void UpdateLines();

	/**
	 * Updates textfield for current
	 * credits with current bet amount.
	 */
	void UpdateCurCredits();

	/**
	 * Updates textfield for total bet
	 * with current amount.
	 */
	void UpdateTotalBet();

	/**
	 * Updates textfield for paid with
	 * current paid amount.
	 */
	void UpdatePaid();

	/**
	 * Releases all buttons.
	 */
	void ReleaseAll();
private:
	/**
	 * Renderer used for operations.
	 */
	SDL_Renderer* m_Renderer;

	/**
	 * Flag showing when the panel is in
	 * the middle of transitioning on screen.
	 */
	bool m_bTransitionIn;

	/**
	 * Flag showing when the panel is in
	 * the middle of transitioning off screen.
	 */
	bool m_bTransitionOut;

	/**
	 * Y coordinate of the whole panel.
	 */
	int m_iY;

	/**
	 * Amount of current credits.
	 */
	unsigned int m_uiCurCredits;

	/**
	 * Amount on bet.
	 */
	unsigned int m_uiBet;

	/**
	 * Amount on lines.
	 */
	unsigned int m_uiLines;

	/**
	 * Amount on total bet.
	 */
	unsigned int m_uiTotalBet;

	/**
	 * Amount paid.
	 */
	unsigned int m_uiPaid;

	/**
	 * Font for larger labels.
	 */
	TTF_Font* m_FontBig;

	/**
	 * Font for smaller labels.
	 */
	TTF_Font* m_FontSmall;

	/**
	 * Button for PayTable toggle.
	 */
	Button* m_ButtonPayTable;

	/**
	 * Label for bet.
	 */
	Label* m_LabelBet;

	/**
	 * TextField for bet.
	 */
	TextField* m_TextFieldBet;

	/**
	 * Button for decreasing bet.
	 */
	Button* m_ButtonBetMinus;

	/**
	 * Button for increasing bet.
	 */
	Button* m_ButtonBetPlus;

	/**
	 * Label for lines.
	 */
	Label* m_LabelLines;

	/**
	 * TextField for lines.
	 */
	TextField* m_TextFieldLines;

	/**
	 * Button for decreasing lines.
	 */
	Button* m_ButtonLinesMinus;

	/**
	 * Button for increasing lines.
	 */
	Button* m_ButtonLinesPlus;

	/**
	 * Button for MaxBet.
	 */
	Button* m_ButtonMaxBet;

	/**
	 * Label for current credits.
	 */
	Label* m_LabelCurCredits;

	/**
	 * TextField for current credits.
	 */
	TextField* m_TextFieldCurCredits;

	/**
	 * Label for total bet.
	 */
	Label* m_LabelTotalBet;

	/**
	 * TextField for total bet.
	 */
	TextField* m_TextFieldTotalBet;

	/**
	 * Label for paid amount.
	 */
	Label* m_LabelPaid;

	/**
	 * TextField for paid amount.
	 */
	TextField* m_TextFieldPaid;

	/**
	 * Button for play.
	 */
	Button* m_ButtonPlay;

	/**
	 * Button for cash out.
	 */
	Button* m_ButtonCashOut;
};

#endif /* GAMEPANEL_H_ */
