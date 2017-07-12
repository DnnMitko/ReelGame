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

	Button();
	virtual ~Button();

public:

	void Press();
	void Release();
	bool IsPressed();

private:


private:

	bool m_bPressed = false;
};

#endif /* BUTTON_H_ */
