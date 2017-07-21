#include "Figure.h"

SDL_Texture* Figure::m_TextureFigures = NULL;
SDL_Texture* Figure::m_TextureBackground = NULL;

Figure::Figure()
{
	m_bIsAnimated = false;
	m_Renderer = NULL;
	m_TextureFigures = NULL;
	m_TextureBackground = NULL;
}

Figure::Figure(SDL_Renderer* newRenderer)
{
	m_bIsAnimated = false;

	m_Renderer = newRenderer;
	if(!m_TextureFigures)
	{
		m_TextureFigures = IMG_LoadTexture(m_Renderer,g_Figure);
		if (m_TextureFigures == NULL)
			std::cerr << "Failed to load texture Figures!!! SDL ERROR: " << IMG_GetError() << std::endl;
	}
	if(!m_TextureBackground)
	{
		m_TextureBackground = IMG_LoadTexture(m_Renderer, g_GameBackground);
		if (m_TextureBackground == NULL)
			std::cerr << "Failed to load texture Background!! SDL ERROR: " << IMG_GetError() << std::endl;
	}
	m_RectFigure.w = g_FigureSize;
	m_RectFigure.h = g_FigureSize;
	m_RectFigure.y = 0;
	Rand();
}

Figure::~Figure()
{
	SDL_DestroyRenderer(m_Renderer);
	m_Renderer = NULL;

	SDL_DestroyTexture(m_TextureFigures);
	m_TextureFigures = NULL;

	SDL_DestroyTexture(m_TextureBackground);
	m_TextureBackground = NULL;
}

void Figure::Render(bool UpdateOnly)
{
	if (!m_TextureFigures || !m_Renderer || !m_TextureBackground)
		return;

	if(UpdateOnly)
	{
		if(m_bIsAnimated)
			Render(false);
	}
	else
	{
		Clear();
		if(m_bIsAnimated)
		{
			if ( SDL_GetTicks() - m_uiTimer >= 200)
			{
				m_uiTimer = SDL_GetTicks();
				m_RectFigure.y += g_FigureSize;
				if ( m_RectFigure.y >= 3 * g_FigureSize)
					m_RectFigure.y = 0;
			}
		}
		SDL_Rect tempRect;
		tempRect.x = m_iX;
		tempRect.y = m_iY;
		tempRect.w = g_FigureSize;
		tempRect.h = g_FigureSize;
		SDL_RenderCopy(m_Renderer, m_TextureFigures, &m_RectFigure, &tempRect);
	}
}

void Figure::SetX(int NewX)
{
	Clear();
	m_iX = NewX;
}

void Figure::SetY(int NewY)
{
	Clear();
	m_iY = NewY;
}

void Figure::Play()
{
	m_uiTimer = SDL_GetTicks();
	m_bIsAnimated = true;
}

void Figure::Pause()
{
	m_RectFigure.y = 0;
	m_bIsAnimated = false;
	Render(false);
}

void Figure::Rand()
{
	int iNum;
	iNum = rand() % 5;
	m_RectFigure.x = iNum * g_FigureSize;
	switch(iNum)
	{
		case '0' : m_cCurFigure = g_FigureID_1; break;
		case '1' : m_cCurFigure = g_FigureID_2; break;
		case '2' : m_cCurFigure = g_FigureID_3; break;
		case '3' : m_cCurFigure = g_FigureID_4; break;
		case '4' : m_cCurFigure = g_FigureID_5; break;
	}
	Render(false);
}

void Figure::MakeSpacial()
{
	m_RectFigure.x = g_FigureSize * 5;
	m_cCurFigure = g_FigureID_6;
}

void Figure::Clear()
{
	SDL_Rect tempRect;
	tempRect.x = m_iX;
	tempRect.y = m_iY;
	tempRect.w = g_FigureSize;
	tempRect.h = g_FigureSize;
	SDL_RenderCopy(m_Renderer,m_TextureBackground, &tempRect, &tempRect);
}

char Figure::GetCurFigure() const
{
	return m_cCurFigure;
}










