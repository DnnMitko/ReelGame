#include "Slot.h"

Slot::Slot()
{
	m_Renderer = NULL;

	m_TextureBackground = NULL;

	for(int i = 0; i < 4; i++)
		m_Figures[i] = NULL;

	m_bIsRolling = false;
	m_bPutInPlace = false;

	m_iX = 0;
	m_iY = 0;
	m_uiTimer = 0;
	m_iPos = 2;
}

Slot::Slot(SDL_Renderer* newRenderer)
{
	m_Renderer = newRenderer;

	m_bIsRolling = false;
	m_bPutInPlace = false;

	m_TextureBackground = IMG_LoadTexture(m_Renderer, g_GameBackground);
	if (m_TextureBackground == NULL)
		std::cerr << "Failed to load texture Background!! SDL ERROR: " << IMG_GetError() << std::endl;

	for(int i = 0; i < 4; i++)
		m_Figures[i] = new Figure(m_Renderer);

	m_iX = 0;
	m_iY = 0;
	m_uiTimer = 0;
	m_iPos = 2;
}

Slot::~Slot()
{
	SDL_DestroyTexture(m_TextureBackground);
	m_TextureBackground = NULL;

	for(int i = 0; i < 4; i++)
	{
		delete m_Figures[i];
		m_Figures[i] = NULL;
	}
}

void Slot::Render(bool UpdateOnly)
{
	if(!m_Renderer || !m_TextureBackground)
		return;

	if(m_bIsRolling)
		ProcessRolling(UpdateOnly);

	else if(m_bPutInPlace)
		ProcessPuttingInPlace(UpdateOnly);

	for(int i = 0; i < 4; i++)
		m_Figures[i]->Render(UpdateOnly);

	if(!UpdateOnly)
		CoverUp();
}

void Slot::SetX(int newX)
{
	m_iX = newX;

	for(int i = 0; i < 4; i++)
		m_Figures[i]->SetX(m_iX);
}

void Slot::SetY(int newY)
{
	m_iY = newY;

	int iTempY = m_iY - g_FigureSize;
	for(int i = 0; i < 4; i++)
	{
		m_Figures[i]->SetY(iTempY);

		iTempY += g_FigureSize;
	}
}

void Slot::Spin(bool bGenSpecial)
{
	m_bIsRolling = true;

	GenNext(bGenSpecial);

	m_uiTimer = SDL_GetTicks();
}

bool Slot::HasStopped() const
{
	if(!m_bIsRolling && !m_bPutInPlace)
		return true;

	return false;
}

void Slot::Animate(std::string strAnimateMap)
{
	for(int i = 1; i < 4; i++)
		if(strAnimateMap[i - 1] == '1')
			m_Figures[i]->Play();
}

void Slot::Stop()
{
	for(int i = 1; i < 4; i++)
		m_Figures[i]->Pause();
}

std::string Slot::GetResult() const
{
	return m_strResult;
}

void Slot::GenNext(bool bGenSpecial)
{
	m_strResult = "";

	int iNum;

	for(int i = 0; i < 3; i++)
	{
		iNum = rand() % 5;

		switch(iNum)
		{
			case 0 : m_strResult += g_FigureID_1; break;
			case 1 : m_strResult += g_FigureID_2; break;
			case 2 : m_strResult += g_FigureID_3; break;
			case 3 : m_strResult += g_FigureID_4; break;
			case 4 : m_strResult += g_FigureID_5; break;
		}
	}

	if(bGenSpecial)
		for(int i = 0; i < 2; i++)
		{
			iNum = rand() % 100 + 1;
			if(iNum <= g_SlotSpecialPercent)
			{
				m_strResult[i] = g_FigureID_6;
				break;
			}
		}
}

void Slot::ProcessRolling(bool& UpdateOnly)
{
	if(SDL_GetTicks() - m_uiTimer >= g_SlotRollTime)
	{
		m_bIsRolling = false;
		m_bPutInPlace = true;
	}
	else
	{
		if(m_Figures[0]->GetY() == m_iY)
		{
			CopyUp();
			m_Figures[0]->Rand();
		}
		else
		{
			for(int i = 3; i >= 0; i--)
			{
				m_Figures[i]->Clear();
				m_Figures[i]->SetY(m_Figures[i]->GetY() + g_SlotSpeed);
			}

			UpdateOnly = false;
		}
	}
}

void Slot::ProcessPuttingInPlace(bool& UpdateOnly)
{
	if(m_Figures[0]->GetY() == m_iY)
	{
		if(m_iPos == -1)
		{
			m_bPutInPlace = false;

			CopyUp();

			m_iPos = 2;
		}
		else
		{
			CopyUp();
			m_Figures[0]->SetFigure(m_strResult[m_iPos]);
			m_iPos--;
		}
	}
	else
	{
		for(int i = 3; i >= 0; i--)
		{
			m_Figures[i]->Clear();
			m_Figures[i]->SetY(m_Figures[i]->GetY() + g_SlotSpeed);
		}

		UpdateOnly = false;
	}
}

void Slot::CoverUp()
{
	SDL_Rect tempRect;
	tempRect.x = m_iX;
	tempRect.w = g_FigureSize;
	tempRect.y = m_iY - g_FigureSize;
	tempRect.h = g_FigureSize;

	SDL_RenderCopy(m_Renderer, m_TextureBackground, &tempRect, &tempRect);

	tempRect.y = m_iY + 3 * g_FigureSize;

	SDL_RenderCopy(m_Renderer, m_TextureBackground, &tempRect, &tempRect);
}

void Slot::CopyUp()
{
	m_Figures[3]->Copy(m_Figures[2]);
	m_Figures[2]->Copy(m_Figures[1]);
	m_Figures[1]->Copy(m_Figures[0]);

	m_Figures[0]->SetY(m_iY - g_FigureSize);
}

















