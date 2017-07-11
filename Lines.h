/*
 * Lines.h
 *
 *  Created on: Jul 11, 2017
 *      Author: polia
 */

#ifndef LINES_H_
#define LINES_H_
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<vector>
class Lines
{
public:

	std::vector<int>Line1 = {matrix[0][1],matrix[1][1],matrix[2][1],matrix[3][1],matrix[4][1]};
	std::vector<int>Line2 = {matrix[0][0],matrix[1][0],matrix[2][0],matrix[3][0],matrix[4][0]};
	std::vector<int>Line3 = {matrix[0][2],matrix[1][2],matrix[2][2],matrix[3][2],matrix[4][2]};
	std::vector<int>Line4 = {matrix[0][1],matrix[1][1],matrix[2][0],matrix[3][1],matrix[4][1]};
	std::vector<int>Line5 = {matrix[0][1],matrix[1][1],matrix[3][2],matrix[3][1],matrix[4][1]};
	std::vector<int>Line6 = {matrix[0][1],matrix[1][0],matrix[2][0],matrix[3][0],matrix[4][1]};
	std::vector<int>Line7 = {matrix[0][1],matrix[1][2],matrix[2][2],matrix[3][2],matrix[4][1]};
	std::vector<int>Line8 = {matrix[0][0],matrix[1][0],matrix[2][1],matrix[3][1],matrix[4][2]};
	std::vector<int>Line9 = {matrix[0][2],matrix[1][2],matrix[2][1],matrix[3][0],matrix[4][0]};
	std::vector<int>Line10 = {matrix[0][0],matrix[1][0],matrix[2][1],matrix[3][0],matrix[4][0]};
	std::vector<int>Line11 = {matrix[0][2],matrix[1][2],matrix[2][1],matrix[3][2],matrix[4][2]};
	std::vector<int>Line12 = {matrix[0][0],matrix[1][1],matrix[2][1],matrix[3][1],matrix[4][0]};
	std::vector<int>Line13 = {matrix[0][2],matrix[1][1],matrix[2][1],matrix[3][1],matrix[4][2]};
	std::vector<int>Line14 = {matrix[0][1],matrix[1][1],matrix[2][2],matrix[3][1],matrix[4][0]};
	std::vector<int>Line15 = {matrix[0][2],matrix[1][1],matrix[2][0],matrix[3][1],matrix[4][2]};

	Lines();

	void addElement();
	virtual ~Lines();
private:

	unsigned int m_uiColumns = 5;
	unsigned int m_uiRows = 3;
	int matrix [m_uiColumns][m_uiRows];

};

#endif /* LINES_H_ */
