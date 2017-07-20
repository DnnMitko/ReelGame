#ifndef LINES_H_
#define LINES_H_
#include "Constants.h"
#include<string>

class Lines
{
struct Line
{
	int num1, num2, num3, num4, num5;
};

public:
	Lines();
	virtual ~Lines();
	void SetResult(std::string);
	float GetTotalWin() const;
	bool HasSpecial();
	std::string GetAnimate() const;

private:
	void GenLines();
	void Calculate();
	void GenAnimate(int, char);
private:
	std::string m_strAnimate;
	std::string m_strResult;
	Line m_Line[15];

	std::string m_strLine[15];

	float m_fTotalWin;


};

#endif /* LINES_H_ */
