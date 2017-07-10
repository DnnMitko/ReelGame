/*
 * TextField.h
 *
 *  Created on: Jul 10, 2017
 *      Author: Ivan
 */

#ifndef TEXTFIELD_H_
#define TEXTFIELD_H_

#include "Label.h"

class TextField : public Label
{
public:
	// Constructors, destructor and operators
	TextField();
	virtual ~TextField();

public:
	// Public functions
	void setField(int, int, int, int);
private:
	// Private functions

private:
	// Private variables
	SDL_Rect rect;
};

#endif /* TEXTFIELD_H_ */
