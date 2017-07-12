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

	TextField();
	virtual ~TextField();

public:

	void SetField(int, int, int, int);

private:


private:

	SDL_Rect rect;
};

#endif /* TEXTFIELD_H_ */
