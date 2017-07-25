#ifndef LINES_H_
#define LINES_H_

#include "Constants.h"
#include<string>

class Lines
{
public:
	/**
	 * Default constructor. Nulls members.
	 */
	Lines();

	/**
	 * Empty destructor.
	 */
	~Lines();
public:
	/**
	 * Set result from reel and
	 * process information.
	 */
	void SetResult(std::string, int);

	/**
	 * Get the total multiplier from
	 * the winnings of the reel result.
	 */
	int GetTotalWin() const;

	/**
	 * Check if there's 3 special symbols.
	 */
	bool HasSpecial();

	/**
	 * Set the animation map.
	 */
	void SetAnimate(std::string);

	/**
	 * Get the animation map.
	 */
	std::string GetAnimate() const;
private:
	/**
	 * Generates strings containing
	 * the figures for each line.
	 */
	void GenLines();

	/**
	 * Calculate total winnings
	 * and maximum win combination.
	 */
	void Calculate();

	/**
	 * Generates animation map
	 * from current result.
	 */
	void GenAnimate();

	/**
	 * Process 3 consecutive
	 * same figures by giving
	 * the line and the position
	 * of the first.
	 */
	void Process3(int, int);

	/**
	 * Process 4 consecutive
	 * same figures by giving
	 * the line and the position
	 * of the first.
	 */
	void Process4(int, int);

	/**
	 * Process 5 consecutive
	 * same figures by giving
	 * the line.
	 */
	void Process5(int);

	/**
	 * Checks and saves if the profit
	 * from a given combo is the maximum
	 * one found so far. Takes in the line,
	 * figure ID and multiplier earned from it.
	 */
	void CheckMax(int, char, int);
private:
	/**
	 * String storing the reel result.
	 */
	std::string m_strResult;

	/**
	 * Holds number of lines
	 * played on during given result.
	 */
	int m_iLinesPlayed;

	/**
	 * Holds animation map.
	 */
	std::string m_strAnimate;

	/**
	 * Static member for mapping positions on the reel
	 * result to each of the 15 lines.
	 */
	static int m_Lines[15][5];

	/**
	 * Strings generated from the lines
	 * and result, storing figure information
	 * on all positions of a given line.
	 */
	std::string m_strLines[15];

	/**
	 * Total win multiplier from
	 * current result.
	 */
	int m_fTotalWin;

	/**
	 * Maximum found multiplier from
	 * current result.
	 */
	int m_iMax;

	/**
	 * Line on which the maximum
	 * multiplier is found from
	 * the current result.
	 */
	int m_iMaxLine;

	/**
	 * Figure ID on the figure
	 * of the most profitable combo
	 * in the current rsult.
	 */
	char m_cMax;
};

#endif /* LINES_H_ */
