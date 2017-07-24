#include "Lines.h"

int Lines::m_Lines[15][5] = { {1, 4, 7, 10, 13},
							  {0, 3, 6, 9, 12},
							  {2, 5, 8, 11, 14},
							  {1, 4, 6, 10, 13},
							  {1, 4, 8, 10, 13},
							  {1, 3, 6, 9, 13},
							  {1, 5, 8, 11, 13},
							  {0, 3, 7, 11, 14},
							  {2, 5, 7, 9, 12},
							  {0, 3, 7, 9, 12},
							  {2, 5, 7, 11, 14},
							  {0, 4, 7, 10, 12},
							  {2, 4, 7, 10, 14},
							  {0, 4, 8, 10, 12},
							  {2, 4, 6, 10, 14}
							};

Lines::Lines()
{
	m_iLinesPlayed = 0;

	m_fTotalWin = 0;
	m_fMax = 0;
	m_iMaxLine = -1;
	m_cMax = '0';
}

Lines::~Lines()
{
}

void Lines::SetResult(std::string result, int iLines)
{
	m_iLinesPlayed = iLines;

	m_strResult = result;
	GenLines();

	Calculate();
	GenAnimate();
}

void Lines::GenLines()
{
	for(int iLine = 0; iLine < m_iLinesPlayed; iLine++)
	{
		m_strLines[iLine] = "";

		for(int iPos = 0; iPos < 5; iPos++)
			m_strLines[iLine] += m_strResult[m_Lines[iLine][iPos]];
	}
}

int Lines::GetTotalWin() const
{
	return m_fTotalWin;
}

void Lines::Calculate()
{
	m_fTotalWin = 0;
	m_fMax = 0;
	m_iMaxLine = -1;
	m_cMax = '0';

	for(int i = 0 ; i < m_iLinesPlayed ; i ++)
	{
		if(m_strLines[i][0] == m_strLines[i][1] && m_strLines[i][1] == m_strLines[i][2])
		{
			if(m_strLines[i][2] == m_strLines[i][3])
			{
				if(m_strLines[i][3] == m_strLines[i][4])
					Process5(i);
				else
					Process4(i, 0);
			}
			else
				Process3(i, 0);
		}
		else if (m_strLines[i][1] == m_strLines[i][2] && m_strLines[i][2] == m_strLines[i][3])
		{
			if (m_strLines[i][3] == m_strLines[i][4])
				Process4(i, 1);
			else
				Process3(i, 1);
		}
		else if (m_strLines[i][2] == m_strLines[i][3] && m_strLines[i][3]== m_strLines[i][4])
			Process3(i, 2);
	}
}

bool Lines::HasSpecial()
{
	for ( int i = 0 ; i < 15 ; i ++)
	{
		if ( m_strResult[i] == g_FigureID_6)
			return true;
	}
	return false;
}

void Lines::SetAnimate(std::string newAnimate)
{
	m_strAnimate = newAnimate;
}

void Lines::GenAnimate()
{
	m_strAnimate = "000000000000000";

	if(HasSpecial())
	{
		for(int i = 0; i < 15; i++)
			if(m_strResult[i] == g_FigureID_6)
				m_strAnimate[i] = '1';
	}
	else if(m_fTotalWin == 0)
		return;
	else
	{
		//TODO
		for(int i = 0; i < 5; i++)
			if (m_strLines[m_iMaxLine][i] == m_cMax)
				m_strAnimate[m_Lines[m_iMaxLine][i]] = '1';
	}
}

void Lines::Process3(int iLine, int iPos)
{
	switch(m_strLines[iLine][iPos])
	{
	case g_FigureID_1 :
		m_fTotalWin += g_LinesFigure1x3;
		CheckMax(g_LinesFigure1x3, g_FigureID_1, iLine);
		break;

	case g_FigureID_2 :
		m_fTotalWin += g_LinesFigure2x3;
		CheckMax(g_LinesFigure2x3, g_FigureID_2, iLine);
		break;

	case g_FigureID_3 :
		m_fTotalWin += g_LinesFigure3x3;
		CheckMax(g_LinesFigure3x3, g_FigureID_3, iLine);
		break;

	case g_FigureID_4 :
		m_fTotalWin += g_LinesFigure4x3;
		CheckMax(g_LinesFigure4x3, g_FigureID_4, iLine);
		break;

	case g_FigureID_5 :
		m_fTotalWin += g_LinesFigure5x3;
		CheckMax(g_LinesFigure5x3, g_FigureID_5, iLine);
		break;
	}
}

void Lines::Process4(int iLine, int iPos)
{
	switch(m_strLines[iLine][iPos])
	{
	case g_FigureID_1 :
		m_fTotalWin += g_LinesFigure1x4;
		CheckMax(g_LinesFigure1x4, g_FigureID_1, iLine);
		break;

	case g_FigureID_2 :
		m_fTotalWin += g_LinesFigure2x4;
		CheckMax(g_LinesFigure2x4, g_FigureID_2, iLine);
		break;

	case g_FigureID_3 :
		m_fTotalWin += g_LinesFigure3x4;
		CheckMax(g_LinesFigure3x4, g_FigureID_3, iLine);
		break;

	case g_FigureID_4 :
		m_fTotalWin += g_LinesFigure4x4;
		CheckMax(g_LinesFigure4x4, g_FigureID_4, iLine);
		break;

	case g_FigureID_5 :
		m_fTotalWin += g_LinesFigure5x4;
		CheckMax(g_LinesFigure5x4, g_FigureID_5, iLine);
		break;
	}
}

void Lines::Process5(int iLine)
{
	switch(m_strLines[iLine][0])
	{
	case g_FigureID_1 :
		m_fTotalWin += g_LinesFigure1x5;
		CheckMax(g_LinesFigure1x5, g_FigureID_1, iLine);
		break;

	case g_FigureID_2 :
		m_fTotalWin += g_LinesFigure2x5;
		CheckMax(g_LinesFigure2x5, g_FigureID_2, iLine);
		break;

	case g_FigureID_3 :
		m_fTotalWin += g_LinesFigure3x5;
		CheckMax(g_LinesFigure3x5, g_FigureID_3, iLine);
		break;

	case g_FigureID_4 :
		m_fTotalWin += g_LinesFigure4x5;
		CheckMax(g_LinesFigure4x5, g_FigureID_4, iLine);
		break;

	case g_FigureID_5 :
		m_fTotalWin += g_LinesFigure5x5;
		CheckMax(g_LinesFigure5x5, g_FigureID_5, iLine);
		break;
	}
}

void Lines::CheckMax(int fMultiplier, char cFigure, int iLine)
{
	if (m_fMax < fMultiplier)
	{
		m_fMax = fMultiplier;
		m_iMaxLine = iLine;
		m_cMax = cFigure;
	}
}

std::string Lines::GetAnimate() const
{
	return m_strAnimate;
}











