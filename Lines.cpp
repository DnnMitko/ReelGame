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

	for ( int i = 0 ; i < 15 ; i ++)
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
							m_fTotalWin += 3.2;
							if (fMax < 3.2)
							{
								fMax = 3.2;
								iMaxLine = i;
								cMax = '1';
							}
							break;

						case '2' :
							m_fTotalWin += 3.4;
							if  (fMax < 3.4)
							{
								fMax = 3.4;
								iMaxLine = i;
								cMax = '2';
							}
							break;

						case '3' :
							m_fTotalWin += 3.5;
							if (fMax < 3.5)
							{
								fMax = 3.5;
								iMaxLine = i;
								cMax = '3';
							}
							break;

						case '4' :
							m_fTotalWin += 3.8;
							if ( fMax < 3.8)
							{
								fMax = 3.8;
								iMaxLine = i;
								cMax = '4';
							}
							break;

						case '5' :
							m_fTotalWin += 4.0;
							if (fMax < 4.0)
							{
								fMax = 4.0;
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
							m_fTotalWin += 2.2;
							if (fMax < 2.2)
							{
								fMax = 2.2;
								iMaxLine = i;
								cMax = '1';
							}
							break;

						case '2' :
							m_fTotalWin += 2.4;
							if (fMax < 2.4)
							{
								fMax = 2.2;
								iMaxLine = i;
								cMax = '2';
							}
							break;

						case '3' :
							m_fTotalWin += 2.5;
							if (fMax < 2.5)
							{
								fMax = 2.5;
								iMaxLine = i;
								cMax = '3';
							}
							break;

						case '4' :
							m_fTotalWin += 2.8;
							if (fMax < 2.8)
							{
								fMax = 2.8;
								iMaxLine = i;
								cMax = '4';
							}
							break;

						case '5' :
							m_fTotalWin += 3.0;
							if (fMax < 3.0)
							{
								fMax = 3.0;
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
						m_fTotalWin += 1.2;
						if (fMax < 1.2)
						{
							fMax = 1.2;
							iMaxLine = i;
							cMax = '1';
						}
						break;

					case '2' :
						m_fTotalWin += 1.4;
						if (fMax < 1.4)
						{
							fMax = 1.4;
							iMaxLine = i;
							cMax = '2';
						}
						break;

					case '3' :
						m_fTotalWin += 1.5;
						if (fMax < 1.5)
						{
							fMax = 1.5;
							iMaxLine = i;
							cMax = '3';
						}
						break;

					case '4' :
						m_fTotalWin += 1.8;
						if (fMax < 1.8)
						{
							fMax = 1.8;
							iMaxLine = i;
							cMax = '4';
						}
						break;

					case '5' :
						m_fTotalWin += 2.0;
						if (fMax < 2.0)
						{
							fMax = 2.0;
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
						m_fTotalWin += 2.2;
						if (fMax < 2.2)
						{
							fMax = 2.2;
							iMaxLine = i;
							cMax = '1';
						}
						break;

					case '2' :
						m_fTotalWin += 2.4;
						if (fMax < 2.4)
						{
							fMax = 2.4;
							iMaxLine = i;
							cMax = '2';
						}
						break;

					case '3' :
						m_fTotalWin += 2.5;
						if (fMax < 2.5)
						{
							fMax = 2.5;
							iMaxLine = i;
							cMax = '3';
						}
						break;

					case '4' :
						m_fTotalWin += 2.8;
						if (fMax < 2.8)
						{
							fMax = 2.8;
							iMaxLine = i;
							cMax = '4';
						}
						break;

					case '5' :
						m_fTotalWin += 3.0;
						if (fMax < 3.0)
						{
							fMax = 3.0;
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
						m_fTotalWin += 1.2;
						if (fMax < 1.2)
						{
							fMax = 1.2;
							iMaxLine = i;
							cMax = '1';
						}
						break;

					case '2' :
						m_fTotalWin += 1.4;
						if (fMax < 1.4)
						{
							fMax = 1.4;
							iMaxLine = i;
							cMax = '2';
						}
						break;

					case '3' :
						m_fTotalWin += 1.5;
						if (fMax < 1.5)
						{
							fMax = 1.5;
							iMaxLine = i;
							cMax = '3';
						}
						break;

					case '4' :
						m_fTotalWin += 1.8;
						if (fMax < 1.8)
						{
							fMax = 1.8;
							iMaxLine = i;
							cMax = '4';
						}
						break;

					case '5' :
						m_fTotalWin += 2.0;
						if (fMax < 2.0)
						{
							fMax = 2.0;
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
					m_fTotalWin += 1.2;
					if (fMax < 1.2)
					{
						fMax = 1.2;
						iMaxLine = i;
						cMax = '1';
					}
					break;

				case '2' :
					m_fTotalWin += 1.4;
					if (fMax < 1.4)
					{
						fMax = 1.4;
						iMaxLine = i;
						cMax = '2';
					}
					break;

				case '3' :
					m_fTotalWin += 1.5;
					if (fMax < 1.5)
					{
						fMax = 1.5;
						iMaxLine = i;
						cMax = '3';
					}
					break;

				case '4' :
					m_fTotalWin += 1.8;
					if (fMax < 1.8)
					{
						fMax = 1.8;
						iMaxLine = i;
						cMax = '4';
					}
					break;

				case '5' :
					m_fTotalWin += 2.0;
					if (fMax < 2.0)
					{
						fMax = 2.0;
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











