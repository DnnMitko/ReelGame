#include "Figure.h"

SDL_Texture* Figure::m_TextureFigures = NULL;
SDL_Texture* Figure::m_TextureBackground = NULL;

Figure::Figure()
{
	m_Renderer = NULL;

	m_TextureFigures = NULL;
	m_TextureBackground = NULL;

	m_bIsAnimated = false;

	m_uiTimer = 0;

	m_iX = 0;
	m_iY = 0;
}

Figure::Figure(SDL_Renderer* newRenderer)
{
	m_bIsAnimated = false;

	// Set renderer.
	m_Renderer = newRenderer;

	// If textures were not loaded, load it.
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

	// Make source rectangle and generate a random figure.
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

	// If we're looking for updates only.
	if(UpdateOnly)
	{
		// If it's animated, draw the figure.
		if(m_bIsAnimated)
			Render(false);
	}
	else
	{
		// If it's animated, check if it's time to change animation frame.
		if(m_bIsAnimated)
		{
			if ( SDL_GetTicks() - m_uiTimer >= g_SlotAnimationDelay)
			{
				// Reset timer.
				m_uiTimer = SDL_GetTicks();

				// Clear the image.
				Clear();

				// Move to next frame of animation.
				m_RectFigure.y += g_FigureSize;
				if ( m_RectFigure.y >= 3 * g_FigureSize)
					m_RectFigure.y = 0;
			}
			// Draw figure.
			Draw();
		}
		else
			Draw();
	}
}

void Figure::SetX(int NewX)
{
	m_iX = NewX;
}

void Figure::SetY(int NewY)
{
	m_iY = NewY;
}

int Figure::GetY() const
{
	return m_iY;
}

void Figure::Play()
{
	// Start timer.
	m_uiTimer = SDL_GetTicks();

	// Raise animated flag.
	m_bIsAnimated = true;
}

void Figure::Pause()
{
	// Set to default frame.
	m_RectFigure.y = 0;

	// Lower animation flag.
	m_bIsAnimated = false;

	// Redraw the figure to show the default frame.
	Clear();
	Render(false);
}

void Figure::Rand()
{
	// Generate a figure and set the source rectangle to it.
	int iNum;
	iNum = rand() % 5;
	m_RectFigure.x = iNum * g_FigureSize;
}

void Figure::SetFigure(char cNewFigure)
{
	// Set source rectangle to the appropriate figure.
	switch(cNewFigure)
	{
		case g_FigureID_1 : m_RectFigure.x = 0; break;
		case g_FigureID_2 : m_RectFigure.x = g_FigureSize; break;
		case g_FigureID_3 : m_RectFigure.x = 2 * g_FigureSize; break;
		case g_FigureID_4 :	m_RectFigure.x = 3 * g_FigureSize; break;
		case g_FigureID_5 :	m_RectFigure.x = 4 * g_FigureSize; break;
		case g_FigureID_6 :	m_RectFigure.x = 5 * g_FigureSize; break;
	}
}

void Figure::Clear()
{
	// Cut a rectangle from the game background and cover the figure.
	SDL_Rect tempRect;
	tempRect.x = m_iX;
	tempRect.y = m_iY;
	tempRect.w = g_FigureSize;
	tempRect.h = g_FigureSize;
	SDL_RenderCopy(m_Renderer, m_TextureBackground, &tempRect, &tempRect);
}

void Figure::Draw()
{
	SDL_Rect tempRect;
	tempRect.x = m_iX;
	tempRect.y = m_iY;
	tempRect.w = g_FigureSize;
	tempRect.h = g_FigureSize;
	SDL_RenderCopy(m_Renderer, m_TextureFigures, &m_RectFigure, &tempRect);

	// If it's animated, draw an outline.
	if(m_bIsAnimated)
	{
		SDL_SetRenderDrawColor(m_Renderer, 0xF0, 0xF0, 0xF0, 0xFF);
		SDL_RenderDrawRect(m_Renderer, &tempRect);
	}
}

void Figure::Copy(Figure* other)
{
	// Copy the position and figure choice of another object.
	this->m_RectFigure = other->m_RectFigure;

	this->m_iX = other->m_iX;
	this->m_iY = other->m_iY;
}









