#include "Lines.h"

Lines::Lines()
{
	m_fTotalWin = 0;

	m_Line[0] = {1, 4, 7, 10, 13};
	m_Line[1] = {0, 3, 6, 9, 12};
	m_Line[2] = {2, 5, 8, 11, 14};
	m_Line[3] = {1, 4, 6, 10, 13};
	m_Line[4] = {1, 4, 8, 10, 13};
	m_Line[5] = {1, 3, 6, 9, 13};
	m_Line[6] = {1, 5, 8, 11, 13};
	m_Line[7] = {0, 3, 7, 11, 14};
	m_Line[8] = {2, 5, 7, 9, 12};
	m_Line[9] = {0, 3, 7, 9, 12};
	m_Line[10] = {2, 5, 7, 11, 14};
	m_Line[11] = {0, 4, 7, 10, 12};
	m_Line[12] = {2, 4, 7, 10, 14};
	m_Line[13] = {0, 4, 8, 10, 12};
	m_Line[14] = {2, 4, 6, 10, 14};

}

Lines::~Lines()
{
	// TODO Auto-generated destructor stub
}

void Lines::SetResult(std::string resutl)
{
	m_strResult = resutl;
}

void Lines::GenLines()
{
	for ( int i = 0 ; i < 15 ; i ++)
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
	float fMax = 0;
	int iMaxLine = -1;
	char cMax = '0';

	for ( int i = 0 ; i < g_LinesMax ; i ++)
	{
		if (m_strLine[i][0] == m_strLine[i][1] && m_strLine[i][1] == m_strLine[i][2])

			{
				if (m_strLine[i][2] == m_strLine[i][3])
				{
					if (m_strLine[i][3] == m_strLine[i][4])
					{
						switch(m_strLine[i][0])
						{
						case '1' :
							m_fTotalWin += g_LinesFigure1x5;
							if (fMax < g_LinesFigure1x5)
							{
								fMax = g_LinesFigure1x5;
								iMaxLine = i;
								cMax = '1';
							}
							break;

						case '2' :
							m_fTotalWin += g_LinesFigure2x5;
							if  (fMax < g_LinesFigure2x5)
							{
								fMax = g_LinesFigure2x5;
								iMaxLine = i;
								cMax = '2';
							}
							break;

						case '3' :
							m_fTotalWin += g_LinesFigure3x5;
							if (fMax < g_LinesFigure3x5)
							{
								fMax = g_LinesFigure3x5;
								iMaxLine = i;
								cMax = '3';
							}
							break;

						case '4' :
							m_fTotalWin += g_LinesFigure4x5;
							if ( fMax < g_LinesFigure4x5)
							{
								fMax = g_LinesFigure4x5;
								iMaxLine = i;
								cMax = '4';
							}
							break;

						case '5' :
							m_fTotalWin += g_LinesFigure5x5;
							if (fMax < g_LinesFigure5x5)
							{
								fMax = g_LinesFigure5x5;
								iMaxLine = i;
								cMax = '5';
							}
							break;
						}
					}
					else
					{
						switch(m_strLine[i][0])
						{
						case '1' :
							m_fTotalWin += g_LinesFigure1x4;
							if (fMax < g_LinesFigure1x4)
							{
								fMax = g_LinesFigure1x4;
								iMaxLine = i;
								cMax = '1';
							}
							break;

						case '2' :
							m_fTotalWin += g_LinesFigure2x4;
							if (fMax < g_LinesFigure2x4)
							{
								fMax = g_LinesFigure2x4;
								iMaxLine = i;
								cMax = '2';
							}
							break;

						case '3' :
							m_fTotalWin += g_LinesFigure3x4;
							if (fMax < g_LinesFigure3x4)
							{
								fMax = g_LinesFigure3x4;
								iMaxLine = i;
								cMax = '3';
							}
							break;

						case '4' :
							m_fTotalWin += g_LinesFigure4x4;
							if (fMax < g_LinesFigure4x4)
							{
								fMax = g_LinesFigure4x4;
								iMaxLine = i;
								cMax = '4';
							}
							break;

						case '5' :
							m_fTotalWin += g_LinesFigure5x4;
							if (fMax < g_LinesFigure5x4)
							{
								fMax = g_LinesFigure5x4;
								iMaxLine = i;
								cMax = '5';
							}
							break;
						}
					}
				}
				else
				{
					switch(m_strLine[i][0])
					{
					case '1' :
						m_fTotalWin += g_LinesFigure1x3;
						if (fMax < g_LinesFigure1x3)
						{
							fMax = g_LinesFigure1x3;
							iMaxLine = i;
							cMax = '1';
						}
						break;

					case '2' :
						m_fTotalWin += g_LinesFigure2x3;
						if (fMax < g_LinesFigure2x3)
						{
							fMax = g_LinesFigure2x3;
							iMaxLine = i;
							cMax = '2';
						}
						break;

					case '3' :
						m_fTotalWin += g_LinesFigure3x3;
						if (fMax < g_LinesFigure3x3)
						{
							fMax = g_LinesFigure3x3;
							iMaxLine = i;
							cMax = '3';
						}
						break;

					case '4' :
						m_fTotalWin += g_LinesFigure4x3;
						if (fMax < g_LinesFigure4x3)
						{
							fMax = g_LinesFigure4x3;
							iMaxLine = i;
							cMax = '4';
						}
						break;

					case '5' :
						m_fTotalWin += g_LinesFigure5x3;
						if (fMax < g_LinesFigure5x3)
						{
							fMax = g_LinesFigure5x3;
							iMaxLine = i;
							cMax = '5';
						}
						break;
					}
				}
			}
			else if (m_strLine[i][1] == m_strLine[i][2] && m_strLine[i][2] == m_strLine[i][3])
			{
				if (m_strLine[i][3] == m_strLine[i][4])
				{
					switch(m_strLine[i][1])
					{
					case '1' :
						m_fTotalWin += g_LinesFigure1x4;
						if (fMax < g_LinesFigure1x4)
						{
							fMax = g_LinesFigure1x4;
							iMaxLine = i;
							cMax = '1';
						}
						break;

					case '2' :
						m_fTotalWin += g_LinesFigure2x4;
						if (fMax < g_LinesFigure2x4)
						{
							fMax = g_LinesFigure2x4;
							iMaxLine = i;
							cMax = '2';
						}
						break;

					case '3' :
						m_fTotalWin += g_LinesFigure3x4;
						if (fMax < g_LinesFigure3x4)
						{
							fMax = g_LinesFigure3x4;
							iMaxLine = i;
							cMax = '3';
						}
						break;

					case '4' :
						m_fTotalWin += g_LinesFigure4x4;
						if (fMax < g_LinesFigure4x4)
						{
							fMax = g_LinesFigure4x4;
							iMaxLine = i;
							cMax = '4';
						}
						break;

					case '5' :
						m_fTotalWin += g_LinesFigure5x4;
						if (fMax < g_LinesFigure5x4)
						{
							fMax = g_LinesFigure5x4;
							iMaxLine = i;
							cMax = '5';
						}
						break;
					}
				}
				else
				{
					switch(m_strLine[i][1])
					{
					case '1' :
						m_fTotalWin += g_LinesFigure1x3;
						if (fMax < g_LinesFigure1x3)
						{
							fMax = g_LinesFigure1x3;
							iMaxLine = i;
							cMax = '1';
						}
						break;

					case '2' :
						m_fTotalWin += g_LinesFigure2x3;
						if (fMax < g_LinesFigure2x3)
						{
							fMax = g_LinesFigure2x3;
							iMaxLine = i;
							cMax = '2';
						}
						break;

					case '3' :
						m_fTotalWin += g_LinesFigure3x3;
						if (fMax < g_LinesFigure3x3)
						{
							fMax = g_LinesFigure3x3;
							iMaxLine = i;
							cMax = '3';
						}
						break;

					case '4' :
						m_fTotalWin += g_LinesFigure4x3;
						if (fMax < g_LinesFigure4x3)
						{
							fMax = g_LinesFigure4x3;
							iMaxLine = i;
							cMax = '4';
						}
						break;

					case '5' :
						m_fTotalWin += g_LinesFigure5x3;
						if (fMax < g_LinesFigure5x3)
						{
							fMax = g_LinesFigure5x3;
							iMaxLine = i;
							cMax = '5';
						}
						break;
					}
				}
			}
			else if (m_strLine[i][2] == m_strLine[i][3] && m_strLine[i][3]== m_strLine[i][4])
			{
				switch(m_strLine[i][2])
				{
				case '1' :
					m_fTotalWin += g_LinesFigure1x3;
					if (fMax < g_LinesFigure1x3)
					{
						fMax = g_LinesFigure1x3;
						iMaxLine = i;
						cMax = '1';
					}
					break;

				case '2' :
					m_fTotalWin += g_LinesFigure2x3;
					if (fMax < g_LinesFigure2x3)
					{
						fMax = g_LinesFigure2x3;
						iMaxLine = i;
						cMax = '2';
					}
					break;

				case '3' :
					m_fTotalWin += g_LinesFigure3x3;
					if (fMax < g_LinesFigure3x3)
					{
						fMax = g_LinesFigure3x3;
						iMaxLine = i;
						cMax = '3';
					}
					break;

				case '4' :
					m_fTotalWin += g_LinesFigure4x3;
					if (fMax < g_LinesFigure4x3)
					{
						fMax = g_LinesFigure4x3;
						iMaxLine = i;
						cMax = '4';
					}
					break;

				case '5' :
					m_fTotalWin += g_LinesFigure5x3;
					if (fMax < g_LinesFigure5x3)
					{
						fMax = g_LinesFigure5x3;
						iMaxLine = i;
						cMax = '5';
					}
					break;
				}
			}
	}
}

bool Lines::HasSpecial()
{
	for ( int i = 0 ; i < 15 ; i ++)
	{
		if ( m_strResult[i] == '6')
			return true;
	}
	return false;
}

void Lines::GenAnimate(int iMaxLine, char cMax)
{
	m_strAnimate = "000000000000000";

	if (m_Line[iMaxLine].num1 == cMax)
	{
		m_strAnimate[m_Line[iMaxLine].num1] = '1';
	}
	if (m_Line[iMaxLine].num2 == cMax)
	{
		m_strAnimate[m_Line[iMaxLine].num2] = '1';
	}
	if (m_Line[iMaxLine].num3 == cMax)
	{
		m_strAnimate[m_Line[iMaxLine].num3] = '1';
	}
	if (m_Line[iMaxLine].num4 == cMax)
	{
		m_strAnimate[m_Line[iMaxLine].num4] = '1';
	}
	if (m_Line[iMaxLine].num5 == cMax)
	{
		m_strAnimate[m_Line[iMaxLine].num5] = '1';
	}
}

std::string Lines::GetAnimate() const
{
	return m_strAnimate;
}











