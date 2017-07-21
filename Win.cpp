#include "Win.h"

Win::Win() : State()
{
	NullAll();
}

Win::Win(SDL_Renderer* newRenderer) : State(newRenderer)
{
	m_TextureBackground = IMG_LoadTexture(m_Renderer, g_WinBackground);
	if(m_TextureBackground == NULL)
		std::cerr << "Failed to load TextureBackground! SDL Error: " << IMG_GetError() << std::endl;

	m_iX = (g_ScreenWidth - g_WinWidth) / 2;
	m_iY = (g_ScreenHeight - g_WinHeight) / 2;

	m_FontCredits = TTF_OpenFont(g_FontLabel, g_WinFontSizeCredits);
	if(m_FontCredits == NULL)
			std::cerr << "Failed to load Label Font! SDL Error: " << TTF_GetError() << std::endl;

	m_FontTitle = TTF_OpenFont(g_FontTitle, g_WinFontSizeSign);
	if(m_FontCredits == NULL)
			std::cerr << "Failed to load Win Font! SDL Error: " << TTF_GetError() << std::endl;

	m_LabelWinSign = new Label(m_Renderer);
	m_LabelWinSign->SetText(g_WinSign, m_FontTitle, g_ColorYellow);
	m_LabelWinSign->SetX(m_iX + (g_WinWidth - m_LabelWinSign->GetWidth()) / 2);
	m_LabelWinSign->SetY(m_iY + (g_WinHeight - m_LabelWinSign->GetHeight()) / 2 + g_WinSignOffsetY);

	m_TextFieldCredits = new TextField(m_Renderer);
	m_TextFieldCredits->SetFieldSize(g_WinCreditHeight, g_WinCreditsWidth);
	m_TextFieldCredits->SetX(m_iX + (g_WinWidth - m_TextFieldCredits->GetWidth()) / 2);
	m_TextFieldCredits->SetY(m_iY + (g_WinHeight - m_TextFieldCredits->GetHeight()) / 2 + g_WinCreditOffsetY);

	m_Sound = Mix_LoadWAV(g_WinSound);

	m_uiCredits = 0;

	m_uiTimer = 0;
}

Win::~Win()
{
	SDL_DestroyTexture(m_TextureBackground);

	delete m_LabelWinSign;
	delete m_TextFieldCredits;

	TTF_CloseFont(m_FontCredits);
	TTF_CloseFont(m_FontTitle);

	Mix_FreeChunk(m_Sound);

	NullAll();
}

void Win::EventHandler(SDL_Event& e)
{
	if(e.type == SDL_MOUSEBUTTONDOWN && !m_bTransitionIn && !m_bTransitionOut)
	{
		int x, y;
		SDL_GetMouseState(&x, &y);

		if(x >= m_iX && x <= (m_iX + g_WinWidth))
			if(y >= m_iY && y <= (m_iY + g_WinHeight))
			{
				m_bTransitionOut = true;
			}
	}
}

void Win::Render(bool UpdateOnly)
{
	if(!m_Renderer || !m_TextureBackground || !m_FontCredits || !m_FontTitle)
		return;

	SDL_Rect tempRect;
	tempRect.h = g_WinHeight;
	tempRect.w = g_WinWidth;
	tempRect.x = m_iX;
	tempRect.y = m_iY;

	SDL_RenderCopy(m_Renderer, m_TextureBackground, NULL, &tempRect);

	SDL_SetRenderDrawColor(m_Renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderDrawRect(m_Renderer, &tempRect);

	if(m_bTransitionIn)
		TransitionIn();

	else if(m_bTransitionOut)
		TransitionOut();

	else if(SDL_GetTicks() - m_uiTimer >= g_WinDelay)
		m_bTransitionOut = true;

	m_LabelWinSign->Render(false);
	m_TextFieldCredits->Render(false);
}

void Win::PrepTransitionIn()
{
	m_bTransitionIn = true;

	m_iY = g_WinHeightTransition;

	m_LabelWinSign->SetY(m_iY + (g_WinHeight - m_LabelWinSign->GetHeight()) / 2 + g_WinSignOffsetY);
	m_TextFieldCredits->SetY(m_iY + (g_WinHeight - m_TextFieldCredits->GetHeight()) / 2 + g_WinCreditOffsetY);
}

void Win::SetCredits(unsigned int newCredits)
{
	std::string strCredits;
	std::stringstream ss;

	m_uiCredits = newCredits;
	ss <<  m_uiCredits;
	strCredits = ss.str();

	m_TextFieldCredits->SetText(strCredits, m_FontCredits, g_ColorWhite);
}

void Win::NullAll()
{
	m_TextureBackground = NULL;
	m_LabelWinSign = NULL;
	m_TextFieldCredits = NULL;
	m_FontCredits = NULL;
	m_FontTitle = NULL;

	m_Sound = NULL;

	m_uiCredits = 0;

	m_uiTimer = 0;

	m_iX = 0;
	m_iY = 0;
}

void Win::TransitionIn()
{
	if(m_iY == (g_ScreenHeight - g_WinHeight) / 2)
	{
		m_bTransitionIn = false;

		Mix_PlayChannel(-1, m_Sound, 0);

		m_uiTimer = SDL_GetTicks();
	}
	else
	{
		m_iY += g_TransitionStep;

		m_LabelWinSign->SetY(m_iY + (g_WinHeight - m_LabelWinSign->GetHeight()) / 2 + g_WinSignOffsetY);
		m_TextFieldCredits->SetY(m_iY + (g_WinHeight - m_TextFieldCredits->GetHeight()) / 2 + g_WinCreditOffsetY);
	}
}
void Win::TransitionOut()
{
	if(m_iY + g_WinHeight <= 0)
	{
		m_bTransitionOut = false;
		m_bSwitch = true;
	}
	else
	{
		m_iY -= g_TransitionStep;

		m_LabelWinSign->SetY(m_iY + (g_WinHeight - m_LabelWinSign->GetHeight()) / 2 + g_WinSignOffsetY);
		m_TextFieldCredits->SetY(m_iY + (g_WinHeight - m_TextFieldCredits->GetHeight()) / 2 + g_WinCreditOffsetY);
	}
}
