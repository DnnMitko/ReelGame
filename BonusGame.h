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

/**
 * BonusGame class for the bonus game.
 * Inherits State similar to the other state classes.
 */
class BonusGame : public State
{
public:
	/**
	 * Unused empty default constructor.
	 * Nulls all members.
	 */
	BonusGame();

	/**
	 * Second constructor, takes and saves information on
	 * Renderer and uses it for future operations.
	 * Also initializes all members.
	 */
	BonusGame(SDL_Renderer*);

	/**
	 * Virtual destructor for freeing memory from
	 * all members.
	 */
	virtual ~BonusGame();
public:
	/**
	 * Finction for processing events.
	 */
	void EventHandler(SDL_Event&);

	/**
	 * Render method taking an UpdateOnly flag.
	 * Flag goes unused in this method as BonusGame
	 * redraws it's whole self every frame.
	 */
	void Render(bool);

	/**
	 * Raises TransitionIn flag and positions elements off screen.
	 */
	void PrepTransitionIn();

	/**
	 * Sets the amount of credits bet on this roll.
	 */
	void SetCredits(unsigned int);

	/**
	 * Gets the total credits won from the bonus game.
	 */
	unsigned int GetCredits() const;

	/**
	 * Check the HasChosen flag.
	 */
	bool GetHasChosen() const;

	/**
	 * Closes chests and resets flags.
	 * Prepares bonus game for another run.
	 */
	void ResetGame();
private:
	/**
	 * Nulls all members.
	 */
	void NullAll();

	/**
	 * Tracks if it's time to stop moving the box.
	 * If so, plays a sound. If not, keeps moving the box.
	 */
	void TransitionIn();

	/**
	 * Tracks if the box is hidden off screen.
	 * If not, keeps moving it. If so, raises
	 * Switch flag.
	 */
	void TransitionOut();

	/**
	 * Allocates memory for the objects on the
	 * Bonus Game title screen.
	 */
	void InitTitleScreen();

	/**
	 * Loads the fonts.
	 */
	void InitFonts();

	/**
	 * Allocates memory for the objects on the
	 * Bonus game choose screen.
	 */
	void InitGame();

	/**
	 * Allocates memory for the chests.
	 */
	void InitChests();

	/**
	 * Loads in the sound effect.
	 */
	void InitSound();

	/**
	 * Updates textfield to show how much is won
	 * from the chest choice in the bonus game.
	 */
	void UpdateChestWin(int);

	/**
	 * Updates the title screen text field
	 * to show the current winnings from
	 * reaching the bonus game.
	 */
	void UpdateCurWin();

	/**
	 * Generates a prize and adds it to the total winnings.
	 */
	void GenPrize();
private:
	/**
	 * Texture for the game background.
	 */
	SDL_Texture* m_TextureBackgroundGame;

	/**
	 * Texture for the bonus game title screen.
	 */
	SDL_Texture* m_TextureBackgroundInit;

	/**
	 * Sound effect.
	 */
	Mix_Chunk* m_Sound;

	/**
	 * Title screen label.
	 */
	Label* m_LabelTitleSign;

	/**
	 * Text field for the chest winnings.
	 */
	TextField* m_TextFieldCredits;

	/**
	 * Chest on the leftmost side.
	 */
	Chest* m_Chest1;

	/**
	 * Chest in the middle.
	 */
	Chest* m_Chest2;

	/**
	 * Chest on the rightmost.
	 */
	Chest* m_Chest3;

	/**
	 * Font for the text fields.
	 */
	TTF_Font* m_FontCredits;

	/**
	 * Font for the title.
	 */
	TTF_Font* m_FontTitle;

	/**
	 * Total winnings.
	 */
	unsigned int m_uiCredits;

	/**
	 * Timer for tracking time intervals.
	 */
	Uint32 m_uiTimer;

	/**
	 * Label telling you how much you won so far.
	 */
	Label* m_LabelCurWin;

	/**
	 * Text field showing the winnings from entering
	 * the bonus game.
	 */
	TextField* m_TextFieldCurWin;

	/**
	 * Start button.
	 */
	Button* m_ButtonStart;

	/**
	 * HasChosen flag.
	 */
	bool m_bHasChosen;

	/**
	 * HasStarted flag.
	 */
	bool m_bHasStarted;

	/**
	 * X position of the box.
	 */
	int m_iX;

	/**
	 * Y position of the box.
	 */
	int m_iY;
};

#endif /* BONUSGAME_H_ */
