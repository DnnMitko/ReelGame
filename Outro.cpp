#include "Outro.h"

Outro::Outro() : State()
{
	m_TextureBackground = NULL;
	m_LabelWinSign = NULL;
	m_TextFieldMoney = NULL;
	m_FontMoney = NULL;
	m_FontWin = NULL;

	m_fCashOutAmmount = 0;

	m_iX = 0;
	m_iY = 0;
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

	m_FontMoney = TTF_OpenFont(g_LabelFont, g_OutroFontSizeMoney);
	if(m_FontMoney == NULL)
			std::cerr << "Failed to load Label Font! SDL Error: " << TTF_GetError() << std::endl;

	m_FontWin = TTF_OpenFont(g_WinFont, g_OutroFontSizeWin);
	if(m_FontWin == NULL)
			std::cerr << "Failed to load Win Font! SDL Error: " << TTF_GetError() << std::endl;

	m_fCashOutAmmount = 0;
}

Outro::~Outro()
{
	SDL_DestroyTexture(m_TextureBackground);
	delete m_LabelWinSign;
	delete m_TextFieldMoney;
	TTF_CloseFont(m_FontMoney);
	TTF_CloseFont(m_FontWin);

	m_TextureBackground = NULL;
	m_LabelWinSign = NULL;
	m_TextFieldMoney = NULL;
	m_FontMoney = NULL;
	m_FontWin = NULL;
}

void Outro::EventHandler(SDL_Event& e)
{
}

void Outro::Render(bool UpdateOnly)
{
	if(!UpdateOnly)
	{
		if(m_Renderer == NULL || m_TextureBackground == NULL || m_FontMoney == NULL || m_FontWin == NULL)
			return;

		SDL_Rect tempRect;
		tempRect.h = g_OutroHeight;
		tempRect.w = g_OutroWidth;
		tempRect.x = m_iX;
		tempRect.y = m_iY;

		SDL_RenderCopy(m_Renderer, m_TextureBackground, NULL, &tempRect);

		SDL_SetRenderDrawColor(m_Renderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderDrawRect(m_Renderer, &tempRect);
	}

	m_LabelWinSign->Render(UpdateOnly);
	m_TextFieldMoney->Render(UpdateOnly);
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

	m_LabelWinSign->SetText(strWin, m_FontWin, SDL_Color{0xF0, 0xF0, 0x00, 0xFF});
	m_LabelWinSign->SetX(m_iX + (g_OutroWidth - m_LabelWinSign->GetWidth()) / 2);
	m_LabelWinSign->SetY(m_iY + (g_OutroHeight - m_LabelWinSign->GetHeight()) / 2 + g_OutroWinOffsetY);
}




























