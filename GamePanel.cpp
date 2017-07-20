#include "GamePanel.h"

GamePanel::GamePanel()
{
	NullAll();
}

GamePanel::GamePanel(SDL_Renderer* newRenderer)
{
	m_Renderer = newRenderer;

	m_uiCurCredits = 0;
	m_uiBet = 0;
	m_uiLines = 1;
	m_uiTotalBet = 0;
	m_uiPaid = 0;

	m_FontBig = TTF_OpenFont(g_GameFont, g_GameFontSizeBig);
	if(m_FontBig == NULL)
		std::cerr << "Failed to load Label Font! SDL Error: " << TTF_GetError() << std::endl;

	m_FontSmall = TTF_OpenFont(g_GameFont, g_GameFontSizeSmall);
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

void GamePanel::EventHandler(SDL_Event& e, bool& bSwitch)
{
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
	else if (e.type == SDL_MOUSEBUTTONUP)
	{
		SDL_GetMouseState(&x, &y);

		if(m_ButtonPayTable->IsIn(x, y) && m_ButtonPayTable->IsPressed())
		{
			//TODO
			bSwitch = true;
			m_bBonus = true;
		}
		else if(m_ButtonBetMinus->IsIn(x, y) && m_ButtonBetMinus->IsPressed())
		{
			if(m_uiBet > 0)
			{
				m_uiBet -= g_GameBetIncriment;
				UpdateBet();

				UpdateTotalBet();
			}
		}
		else if(m_ButtonBetPlus->IsIn(x, y) && m_ButtonBetPlus->IsPressed())
		{
			if(m_uiBet < g_GameMaxBetAmmount && (m_uiBet + g_GameBetIncriment) * m_uiLines <= m_uiCurCredits)
			{
				m_uiBet += g_GameBetIncriment;
				UpdateBet();

				UpdateTotalBet();
			}
		}
		else if(m_ButtonLinesMinus->IsIn(x, y) && m_ButtonLinesMinus->IsPressed())
		{
			if(m_uiLines > 1)
			{
				m_uiLines--;
				UpdateLines();

				UpdateTotalBet();
			}
		}
		else if(m_ButtonLinesPlus->IsIn(x, y) && m_ButtonLinesPlus->IsPressed())
		{
			if(m_uiLines < g_GameMaxLines && m_uiBet * (m_uiLines + 1) <= m_uiCurCredits)
			{
				m_uiLines++;
				UpdateLines();

				UpdateTotalBet();
			}
		}
		else if(m_ButtonMaxBet->IsIn(x, y) && m_ButtonMaxBet->IsPressed())
		{
			for(unsigned int testLines = g_GameMaxLines; testLines >= 0; testLines -= 1)
			{
				for(unsigned int testBet = g_GameMaxBetAmmount; testBet >= 0; testBet -= g_GameBetIncriment)
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
		}
		else if(m_ButtonPlay->IsIn(x, y) && m_ButtonPlay->IsPressed())
		{
			//TODO
			m_bWin = true;
			bSwitch = true;
		}
		else if(m_ButtonCashOut->IsIn(x, y) && m_ButtonCashOut->IsPressed())
		{
			//TODO
			bSwitch = true;
		}

		ReleaseAll();
	}
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

unsigned int GamePanel::GetTotalBet() const
{
	return m_uiTotalBet;
}

unsigned int GamePanel::GetPaid() const
{
	return m_uiPaid;
}

void GamePanel::CalcWinning(unsigned int uiPaid)
{
	m_uiPaid = uiPaid;
	UpdatePaid();

	m_uiCurCredits -= m_uiTotalBet;

	if(m_uiPaid == 0)
	{
		UpdateCurCredits();
		Clear();
	}
	else
	{
		m_uiCurCredits += m_uiPaid;
		UpdateCurCredits();
	}
}

bool GamePanel::GetWin() const
{
	return m_bWin;
}

void GamePanel::ResetWin()
{
	m_bWin = false;
}

bool GamePanel::GetBonus() const
{
	return m_bBonus;
}

void GamePanel::ResetBonus()
{
	m_bBonus = false;
}

void GamePanel::Clear()
{
	m_uiBet = 0;
	UpdateBet();

	m_uiLines = 1;
	UpdateLines();

	m_uiTotalBet = 0;
	UpdateTotalBet();

	m_uiPaid = 0;
	UpdatePaid();
}

void GamePanel::NullAll()
{
	m_bBonus = false;
	m_bWin = false;

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

void GamePanel::InitPayTable(int curX)
{
	m_ButtonPayTable = new Button(m_Renderer);
	m_ButtonPayTable->SetX(curX);
	m_ButtonPayTable->SetY(g_GameMenuHeight);
	m_ButtonPayTable->SetText("Pay Table", m_FontBig, SDL_Color{0x00, 0x00, 0x00, 0xFF});
	m_ButtonPayTable->SetFieldSize(g_GamePayTableHeight, g_GamePayTableWidth);
}

void GamePanel::InitBet(int curX)
{
	m_LabelBet = new Label(m_Renderer);
	m_LabelBet->SetText(g_GameLabelBet, m_FontSmall, SDL_Color{0x00, 0x00, 0x00, 0xFF});
	m_LabelBet->SetX(curX + (g_GameFieldWidth - m_LabelBet->GetWidth()) / 2);
	m_LabelBet->SetY(g_GameMenuHeight - m_LabelBet->GetHeight());

	m_TextFieldBet = new TextField(m_Renderer);
	m_TextFieldBet->SetX(curX);
	m_TextFieldBet->SetY(g_GameMenuHeight);
	m_TextFieldBet->SetFieldSize(g_GameFieldHeight, g_GameFieldWidth);
	UpdateBet();

	m_ButtonBetMinus = new Button(m_Renderer);
	m_ButtonBetMinus->SetX(curX);
	m_ButtonBetMinus->SetY(g_GameMenuHeight + g_GameFieldHeight);
	m_ButtonBetMinus->SetFieldSize(g_GameFieldHeight, g_GameFieldWidth / 2);
	m_ButtonBetMinus->SetText("-", m_FontBig, SDL_Color{0x00, 0x00, 0x00, 0xFF});

	m_ButtonBetPlus = new Button(m_Renderer);
	m_ButtonBetPlus->SetX(curX + g_GameFieldWidth / 2);
	m_ButtonBetPlus->SetY(g_GameMenuHeight + g_GameFieldHeight);
	m_ButtonBetPlus->SetFieldSize(g_GameFieldHeight, g_GameFieldWidth / 2);
	m_ButtonBetPlus->SetText("+", m_FontBig, SDL_Color{0x00, 0x00, 0x00, 0xFF});
}

void GamePanel::InitLines(int curX)
{
	m_LabelLines = new Label(m_Renderer);
	m_LabelLines->SetText(g_GameLabelLines, m_FontSmall, SDL_Color{0x00, 0x00, 0x00, 0xFF});
	m_LabelLines->SetX(curX + (g_GameFieldWidth - m_LabelLines->GetWidth()) / 2);
	m_LabelLines->SetY(g_GameMenuHeight - m_LabelLines->GetHeight());

	m_TextFieldLines = new TextField(m_Renderer);
	m_TextFieldLines->SetX(curX);
	m_TextFieldLines->SetY(g_GameMenuHeight);
	m_TextFieldLines->SetFieldSize(g_GameFieldHeight, g_GameFieldWidth);
	UpdateLines();

	m_ButtonLinesMinus = new Button(m_Renderer);
	m_ButtonLinesMinus->SetX(curX);
	m_ButtonLinesMinus->SetY(g_GameMenuHeight + g_GameFieldHeight);
	m_ButtonLinesMinus->SetFieldSize(g_GameFieldHeight, g_GameFieldWidth / 2);
	m_ButtonLinesMinus->SetText("-", m_FontBig, SDL_Color{0x00, 0x00, 0x00, 0xFF});

	m_ButtonLinesPlus = new Button(m_Renderer);
	m_ButtonLinesPlus->SetX(curX + g_GameFieldWidth / 2);
	m_ButtonLinesPlus->SetY(g_GameMenuHeight + g_GameFieldHeight);
	m_ButtonLinesPlus->SetFieldSize(g_GameFieldHeight, g_GameFieldWidth / 2);
	m_ButtonLinesPlus->SetText("+", m_FontBig, SDL_Color{0x00, 0x00, 0x00, 0xFF});
}

void GamePanel::InitMaxBet(int curX)
{
	m_ButtonMaxBet = new Button(m_Renderer);
	m_ButtonMaxBet->SetX(curX);
	m_ButtonMaxBet->SetY(g_GameMenuHeight);
	m_ButtonMaxBet->SetFieldSize(g_GameMaxBetHeight, g_GameMaxBetWidth);
	m_ButtonMaxBet->SetText(g_GameButtonMaxBet, m_FontBig, SDL_Color{0x00, 0x00, 0x00, 0xFF});
}

void GamePanel::InitCurCredits(int curX)
{
	m_LabelCurCredits = new Label(m_Renderer);
	m_LabelCurCredits->SetText(g_GameLabelCredits, m_FontSmall, SDL_Color{0x00, 0x00, 0x00, 0xFF});
	m_LabelCurCredits->SetX(curX + (g_GameFieldWidth - m_LabelCurCredits->GetWidth()) / 2);
	m_LabelCurCredits->SetY(g_GameMenuHeight + g_GameFieldHeight - m_LabelCurCredits->GetHeight());

	m_TextFieldCurCredits = new TextField(m_Renderer);
	m_TextFieldCurCredits->SetX(curX);
	m_TextFieldCurCredits->SetY(g_GameMenuHeight + g_GameFieldHeight);
	m_TextFieldCurCredits->SetFieldSize(g_GameFieldHeight, g_GameFieldWidth);
	UpdateCurCredits();
}

void GamePanel::InitTotalBet(int curX)
{
	m_LabelTotalBet = new Label(m_Renderer);
	m_LabelTotalBet->SetText(g_GameLabelTotalBet, m_FontSmall, SDL_Color{0x00, 0x00, 0x00, 0xFF});
	m_LabelTotalBet->SetX(curX + (g_GameFieldWidth - m_LabelTotalBet->GetWidth()) / 2);
	m_LabelTotalBet->SetY(g_GameMenuHeight + g_GameFieldHeight - m_LabelTotalBet->GetHeight());

	m_TextFieldTotalBet = new TextField(m_Renderer);
	m_TextFieldTotalBet->SetX(curX);
	m_TextFieldTotalBet->SetY(g_GameMenuHeight + g_GameFieldHeight);
	m_TextFieldTotalBet->SetFieldSize(g_GameFieldHeight, g_GameFieldWidth);
	UpdateTotalBet();
}

void GamePanel::InitPaid(int curX)
{
	m_LabelPaid = new Label(m_Renderer);
	m_LabelPaid->SetText(g_GameLabelPaid, m_FontSmall, SDL_Color{0x00, 0x00, 0x00, 0xFF});
	m_LabelPaid->SetX(curX + (g_GameFieldWidth - m_LabelPaid->GetWidth()) / 2);
	m_LabelPaid->SetY(g_GameMenuHeight + g_GameFieldHeight - m_LabelPaid->GetHeight());

	m_TextFieldPaid = new TextField(m_Renderer);
	m_TextFieldPaid->SetX(curX);
	m_TextFieldPaid->SetY(g_GameMenuHeight + g_GameFieldHeight);
	m_TextFieldPaid->SetFieldSize(g_GameFieldHeight, g_GameFieldWidth);
	UpdatePaid();
}

void GamePanel::InitPlay(int curX)
{
	m_ButtonPlay = new Button(m_Renderer);
	m_ButtonPlay->SetX(curX);
	m_ButtonPlay->SetY(g_GameMenuHeight);
	m_ButtonPlay->SetFieldSize(g_GamePlayHeight, g_GamePlayWidth);
	m_ButtonPlay->SetText(g_GameButtonPlay, m_FontBig, SDL_Color{0x00, 0x00, 0x00, 0xFF});
}

void GamePanel::InitCashOut(int curX)
{
	m_ButtonCashOut = new Button(m_Renderer);
	m_ButtonCashOut->SetX(curX);
	m_ButtonCashOut->SetY(g_GameMenuHeight);
	m_ButtonCashOut->SetFieldSize(g_GameCashOutHeight, g_GameCashOutWidth);
	m_ButtonCashOut->SetText(g_GameButtonCashOut, m_FontBig, SDL_Color{0x00, 0x00, 0x00, 0xFF});
}

void GamePanel::UpdateBet()
{
	std::stringstream ss;
	std::string tempStr;

	ss << m_uiBet;
	tempStr = ss.str();

	m_TextFieldBet->SetText(tempStr, m_FontSmall, SDL_Color{0xFF, 0xFF, 0xFF, 0xFF});
}

void GamePanel::UpdateLines()
{
	std::stringstream ss;
	std::string tempStr;

	ss << m_uiLines;
	tempStr = ss.str();

	m_TextFieldLines->SetText(tempStr, m_FontSmall, SDL_Color{0xFF, 0xFF, 0xFF, 0xFF});
}

void GamePanel::UpdateCurCredits()
{
	std::stringstream ss;
	std::string tempStr;

	ss << m_uiCurCredits;
	tempStr = ss.str();

	m_TextFieldCurCredits->SetText(tempStr, m_FontSmall, SDL_Color{0xFF, 0xFF, 0xFF, 0xFF});
}

void GamePanel::UpdateTotalBet()
{
	m_uiTotalBet = m_uiBet * m_uiLines;

	std::stringstream ss;
	std::string tempStr;

	ss << m_uiTotalBet;
	tempStr = ss.str();

	m_TextFieldTotalBet->SetText(tempStr, m_FontSmall, SDL_Color{0xFF, 0xFF, 0xFF, 0xFF});
}

void GamePanel::UpdatePaid()
{
	std::stringstream ss;
	std::string tempStr;

	ss << m_uiPaid;
	tempStr = ss.str();

	m_TextFieldPaid->SetText(tempStr, m_FontSmall, SDL_Color{0xFF, 0xFF, 0xFF, 0xFF});
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
