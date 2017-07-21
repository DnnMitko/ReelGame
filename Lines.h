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

	void GenAnimate();

	void Process3(int, int);
	void Process4(int, int);
	void Process5(int);
	void CheckMax(float, char, int);
private:
	std::string m_strAnimate;

	std::string m_strResult;

	Line m_Line[15];
	std::string m_strLine[15];

	float m_fTotalWin;

	float m_fMax;
	int m_iMaxLine;
	char m_cMax;
};

#endif /* LINES_H_ */
