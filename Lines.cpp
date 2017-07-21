#include "Lines.h"

Lines::Lines()
{
	m_fTotalWin = 0;

	m_Line[0] = (Line){1, 4, 7, 10, 13};
	m_Line[1] = (Line){0, 3, 6, 9, 12};
	m_Line[2] = (Line){2, 5, 8, 11, 14};
	m_Line[3] = (Line){1, 4, 6, 10, 13};
	m_Line[4] = (Line){1, 4, 8, 10, 13};
	m_Line[5] = (Line){1, 3, 6, 9, 13};
	m_Line[6] = (Line){1, 5, 8, 11, 13};
	m_Line[7] = (Line){0, 3, 7, 11, 14};
	m_Line[8] = (Line){2, 5, 7, 9, 12};
	m_Line[9] = (Line){0, 3, 7, 9, 12};
	m_Line[10] = (Line){2, 5, 7, 11, 14};
	m_Line[11] = (Line){0, 4, 7, 10, 12};
	m_Line[12] = (Line){2, 4, 7, 10, 14};
	m_Line[13] = (Line){0, 4, 8, 10, 12};
	m_Line[14] = (Line){2, 4, 6, 10, 14};

	m_fTotalWin = 0;
	m_fMax = 0;
	m_iMaxLine = -1;
	m_cMax = '0';
}

Lines::~Lines()
{
	// TODO Auto-generated destructor stub
}

void Lines::SetResult(std::string result)
{
	m_strResult = result;
	GenLines();

	Calculate();
	GenAnimate();
}

void Lines::GenLines()
{
	for(int i = 0 ; i < g_LinesMax ; i ++)
	{
		m_strLine[i] = m_strResult[m_Line[i].num1]
					 + m_strResult[m_Line[i].num2]
					 + m_strResult[m_Line[i].num3]
					 + m_strResult[m_Line[i].num4]
					 + m_strResult[m_Line[i].num5];
	}
}

float Lines::GetTotalWin() const
{
	return m_fTotalWin;
}

void Lines::Calculate()
{
	m_fTotalWin = 0;
	m_fMax = 0;
	m_iMaxLine = -1;
	m_cMax = '0';

	for(int i = 0 ; i < g_LinesMax ; i ++)
	{
		if(m_strLine[i][0] == m_strLine[i][1] && m_strLine[i][1] == m_strLine[i][2])
		{
			if(m_strLine[i][2] == m_strLine[i][3])
			{
				if(m_strLine[i][3] == m_strLine[i][4])
					Process5(i);
				else
					Process4(i, 0);
			}
			else
				Process3(i, 0);
		}
		else if (m_strLine[i][1] == m_strLine[i][2] && m_strLine[i][2] == m_strLine[i][3])
		{
			if (m_strLine[i][3] == m_strLine[i][4])
				Process4(i, 1);
			else
				Process3(i, 1);
		}
		else if (m_strLine[i][2] == m_strLine[i][3] && m_strLine[i][3]== m_strLine[i][4])
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

void Lines::GenAnimate()
{
	m_strAnimate = "000000000000000";

	if (m_Line[m_iMaxLine].num1 == m_cMax)
	{
		m_strAnimate[m_Line[m_iMaxLine].num1] = '1';
	}
	if (m_Line[m_iMaxLine].num2 == m_cMax)
	{
		m_strAnimate[m_Line[m_iMaxLine].num2] = '1';
	}
	if (m_Line[m_iMaxLine].num3 == m_cMax)
	{
		m_strAnimate[m_Line[m_iMaxLine].num3] = '1';
	}
	if (m_Line[m_iMaxLine].num4 == m_cMax)
	{
		m_strAnimate[m_Line[m_iMaxLine].num4] = '1';
	}
	if (m_Line[m_iMaxLine].num5 == m_cMax)
	{
		m_strAnimate[m_Line[m_iMaxLine].num5] = '1';
	}
}

void Lines::Process3(int iLine, int iPos)
{
	switch(m_strLine[iLine][iPos])
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
	switch(m_strLine[iLine][iPos])
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
	switch(m_strLine[iLine][0])
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

void Lines::CheckMax(float fMultiplier, char cFigure, int iLine)
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











