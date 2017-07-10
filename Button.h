/*
 * Button.h
 *
 *  Created on: Jul 10, 2017
 *      Author: Ivan
 */

#ifndef BUTTON_H_
#define BUTTON_H_

#include "TextField.h"

class Button : public TextField
{

public:
	// Constructors, destructor and operators
	Button();
	virtual ~Button();

public:
	// Public functions
	void Press();
	void Release();
	bool IsPressed();

private:
	// Private functions

private:
	// Private variables
	bool m_bPressed = false;
};

#endif /* BUTTON_H_ */
