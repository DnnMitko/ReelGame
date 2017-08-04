#ifndef INTRO_H_
#define INTRO_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>
#include <sstream>
#include "State.h"
#include "Button.h"
#include "Info.h"

/**
 * Intro game state class inheriting State.
 */
class Intro : public State
{
public:
	/**
	 * Default constructor, not meant to be used, NULLs all members.
	 */
	Intro();

	/**
	 * Second constructor, sets up SDL_Renderer* to use for future operations.
	 * Allocates memory for all members and sets up their positions and content.
	 * Sets status of the Resume button.
	 */
	Intro(SDL_Renderer*);

	/**
	 * Virtual destructor frees all allocated memory and NULLs all members.
	 */
	~Intro();
public:
	/**
	 * Render method drawing the menu.
	 * Takes in an UpdateOnly flag.
	 * Does nothing if either the renderer, background or fonts fail to load.
	 * Recognizes TransitionIn and TransitionOut flags to move the box each Render call.
	 */
	void Render(bool);

	/**
	 * Interprets events during the time this state is active.
	 * Recognizes mouse clicks on it's buttons.
	 */
	void EventHandler(SDL_Event&);

	/**
	 * Raises TransitionIn flag and positions elements outside the screen for future appearance.
	 */
	void PrepTransitionIn();

	/**
	 * Get method for credits.
	 */
	unsigned int GetCredits() const;

	/**
	 * Check resume flag.
	 */
	bool GetResume() const;

	/**
	 * Reset resume flag.
	 */
	void ResetResume();

	/**
	 * Check if resume should be enabled.
	 */
	void CheckSave(bool);
private:
	/**
	 * Release all buttons.
	 */
	void ReleaseAll();

	/**
	 * Null all members.
	 */
	void NullAll();

	/**
	 * Allocate and position Start button.
	 */
	void InitStartGame();

	/**
	 * Allocate and position Resume button.
	 * Takes bool to know if the button should be accessable.
	 */
	void InitResumeGame();

	/**
	 * Allocate and position credit buttons
	 * for increase and decrease.
	 * Also the credit label.
	 */
	void InitInsertCredit();

	/**
	 * Allocate and position Info button
	 * and Info pop-up object.
	 */
	void InitInfo();

	/**
	 * Allocate and position volume buttons
	 * for increase and decrease.
	 * Also the volume label.
	 */
	void InitVolume();

	/**
	 * Allocate and positions label and
	 * textfield for added credits.
	 */
	void InitCredits();

	/**
	 * Update the amount shown on added credits.
	 */
	void UpdateCredits();

	/**
	 * Checks if the menu is in it's final position.
	 * If so, drops the TransitionIN flag.
	 * If not, moves all elements up by an increment.
	 */
	void TransitionIn();

	/**
	 * Checks if the menu is out of the screen.
	 * If so, drops the TransitionOut flag and
	 * raises the Switch flag.
	 * If not, moves all elements down by an increment.
	 */
	void TransitionOut();

	/**
	 * Repositions all elements' Y coordinate.
	 */
	void Reposition();
private:
	/**
	 * Amount of credits in intro.
	 */
	int m_uiCredit;

	/**
	 * Flag for checking if we're
	 * resuming a game or starting anew.
	 */
	bool m_bResume;

	/**
	 * Texture for the background image.
	 */
	SDL_Texture* m_TextureBackground;

	/**
	 * Font used for texts.
	 */
	TTF_Font* m_Font;

	/**
	 * Button for start.
	 */
	Button* m_ButtonStart;

	/**
	 * Button for resume.
	 */
	Button* m_ButtonResume;

	/**
	 * Label for credit in the menu.
	 */
	Label* m_LabelCredit;

	/**
	 * Button for increasing credits.
	 */
	Button* m_ButtonCreditPlus;

	/**
	 * Button for decreasing credits.
	 */
	Button* m_ButtonCreditMinus;

	/**
	 * Button for info.
	 */
	Button* m_ButtonInfo;

	/**
	 * Label for volume.
	 */
	Label* m_LabelVolume;

	/**
	 * Button for increasing volume.
	 */
	Button* m_ButtonVolumePlus;

	/**
	 * Button for decreasing volume.
	 */
	Button* m_ButtonVolumeMinus;

	/**
	 * Label for the credits field.
	 */
	Label* m_LabelCredits;

	/**
	 * Credits field.
	 */
	TextField* m_TextFieldCredits;

	/**
	 * Background music.
	 */
	Mix_Music* m_BackgroundSound;

	/**
	 * Current volume setting.
	 */
	int m_iVolume;

	/**
	 * Info pop up.
	 */
	Info* m_Info;

	/**
	 * Flag tracking if info is shown.
	 */
	bool m_bShowInfo;

	/**
	 * Current menu Y coordinate.
	 */
	int m_iY;
};

#endif /* INTRO_H_ */
