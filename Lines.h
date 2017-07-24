#ifndef LINES_H_
#define LINES_H_

#include "Constants.h"
#include<string>

class Lines
{
public:
	Lines();
	~Lines();
public:
	void SetResult(std::string, int);

	int GetTotalWin() const;

	bool HasSpecial();

	void SetAnimate(std::string);
	std::string GetAnimate() const;
private:
	void GenLines();

	void Calculate();

	void GenAnimate();

	void Process3(int, int);
	void Process4(int, int);
	void Process5(int);
	void CheckMax(int, char, int);
private:
	std::string m_strResult;
	int m_iLinesPlayed;

	std::string m_strAnimate;

	static int m_Lines[15][5];
	std::string m_strLines[15];

	int m_fTotalWin;

	float m_fMax;
	int m_iMaxLine;
	char m_cMax;
};

#endif /* LINES_H_ */
