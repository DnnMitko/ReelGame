#include "Outro.h"

Outro::Outro() : State()
{
	NullAll();
}

Outro::Outro(SDL_Renderer* newRenderer) : State(newRenderer)
{
	m_TextureBackground = IMG_LoadTexture(m_Renderer, g_OutroBackground);
	if(m_TextureBackground == NULL)
		std::cerr << "Failed to load TextureBackground! SDL Error: " << IMG_GetError() << std::endl;

	m_iX = (g_ScreenWidth - g_OutroWidth) / 2;
	m_iY = (g_ScreenHeight - g_OutroHeight) / 2;

	m_LabelWinSign = new Label(m_Renderer);

	m_TextFieldMoney = new TextField(m_Renderer);
	m_TextFieldMoney->SetFieldSize(g_OutroMoneyHeight, g_OutroMoneyWidth);
	m_TextFieldMoney->SetX(m_iX + (g_OutroWidth - m_TextFieldMoney->GetWidth()) / 2);
	m_TextFieldMoney->SetY(m_iY + (g_OutroHeight - m_TextFieldMoney->GetHeight()) / 2 + g_OutroMoneyOffsetY);

	m_FontMoney = TTF_OpenFont(g_FontLabel, g_OutroFontSizeMoney);
	if(m_FontMoney == NULL)
			std::cerr << "Failed to load Label Font! SDL Error: " << TTF_GetError() << std::endl;

	m_FontTitle = TTF_OpenFont(g_FontTitle, g_OutroFontSizeWin);
	if(m_FontTitle == NULL)
			std::cerr << "Failed to load Win Font! SDL Error: " << TTF_GetError() << std::endl;

	m_fCashOutAmmount = 0;

	m_uiTimer = 0;
}

Outro::~Outro()
{
	SDL_DestroyTexture(m_TextureBackground);

	delete m_LabelWinSign;
	delete m_TextFieldMoney;

	TTF_CloseFont(m_FontMoney);
	TTF_CloseFont(m_FontTitle);

	NullAll();
}

void Outro::EventHandler(SDL_Event& e)
{
	if(e.type == SDL_MOUSEBUTTONDOWN && !m_bTransitionIn && !m_bTransitionOut)
	{
		int x, y;
		SDL_GetMouseState(&x, &y);

		if(x >= m_iX && x <= (m_iX + g_OutroWidth))
			if(y >= m_iY && y <= (m_iY + g_OutroHeight))
			{
				m_bTransitionOut = true;
			}
	}
}

void Outro::Render(bool UpdateOnly)
{
	if(!m_Renderer || !m_TextureBackground || !m_FontMoney || !m_FontTitle)
		return;

	SDL_Rect tempRect;
	tempRect.h = g_OutroHeight;
	tempRect.w = g_OutroWidth;
	tempRect.x = m_iX;
	tempRect.y = m_iY;

	SDL_RenderCopy(m_Renderer, m_TextureBackground, NULL, &tempRect);

	SDL_SetRenderDrawColor(m_Renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderDrawRect(m_Renderer, &tempRect);

	if(m_bTransitionIn)
		TransitionIn();

	else if(m_bTransitionOut)
		TransitionOut();

	else if(SDL_GetTicks() - m_uiTimer >= g_OutroDelay)
		m_bTransitionOut = true;

	m_LabelWinSign->Render(false);
	m_TextFieldMoney->Render(false);
}

void Outro::PrepTransitionIn()
{
	m_bTransitionIn = true;

	m_iY = g_OutroHeightTransition;

	m_LabelWinSign->SetY(m_iY + (g_WinHeight - m_LabelWinSign->GetHeight()) / 2 + g_WinSignOffsetY);
	m_TextFieldMoney->SetY(m_iY + (g_WinHeight - m_TextFieldMoney->GetHeight()) / 2 + g_WinCreditOffsetY);
}

void Outro::SetCredits(unsigned int newCredits)
{
	m_fCashOutAmmount = newCredits * g_Denominator;

	std::string strMoney;
	std::stringstream ss;

	ss << "BGN " << m_fCashOutAmmount;
	strMoney = ss.str();

	m_TextFieldMoney->SetText(strMoney, m_FontMoney, SDL_Color{0xFF, 0xFF, 0xFF, 0xFF});

	std::string strWin;

	if(m_fCashOutAmmount < g_OutroWinSignLimits[0])
		strWin = g_OutroWinSign[0];
	else if(m_fCashOutAmmount < g_OutroWinSignLimits[1])
		strWin = g_OutroWinSign[1];
	else
		strWin = g_OutroWinSign[2];

	m_LabelWinSign->SetText(strWin, m_FontTitle, SDL_Color{0xF0, 0xF0, 0x00, 0xFF});
	m_LabelWinSign->SetX(m_iX + (g_OutroWidth - m_LabelWinSign->GetWidth()) / 2);
	m_LabelWinSign->SetY(m_iY + (g_OutroHeight - m_LabelWinSign->GetHeight()) / 2 + g_OutroWinOffsetY);
}

void Outro::NullAll()
{
	m_TextureBackground = NULL;
	m_LabelWinSign = NULL;
	m_TextFieldMoney = NULL;

	m_FontMoney = NULL;
	m_FontTitle = NULL;

	m_fCashOutAmmount = 0;

	m_uiTimer = 0;

	m_iX = 0;
	m_iY = 0;
}

void Outro::TransitionIn()
{
	if(m_iY == (g_ScreenHeight - g_OutroHeight) / 2)
	{
		m_bTransitionIn = false;

		m_uiTimer = SDL_GetTicks();
	}
	else
	{
		m_iY += g_TransitionStep;

		m_LabelWinSign->SetY(m_iY + (g_OutroHeight - m_LabelWinSign->GetHeight()) / 2 + g_OutroWinOffsetY);
		m_TextFieldMoney->SetY(m_iY + (g_OutroHeight - m_TextFieldMoney->GetHeight()) / 2 + g_WinCreditOffsetY);
	}
}
void Outro::TransitionOut()
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
		m_TextFieldMoney->SetY(m_iY + (g_OutroHeight - m_TextFieldMoney->GetHeight()) / 2 + g_WinCreditOffsetY);
	}
}

























