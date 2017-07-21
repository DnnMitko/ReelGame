#include "Info.h"

Info::Info()
{
	m_Rednerer = NULL;

	m_TextrureScreens[0] = NULL;
	m_TextrureScreens[1] = NULL;

	m_Font = NULL;

	m_ButtonNext = NULL;
	m_ButtonExit = NULL;

	m_bHide = false;
	m_bShowFirst = true;
	m_bHasChanged = true;

	m_iX = 0;
	m_iY = 0;
}

Info::Info(SDL_Renderer* newRenderer)
{
	m_Rednerer = newRenderer;

	m_iX = (g_ScreenWidth - g_InfoWidth) / 2;
	m_iY = (g_ScreenHeight - g_InfoHeight) / 2;

	m_bHide = false;
	m_bShowFirst = true;
	m_bHasChanged = true;

	m_TextrureScreens[0] = IMG_LoadTexture(newRenderer, g_InfoScreen1);
	if( m_TextrureScreens[0] == NULL )
		std::cerr << "Failed to load Texture for Info! SDL Error: " << IMG_GetError() << std::endl;

	m_TextrureScreens[1] = IMG_LoadTexture(newRenderer, g_InfoScreen2);
	if( m_TextrureScreens[1] == NULL )
		std::cerr << "Failed to load Texture for Info! SDL Error: " << IMG_GetError() << std::endl;

	m_Font = TTF_OpenFont(g_FontLabel, g_InfoFontSize);

	m_ButtonNext = new Button(m_Rednerer);
	m_ButtonNext->SetFieldSize(g_InfoButtonHeight, g_InfoButtonWidth);
	m_ButtonNext->SetX(m_iX + g_InfoWidth - g_InfoButtonWidth + g_InfoButtonNextOffsetX);
	m_ButtonNext->SetY(m_iY + g_InfoHeight - g_InfoButtonHeight + g_InfoButtonNextOffsetY);
	m_ButtonNext->SetText(g_InforButtonNext[m_bShowFirst], m_Font, SDL_Color{0x00, 0x00, 0x00, 0xFF});

	m_ButtonExit = new Button(m_Rednerer);
	m_ButtonExit->SetFieldSize(g_InfoButtonHeight, g_InfoButtonWidth);
	m_ButtonExit->SetX(m_iX + g_InfoWidth - g_InfoButtonWidth + g_InfoButtonExitOffsetX);
	m_ButtonExit->SetY(m_iY + g_InfoButtonExitOffsetY);
	m_ButtonExit->SetText(g_InfoButtonExit, m_Font, SDL_Color{0x00, 0x00, 0x00, 0xFF});
}

Info::~Info()
{
	SDL_DestroyTexture(m_TextrureScreens[0]);
	SDL_DestroyTexture(m_TextrureScreens[1]);
	m_TextrureScreens[0] = NULL;
	m_TextrureScreens[1] = NULL;

	delete m_ButtonNext;
	delete m_ButtonExit;

	m_ButtonNext = NULL;
	m_ButtonExit = NULL;
}

void Info::Render(bool UpdateOnly)
{
	if(!m_Rednerer || !m_TextrureScreens[0] || !m_TextrureScreens[1] || !m_Font)
		return;

	if(m_bHasChanged)
	{
		m_bHasChanged = false;
		UpdateOnly = false;
	}

	if(!UpdateOnly)
	{
		SDL_Rect tempRect;
		tempRect.x = m_iX;
		tempRect.y = m_iY;
		tempRect.w = g_InfoWidth;
		tempRect.h = g_InfoHeight;

		if(m_bShowFirst)
			SDL_RenderCopy(m_Rednerer, m_TextrureScreens[0], NULL, &tempRect);
		else
			SDL_RenderCopy(m_Rednerer, m_TextrureScreens[1], NULL, &tempRect);

		SDL_SetRenderDrawColor(m_Rednerer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderDrawRect(m_Rednerer, &tempRect);
	}

	m_ButtonNext->Render(UpdateOnly);
	m_ButtonExit->Render(UpdateOnly);
}

void Info::EventHandler(SDL_Event& e)
{
	int x, y;

	if(e.type == SDL_MOUSEBUTTONDOWN)
	{
		SDL_GetMouseState(&x, &y);

		if(m_ButtonNext->IsIn(x, y))
			m_ButtonNext->Press();
		else if(m_ButtonExit->IsIn(x, y))
			m_ButtonExit->Press();
	}
	else if(e.type == SDL_MOUSEBUTTONUP)
	{
		SDL_GetMouseState(&x, &y);

		if(m_ButtonNext->IsIn(x, y) && m_ButtonNext->IsPressed())
		{
			m_bShowFirst = !m_bShowFirst;
			m_ButtonNext->SetText(g_InforButtonNext[m_bShowFirst], m_Font, SDL_Color{0x00, 0x00, 0x00, 0xFF});

			m_bHasChanged = true;
		}
		else if(m_ButtonExit->IsIn(x, y) && m_ButtonExit->IsPressed())
		{
			m_bHide = true;
		}

		m_ButtonNext->Release();
		m_ButtonExit->Release();
	}
}

bool Info::GetHide() const
{
	return m_bHide;
}

void Info::Reset()
{
	m_bHide = false;
	m_bShowFirst = true;
	m_bHasChanged = true;
}






















