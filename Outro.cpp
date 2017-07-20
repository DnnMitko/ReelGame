#include "Outro.h"

Outro::Outro() : State()
{
	// NULL all members
	NullAll();
}

Outro::Outro(SDL_Renderer* newRenderer) : State(newRenderer)
{
	// Load background and check if successful
	m_TextureBackground = IMG_LoadTexture(m_Renderer, g_OutroBackground);
	if(m_TextureBackground == NULL)
		std::cerr << "Failed to load TextureBackground! SDL Error: " << IMG_GetError() << std::endl;

	// Set up position of the box at the center of the screen
	m_iX = (g_ScreenWidth - g_OutroWidth) / 2;
	m_iY = (g_ScreenHeight - g_OutroHeight) / 2;

	// Allocate memory for the win label
	m_LabelWinSign = new Label(m_Renderer);

	// Allocate and position the textfield displaying the money
	m_TextFieldMoney = new TextField(m_Renderer);
	m_TextFieldMoney->SetFieldSize(g_OutroMoneyHeight, g_OutroMoneyWidth);
	m_TextFieldMoney->SetX(m_iX + (g_OutroWidth - m_TextFieldMoney->GetWidth()) / 2);
	m_TextFieldMoney->SetY(m_iY + (g_OutroHeight - m_TextFieldMoney->GetHeight()) / 2 + g_OutroMoneyOffsetY);

	// Load font for the textfield and check if successful
	m_FontLabel = TTF_OpenFont(g_FontLabel, g_OutroFontSizeMoney);
	if(m_FontLabel == NULL)
			std::cerr << "Failed to load Label Font! SDL Error: " << TTF_GetError() << std::endl;

	// Load font for the title and check if successful
	m_FontTitle = TTF_OpenFont(g_FontTitle, g_OutroFontSizeWin);
	if(m_FontTitle == NULL)
			std::cerr << "Failed to load Win Font! SDL Error: " << TTF_GetError() << std::endl;

	// NULL the rest of the members (just in case)
	m_fCashOutAmmount = 0;
	m_uiTimer = 0;
}

Outro::~Outro()
{
	// Destroy and free memory from all members
	SDL_DestroyTexture(m_TextureBackground);

	delete m_LabelWinSign;
	delete m_TextFieldMoney;

	TTF_CloseFont(m_FontLabel);
	TTF_CloseFont(m_FontTitle);

	// NULL all members
	NullAll();
}

void Outro::EventHandler(SDL_Event& e)
{
	// If we're not in transition and a mouse click is done
	if(e.type == SDL_MOUSEBUTTONDOWN && !m_bTransitionIn && !m_bTransitionOut)
	{
		// Get mouse coordinates
		int x, y;
		SDL_GetMouseState(&x, &y);

		// If mouse clicked within the box
		if(x >= m_iX && x <= (m_iX + g_OutroWidth))
			if(y >= m_iY && y <= (m_iY + g_OutroHeight))
			{
				// Raise leaving flag
				m_bTransitionOut = true;
			}
	}
}

void Outro::Render(bool UpdateOnly)
{
	// If something failed to load, exit without doing anything
	if(!m_Renderer || !m_TextureBackground || !m_FontLabel || !m_FontTitle)
		return;

	// If we're in the middle of dropping in,
	// do corresponding repositions
	if(m_bTransitionIn)
		TransitionIn();

	// If we're in the middle of going away,
	// do corresponding repositions
	else if(m_bTransitionOut)
		TransitionOut();

	// If we're not moving,
	// check if enough time passed for box to leave
	else if(SDL_GetTicks() - m_uiTimer >= g_OutroDelay)
		m_bTransitionOut = true;

	// Make a rectangle positioned like the box's supposed to be
	SDL_Rect tempRect;
	tempRect.h = g_OutroHeight;
	tempRect.w = g_OutroWidth;
	tempRect.x = m_iX;
	tempRect.y = m_iY;

	// Draw the box there
	SDL_RenderCopy(m_Renderer, m_TextureBackground, NULL, &tempRect);

	// Draw an outline
	SDL_SetRenderDrawColor(m_Renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderDrawRect(m_Renderer, &tempRect);

	// Draw title message and win field
	m_LabelWinSign->Render(false);
	m_TextFieldMoney->Render(false);
}

void Outro::PrepTransitionIn()
{
	// Raise the TransitionIN flag
	m_bTransitionIn = true;

	// Set position to above the screen
	m_iY = g_OutroHeightTransition;

	// Reposition members to follow the change in height
	m_LabelWinSign->SetY(m_iY + (g_WinHeight - m_LabelWinSign->GetHeight()) / 2 + g_OutroWinOffsetY);
	m_TextFieldMoney->SetY(m_iY + (g_OutroHeight - m_TextFieldMoney->GetHeight()) / 2 + g_OutroMoneyOffsetY);
}

void Outro::SetCredits(unsigned int newCredits)
{
	// Calculate real money from the credits
	m_fCashOutAmmount = newCredits * g_Denominator;

	// Make a string and stringstream
	std::string strMoney;
	std::stringstream ss;

	// Convert the money into a string
	ss << "BGN " << m_fCashOutAmmount;
	strMoney = ss.str();

	// Set that string to show on the textfield
	m_TextFieldMoney->SetText(strMoney, m_FontLabel, SDL_Color{0xFF, 0xFF, 0xFF, 0xFF});

	// String for the win message
	std::string strWin;

	// If we reach certain milestones, load certain win messages
	if(m_fCashOutAmmount < g_OutroWinSignLimits[0])
		strWin = g_OutroWinSign[0];
	else if(m_fCashOutAmmount < g_OutroWinSignLimits[1])
		strWin = g_OutroWinSign[1];
	else
		strWin = g_OutroWinSign[2];

	// Set the win message to the win sign and center it on screen
	m_LabelWinSign->SetText(strWin, m_FontTitle, SDL_Color{0xF0, 0xF0, 0x00, 0xFF});
	m_LabelWinSign->SetX(m_iX + (g_OutroWidth - m_LabelWinSign->GetWidth()) / 2);
	m_LabelWinSign->SetY(m_iY + (g_OutroHeight - m_LabelWinSign->GetHeight()) / 2 + g_OutroWinOffsetY);
}

void Outro::NullAll()
{
	// NULL all members
	m_TextureBackground = NULL;
	m_LabelWinSign = NULL;
	m_TextFieldMoney = NULL;

	m_FontLabel = NULL;
	m_FontTitle = NULL;

	m_fCashOutAmmount = 0;

	m_uiTimer = 0;

	m_iX = 0;
	m_iY = 0;
}

void Outro::TransitionIn()
{
	// If we reached our position
	if(m_iY == (g_ScreenHeight - g_OutroHeight) / 2)
	{
		// Drop the TransitionIN flag
		m_bTransitionIn = false;

		// Save current time
		m_uiTimer = SDL_GetTicks();
	}
	else
	{
		// Move the box down
		m_iY += g_TransitionStep;

		// Reposition elements
		m_LabelWinSign->SetY(m_iY + (g_OutroHeight - m_LabelWinSign->GetHeight()) / 2 + g_OutroWinOffsetY);
		m_TextFieldMoney->SetY(m_iY + (g_OutroHeight - m_TextFieldMoney->GetHeight()) / 2 + g_WinCreditOffsetY);
	}
}
void Outro::TransitionOut()
{
	// If we're hidden off screen
	if(m_iY + g_OutroHeight <= 0)
	{
		// Drop the TransitionOUT flag
		m_bTransitionOut = false;

		// Raise the Switch flag
		m_bSwitch = true;
	}
	else
	{
		// Move the box up
		m_iY -= g_TransitionStep;

		// Reposition elements
		m_LabelWinSign->SetY(m_iY + (g_OutroHeight - m_LabelWinSign->GetHeight()) / 2 + g_OutroWinOffsetY);
		m_TextFieldMoney->SetY(m_iY + (g_OutroHeight - m_TextFieldMoney->GetHeight()) / 2 + g_OutroMoneyOffsetY);
	}
}

























