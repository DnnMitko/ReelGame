#include "GamePanel.h"

GamePanel::GamePanel()
{
	NullAll();
}

GamePanel::GamePanel(SDL_Renderer* newRenderer)
{
	m_Renderer = newRenderer;

	m_bTransitionIn = false;
	m_bTransitionOut = false;

	m_iY = g_GameMenuHeight;

	m_uiCurCredits = 0;
	m_uiBet = 0;
	m_uiLines = 1;
	m_uiTotalBet = 0;
	m_uiPaid = 0;

	m_FontBig = TTF_OpenFont(g_FontLabel, g_GameFontSizeBig);
	if(m_FontBig == NULL)
		std::cerr << "Failed to load Label Font! SDL Error: " << TTF_GetError() << std::endl;

	m_FontSmall = TTF_OpenFont(g_FontLabel, g_GameFontSizeSmall);
	if(m_FontSmall == NULL)
		std::cerr << "Failed to load Label Font! SDL Error: " << TTF_GetError() << std::endl;

	int curX = g_GameOffsetX;
	InitPayTable(curX);

	curX += g_GamePayTableWidth + g_GameMarginX;
	InitBet(curX);

	curX += g_GameFieldWidth + g_GameMarginX;
	InitLines(curX);

	curX += g_GameFieldWidth + g_GameMarginX;
	InitMaxBet(curX);

	curX += g_GameMaxBetWidth + g_GameMarginX;
	InitCurCredits(curX);

	// Total bet disables/enables play button so we need it created here.
	m_ButtonPlay = new Button(m_Renderer);
	curX += g_GameFieldWidth + g_GameMarginX;
	InitTotalBet(curX);

	curX += g_GameFieldWidth + g_GameMarginX;
	InitPaid(curX);

	curX += g_GameFieldWidth + g_GameMarginX;
	InitPlay(curX);

	curX += g_GamePlayWidth + g_GameMarginX;
	InitCashOut(curX);
}

GamePanel::~GamePanel()
{
	delete m_ButtonPayTable;

	delete m_LabelBet;
	delete m_TextFieldBet;
	delete m_ButtonBetMinus;
	delete m_ButtonBetPlus;

	delete m_LabelLines;
	delete m_TextFieldLines;
	delete m_ButtonLinesMinus;
	delete m_ButtonLinesPlus;

	delete m_ButtonMaxBet;

	delete m_LabelCurCredits;
	delete m_TextFieldCurCredits;

	delete m_LabelTotalBet;
	delete m_TextFieldTotalBet;

	delete m_LabelPaid;
	delete m_TextFieldPaid;

	delete m_ButtonPlay;

	delete m_ButtonCashOut;

	TTF_CloseFont(m_FontBig);
	TTF_CloseFont(m_FontSmall);

	NullAll();
}

void GamePanel::Render(bool UpdateOnly)
{
	if(!m_Renderer || !m_FontBig || !m_FontSmall)
		return;

	if(m_bTransitionIn)
		TransitionIn();
	else if(m_bTransitionOut)
		TransitionOut();

	m_ButtonPayTable->Render(UpdateOnly);

	m_LabelBet->Render(UpdateOnly);
	m_TextFieldBet->Render(UpdateOnly);
	m_ButtonBetMinus->Render(UpdateOnly);
	m_ButtonBetPlus->Render(UpdateOnly);

	m_LabelLines->Render(UpdateOnly);
	m_TextFieldLines->Render(UpdateOnly);
	m_ButtonLinesMinus->Render(UpdateOnly);
	m_ButtonLinesPlus->Render(UpdateOnly);

	m_ButtonMaxBet->Render(UpdateOnly);

	m_LabelCurCredits->Render(UpdateOnly);
	m_TextFieldCurCredits->Render(UpdateOnly);

	m_LabelTotalBet->Render(UpdateOnly);
	m_TextFieldTotalBet->Render(UpdateOnly);

	m_LabelPaid->Render(UpdateOnly);
	m_TextFieldPaid->Render(UpdateOnly);

	m_ButtonPlay->Render(UpdateOnly);

	m_ButtonCashOut->Render(UpdateOnly);
}

void GamePanel::EventHandler(SDL_Event& e, bool& bShowPayTable, bool& bPlay, bool& bCashOut)
{
	static bool bPayTableState = false;

	int x, y;
	if(e.type == SDL_MOUSEBUTTONDOWN)
	{
		SDL_GetMouseState(&x, &y);

		if(m_ButtonPayTable->IsIn(x, y))
			m_ButtonPayTable->Press();

		else if(m_ButtonBetMinus->IsIn(x, y))
			m_ButtonBetMinus->Press();
		else if(m_ButtonBetPlus->IsIn(x, y))
			m_ButtonBetPlus->Press();

		else if(m_ButtonLinesMinus->IsIn(x, y))
			m_ButtonLinesMinus->Press();
		else if(m_ButtonLinesPlus->IsIn(x, y))
			m_ButtonLinesPlus->Press();

		else if(m_ButtonMaxBet->IsIn(x, y))
			m_ButtonMaxBet->Press();

		else if(m_ButtonPlay->IsIn(x, y))
			m_ButtonPlay->Press();

		else if(m_ButtonCashOut->IsIn(x, y))
			m_ButtonCashOut->Press();
	}
	else if(e.type == SDL_MOUSEBUTTONUP)
	{
		SDL_GetMouseState(&x, &y);

		if(m_ButtonPayTable->IsIn(x, y) && m_ButtonPayTable->IsPressed())
		{
			bPayTableState = !bPayTableState;
		}
		else if(m_ButtonBetMinus->IsIn(x, y) && m_ButtonBetMinus->IsPressed())
		{
			if(m_uiBet > 0)
			{
				m_ButtonBetPlus->Enable();

				m_uiBet -= g_GameBetIncriment;
				UpdateBet();
				UpdateTotalBet();

				if(m_uiBet == 0)
				{
					m_ButtonBetMinus->Release();
					m_ButtonBetMinus->Disable();
				}

				if(m_uiLines < g_GameMaxLines && m_uiBet * (m_uiLines + 1) <= m_uiCurCredits)
					m_ButtonLinesPlus->Enable();
			}
		}
		else if(m_ButtonBetPlus->IsIn(x, y) && m_ButtonBetPlus->IsPressed())
		{
			if(m_uiBet < g_GameMaxBetAmmount && (m_uiBet + g_GameBetIncriment) * m_uiLines <= m_uiCurCredits)
			{
				m_ButtonBetMinus->Enable();

				m_uiBet += g_GameBetIncriment;
				UpdateBet();
				UpdateTotalBet();

				if(m_uiBet == g_GameMaxBetAmmount || (m_uiBet + g_GameBetIncriment) * m_uiLines > m_uiCurCredits)
				{
					m_ButtonBetPlus->Release();
					m_ButtonBetPlus->Disable();
				}

				if(m_uiBet * (m_uiLines + 1) > m_uiCurCredits)
					m_ButtonLinesPlus->Disable();
			}
		}
		else if(m_ButtonLinesMinus->IsIn(x, y) && m_ButtonLinesMinus->IsPressed())
		{
			if(m_uiLines > 1)
			{
				m_ButtonLinesPlus->Enable();

				m_uiLines--;
				UpdateLines();
				UpdateTotalBet();

				if(m_uiLines == 1)
				{
					m_ButtonLinesMinus->Release();
					m_ButtonLinesMinus->Disable();
				}
				
				if(m_uiBet < g_GameMaxBetAmmount && m_uiLines * (m_uiBet + g_GameBetIncriment) <= m_uiCurCredits)
					m_ButtonBetPlus->Enable();
			}
		}
		else if(m_ButtonLinesPlus->IsIn(x, y) && m_ButtonLinesPlus->IsPressed())
		{
			if(m_uiLines < g_GameMaxLines && m_uiBet * (m_uiLines + 1) <= m_uiCurCredits)
			{
				m_ButtonLinesMinus->Enable();

				m_uiLines++;
				UpdateLines();
				UpdateTotalBet();
				
				if(m_uiLines == g_GameMaxLines || m_uiBet * (m_uiLines + 1) > m_uiCurCredits)
				{
					m_ButtonLinesPlus->Release();
					m_ButtonLinesPlus->Disable();
				}

				if(m_uiLines * (m_uiBet + g_GameBetIncriment) > m_uiCurCredits)
					m_ButtonBetPlus->Disable();
			}
		}
		else if(m_ButtonMaxBet->IsIn(x, y) && m_ButtonMaxBet->IsPressed())
		{
			for(unsigned int testLines = g_GameMaxLines; testLines >= 1; testLines -= 1)
			{
				for(unsigned int testBet = g_GameMaxBetAmmount; testBet > 0; testBet -= g_GameBetIncriment)
				{
					if(testBet * testLines <= m_uiCurCredits)
					{
						m_uiLines = testLines;
						UpdateLines();

						m_uiBet = testBet;
						UpdateBet();

						UpdateTotalBet();
						break;
					}
				}

				if(m_uiTotalBet != 0)
					break;
			}

			if(m_uiBet == 0)
			{
				m_ButtonBetMinus->Disable();
				m_ButtonBetPlus->Enable();
			}
			else
			{
				m_ButtonBetMinus->Enable();
				if(m_uiBet == g_GameMaxBetAmmount || (m_uiBet + g_GameBetIncriment) * m_uiLines > m_uiCurCredits)
					m_ButtonBetPlus->Disable();
			}

			if(m_uiLines == 1)
			{
				m_ButtonLinesMinus->Disable();
				m_ButtonLinesPlus->Enable();
			}
			else
			{
				m_ButtonLinesMinus->Enable();
				if(m_uiLines == g_GameMaxLines || m_uiBet * (m_uiLines + 1) > m_uiCurCredits)
					m_ButtonLinesPlus->Disable();
			}

		}
		else if(m_ButtonPlay->IsIn(x, y) && m_ButtonPlay->IsPressed())
		{
			bPayTableState = false;

			if(!m_uiTotalBet == 0)
			{
				m_uiPaid = 0;
				UpdatePaid();

				m_uiCurCredits -= m_uiTotalBet;
				UpdateCurCredits();

				bPlay = true;
			}
		}
		else if(m_ButtonCashOut->IsIn(x, y) && m_ButtonCashOut->IsPressed())
		{
			bPayTableState = false;

			bCashOut = true;
		}

		ReleaseAll();
	}

	bShowPayTable = bPayTableState;
}

void GamePanel::PrepTransitionIn()
{
	m_bTransitionIn = true;

	m_iY = g_ScreenHeight + g_GamePanelHideOffsetY;
	Reposition();

	if(m_uiBet == 0)
	{
		m_ButtonBetMinus->Disable();
		m_ButtonBetPlus->Enable();
	}
	else
	{
		m_ButtonBetMinus->Enable();
		if(m_uiBet == g_GameMaxBetAmmount || (m_uiBet + g_GameBetIncriment) * m_uiLines > m_uiCurCredits)
			m_ButtonBetPlus->Disable();
	}

	if(m_uiLines == 1)
	{
		m_ButtonLinesMinus->Disable();
		m_ButtonLinesPlus->Enable();
	}
	else
	{
		m_ButtonLinesMinus->Enable();
		if(m_uiLines == g_GameMaxLines || m_uiBet * (m_uiLines + 1) > m_uiCurCredits)
			m_ButtonLinesPlus->Disable();
	}
}

bool GamePanel::InTransition()
{
	if(m_bTransitionIn || m_bTransitionOut)
		return true;

	return false;
}

void GamePanel::Hide()
{
	m_bTransitionOut = true;
}

void GamePanel::SetCredits(unsigned int newCredits)
{
	m_uiCurCredits = newCredits;
	UpdateCurCredits();
}

unsigned int GamePanel::GetCredits() const
{
	return m_uiCurCredits;
}

unsigned int GamePanel::GetBet() const
{
	return m_uiBet;
}

void GamePanel::SetBet(unsigned int newBet)
{
	m_uiBet = newBet;
	UpdateBet();

	UpdateTotalBet();
}

unsigned int GamePanel::GetLines() const
{
	return m_uiLines;
}

void GamePanel::SetLines(unsigned int newLines)
{
	m_uiLines = newLines;
	UpdateLines();

	UpdateTotalBet();
}

unsigned int GamePanel::GetPaid() const
{
	return m_uiPaid;
}

unsigned int GamePanel::GetTotalBet() const
{
	return m_uiTotalBet;
}

void GamePanel::CalcWinning(unsigned int uiPaid)
{
	m_uiPaid = uiPaid;
	UpdatePaid();

	m_uiCurCredits += m_uiPaid;
	UpdateCurCredits();

	RecalcBet();
}

void GamePanel::Clear()
{
	m_uiBet = 0;
	UpdateBet();
	m_ButtonBetMinus->Disable();
	m_ButtonBetPlus->Enable();

	m_uiLines = 1;
	UpdateLines();
	m_ButtonLinesMinus->Disable();
	m_ButtonLinesPlus->Enable();

	UpdateTotalBet();

	m_uiPaid = 0;
	UpdatePaid();
}

void GamePanel::NullAll()
{
	m_bTransitionIn = false;
	m_bTransitionOut = false;

	m_uiCurCredits = 0;
	m_uiBet = 0;
	m_uiLines = 1;
	m_uiTotalBet = 0;
	m_uiPaid = 0;

	m_ButtonPayTable = NULL;

	m_LabelBet = NULL;
	m_TextFieldBet = NULL;
	m_ButtonBetMinus = NULL;
	m_ButtonBetPlus = NULL;

	m_LabelLines = NULL;
	m_TextFieldLines = NULL;
	m_ButtonLinesMinus = NULL;
	m_ButtonLinesPlus = NULL;

	m_ButtonMaxBet = NULL;

	m_LabelCurCredits = NULL;
	m_TextFieldCurCredits = NULL;

	m_LabelTotalBet = NULL;
	m_TextFieldTotalBet = NULL;

	m_LabelPaid = NULL;
	m_TextFieldPaid = NULL;

	m_ButtonPlay = NULL;

	m_ButtonCashOut = NULL;

	m_FontBig = NULL;
	m_FontSmall = NULL;
}

void GamePanel::TransitionIn()
{
	if(m_iY == g_GameMenuHeight)
		m_bTransitionIn = false;
	else
	{
		m_iY -= g_TransitionStep;
		Reposition();
	}
}

void GamePanel::TransitionOut()
{
	if(m_iY >= g_ScreenHeight + g_GamePanelHideOffsetY)
		m_bTransitionOut = false;
	else
	{
		m_iY += g_TransitionStep;
		Reposition();
	}
}

void GamePanel::Reposition()
{
	m_ButtonPayTable->SetY(m_iY);

	m_LabelBet->SetY(m_iY - m_LabelBet->GetHeight());
	m_TextFieldBet->SetY(m_iY);
	m_ButtonBetMinus->SetY(m_iY + g_GameFieldHeight);
	m_ButtonBetPlus->SetY(m_iY + g_GameFieldHeight);

	m_LabelLines->SetY(m_iY - m_LabelLines->GetHeight());
	m_TextFieldLines->SetY(m_iY);
	m_ButtonLinesMinus->SetY(m_iY + g_GameFieldHeight);
	m_ButtonLinesPlus->SetY(m_iY + g_GameFieldHeight);

	m_ButtonMaxBet->SetY(m_iY);

	m_LabelCurCredits->SetY(m_iY + g_GameFieldHeight - m_LabelCurCredits->GetHeight());
	m_TextFieldCurCredits->SetY(m_iY + g_GameFieldHeight);

	m_LabelTotalBet->SetY(m_iY + g_GameFieldHeight - m_LabelTotalBet->GetHeight());
	m_TextFieldTotalBet->SetY(m_iY + g_GameFieldHeight);

	m_LabelPaid->SetY(m_iY + g_GameFieldHeight - m_LabelPaid->GetHeight());
	m_TextFieldPaid->SetY(m_iY + g_GameFieldHeight);

	m_ButtonPlay->SetY(m_iY);

	m_ButtonCashOut->SetY(m_iY);
}

void GamePanel::RecalcBet()
{
	if(m_uiTotalBet <= m_uiCurCredits)
		return;
	else
	{
		while (m_uiBet * m_uiLines > m_uiCurCredits)
		{
			if(m_uiBet > g_GameBetIncriment)
				m_uiBet -= g_GameBetIncriment;
			else if(m_uiLines > 1)
				m_uiLines -= 1;
			else
			{
				m_uiBet = 0;
				break;
			}
		}

		if(m_uiBet == 0)
		{
			m_ButtonBetMinus->Disable();
			m_ButtonBetPlus->Enable();
		}
		else
		{
			m_ButtonBetMinus->Enable();
			if(m_uiBet == g_GameMaxBetAmmount)
				m_ButtonBetPlus->Disable();
		}

		if(m_uiLines == 1)
		{
			m_ButtonLinesMinus->Disable();
			m_ButtonLinesPlus->Enable();
		}
		else
		{
			m_ButtonLinesMinus->Enable();
			if(m_uiLines == g_GameMaxLines)
				m_ButtonLinesPlus->Disable();
		}

		UpdateBet();
		UpdateLines();
		UpdateTotalBet();
	}
}

void GamePanel::InitPayTable(int curX)
{
	m_ButtonPayTable = new Button(m_Renderer);
	m_ButtonPayTable->SetX(curX);
	m_ButtonPayTable->SetY(m_iY);
	m_ButtonPayTable->SetText("Pay Table", m_FontBig, g_ColorBlack);
	m_ButtonPayTable->SetFieldSize(g_GamePayTableHeight, g_GamePayTableWidth);
}

void GamePanel::InitBet(int curX)
{
	m_LabelBet = new Label(m_Renderer);
	m_LabelBet->SetText(g_GameLabelBet, m_FontSmall, g_ColorBlack);
	m_LabelBet->SetX(curX + (g_GameFieldWidth - m_LabelBet->GetWidth()) / 2);
	m_LabelBet->SetY(m_iY - m_LabelBet->GetHeight());

	m_TextFieldBet = new TextField(m_Renderer);
	m_TextFieldBet->SetX(curX);
	m_TextFieldBet->SetY(m_iY);
	m_TextFieldBet->SetFieldSize(g_GameFieldHeight, g_GameFieldWidth);
	UpdateBet();

	m_ButtonBetMinus = new Button(m_Renderer);
	m_ButtonBetMinus->SetX(curX);
	m_ButtonBetMinus->SetY(m_iY + g_GameFieldHeight);
	m_ButtonBetMinus->SetFieldSize(g_GameFieldHeight, g_GameFieldWidth / 2);
	m_ButtonBetMinus->SetText("-", m_FontBig, g_ColorBlack);

	m_ButtonBetPlus = new Button(m_Renderer);
	m_ButtonBetPlus->SetX(curX + g_GameFieldWidth / 2);
	m_ButtonBetPlus->SetY(m_iY + g_GameFieldHeight);
	m_ButtonBetPlus->SetFieldSize(g_GameFieldHeight, g_GameFieldWidth / 2);
	m_ButtonBetPlus->SetText("+", m_FontBig, g_ColorBlack);
}

void GamePanel::InitLines(int curX)
{
	m_LabelLines = new Label(m_Renderer);
	m_LabelLines->SetText(g_GameLabelLines, m_FontSmall, g_ColorBlack);
	m_LabelLines->SetX(curX + (g_GameFieldWidth - m_LabelLines->GetWidth()) / 2);
	m_LabelLines->SetY(m_iY - m_LabelLines->GetHeight());

	m_TextFieldLines = new TextField(m_Renderer);
	m_TextFieldLines->SetX(curX);
	m_TextFieldLines->SetY(m_iY);
	m_TextFieldLines->SetFieldSize(g_GameFieldHeight, g_GameFieldWidth);
	UpdateLines();

	m_ButtonLinesMinus = new Button(m_Renderer);
	m_ButtonLinesMinus->SetX(curX);
	m_ButtonLinesMinus->SetY(m_iY + g_GameFieldHeight);
	m_ButtonLinesMinus->SetFieldSize(g_GameFieldHeight, g_GameFieldWidth / 2);
	m_ButtonLinesMinus->SetText("-", m_FontBig, g_ColorBlack);

	m_ButtonLinesPlus = new Button(m_Renderer);
	m_ButtonLinesPlus->SetX(curX + g_GameFieldWidth / 2);
	m_ButtonLinesPlus->SetY(m_iY + g_GameFieldHeight);
	m_ButtonLinesPlus->SetFieldSize(g_GameFieldHeight, g_GameFieldWidth / 2);
	m_ButtonLinesPlus->SetText("+", m_FontBig, g_ColorBlack);
}

void GamePanel::InitMaxBet(int curX)
{
	m_ButtonMaxBet = new Button(m_Renderer);
	m_ButtonMaxBet->SetX(curX);
	m_ButtonMaxBet->SetY(m_iY);
	m_ButtonMaxBet->SetFieldSize(g_GameMaxBetHeight, g_GameMaxBetWidth);
	m_ButtonMaxBet->SetText(g_GameButtonMaxBet, m_FontBig, g_ColorBlack);
}

void GamePanel::InitCurCredits(int curX)
{
	m_LabelCurCredits = new Label(m_Renderer);
	m_LabelCurCredits->SetText(g_GameLabelCredits, m_FontSmall, g_ColorBlack);
	m_LabelCurCredits->SetX(curX + (g_GameFieldWidth - m_LabelCurCredits->GetWidth()) / 2);
	m_LabelCurCredits->SetY(m_iY + g_GameFieldHeight - m_LabelCurCredits->GetHeight());

	m_TextFieldCurCredits = new TextField(m_Renderer);
	m_TextFieldCurCredits->SetX(curX);
	m_TextFieldCurCredits->SetY(m_iY + g_GameFieldHeight);
	m_TextFieldCurCredits->SetFieldSize(g_GameFieldHeight, g_GameFieldWidth);
	UpdateCurCredits();
}

void GamePanel::InitTotalBet(int curX)
{
	m_LabelTotalBet = new Label(m_Renderer);
	m_LabelTotalBet->SetText(g_GameLabelTotalBet, m_FontSmall, g_ColorBlack);
	m_LabelTotalBet->SetX(curX + (g_GameFieldWidth - m_LabelTotalBet->GetWidth()) / 2);
	m_LabelTotalBet->SetY(m_iY + g_GameFieldHeight - m_LabelTotalBet->GetHeight());

	m_TextFieldTotalBet = new TextField(m_Renderer);
	m_TextFieldTotalBet->SetX(curX);
	m_TextFieldTotalBet->SetY(m_iY + g_GameFieldHeight);
	m_TextFieldTotalBet->SetFieldSize(g_GameFieldHeight, g_GameFieldWidth);
	UpdateTotalBet();
}

void GamePanel::InitPaid(int curX)
{
	m_LabelPaid = new Label(m_Renderer);
	m_LabelPaid->SetText(g_GameLabelPaid, m_FontSmall, g_ColorBlack);
	m_LabelPaid->SetX(curX + (g_GameFieldWidth - m_LabelPaid->GetWidth()) / 2);
	m_LabelPaid->SetY(m_iY + g_GameFieldHeight - m_LabelPaid->GetHeight());

	m_TextFieldPaid = new TextField(m_Renderer);
	m_TextFieldPaid->SetX(curX);
	m_TextFieldPaid->SetY(m_iY + g_GameFieldHeight);
	m_TextFieldPaid->SetFieldSize(g_GameFieldHeight, g_GameFieldWidth);
	UpdatePaid();
}

void GamePanel::InitPlay(int curX)
{
	m_ButtonPlay->SetX(curX);
	m_ButtonPlay->SetY(m_iY);
	m_ButtonPlay->SetFieldSize(g_GamePlayHeight, g_GamePlayWidth);
	m_ButtonPlay->SetText(g_GameButtonPlay, m_FontBig, g_ColorBlack);
}

void GamePanel::InitCashOut(int curX)
{
	m_ButtonCashOut = new Button(m_Renderer);
	m_ButtonCashOut->SetX(curX);
	m_ButtonCashOut->SetY(m_iY);
	m_ButtonCashOut->SetFieldSize(g_GameCashOutHeight, g_GameCashOutWidth);
	m_ButtonCashOut->SetText(g_GameButtonCashOut, m_FontBig, g_ColorBlack);
}

void GamePanel::UpdateBet()
{
	std::stringstream ss;
	std::string tempStr;

	ss << m_uiBet;
	tempStr = ss.str();

	m_TextFieldBet->SetText(tempStr, m_FontSmall, g_ColorWhite);
}

void GamePanel::UpdateLines()
{
	std::stringstream ss;
	std::string tempStr;

	ss << m_uiLines;
	tempStr = ss.str();

	m_TextFieldLines->SetText(tempStr, m_FontSmall, g_ColorWhite);
}

void GamePanel::UpdateCurCredits()
{
	std::stringstream ss;
	std::string tempStr;

	ss << m_uiCurCredits;
	tempStr = ss.str();

	m_TextFieldCurCredits->SetText(tempStr, m_FontSmall, g_ColorWhite);
}

void GamePanel::UpdateTotalBet()
{
	m_uiTotalBet = m_uiBet * m_uiLines;

	std::stringstream ss;
	std::string tempStr;

	ss << m_uiTotalBet;
	tempStr = ss.str();

	m_TextFieldTotalBet->SetText(tempStr, m_FontSmall, g_ColorWhite);

	if(m_uiTotalBet == 0)
		m_ButtonPlay->Disable();
	else
		m_ButtonPlay->Enable();
}

void GamePanel::UpdatePaid()
{
	std::stringstream ss;
	std::string tempStr;

	ss << m_uiPaid;
	tempStr = ss.str();

	m_TextFieldPaid->SetText(tempStr, m_FontSmall, g_ColorWhite);
}

void GamePanel::ReleaseAll()
{
	m_ButtonPayTable->Release();

	m_ButtonBetMinus->Release();
	m_ButtonBetPlus->Release();

	m_ButtonLinesMinus->Release();
	m_ButtonLinesPlus->Release();

	m_ButtonMaxBet->Release();

	m_ButtonPlay->Release();

	m_ButtonCashOut->Release();
}
