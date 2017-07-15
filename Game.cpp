#include "Game.h"

Game::Game() : State()
{
	m_uiCurrentCredits = 0;

	m_TextureBackground = NULL;

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

	m_FontBig = NULL;
	m_FontSmall = NULL;
}

Game::Game(SDL_Renderer* newRenderer) : State(newRenderer)
{
	m_uiCurrentCredits = 0;

	m_TextureBackground = IMG_LoadTexture(m_Renderer, "images/GameBackground.png");

	m_FontBig = TTF_OpenFont("fonts/Roboto-Medium.ttf", 30);
	m_FontSmall = TTF_OpenFont("fonts/Roboto-Medium.ttf", 20);

	SDL_Color ColorBlack = {0x00, 0x00, 0x00, 0xFF};
	SDL_Color ColorWhite = {0xFF, 0xFF, 0xFF, 0xFF};

	int curX = g_GameOffsetX;

	m_ButtonPayTable = new Button(m_Renderer);
	m_ButtonPayTable->SetX(curX);
	m_ButtonPayTable->SetY(g_GameMenuHeight);
	m_ButtonPayTable->SetText("Pay Table", m_FontBig, ColorBlack);
	m_ButtonPayTable->SetFieldSize(g_GamePayTableHeight, g_GamePayTableWidth);

	curX += g_GamePayTableWidth + g_GameMarginX;

	m_LabelBet = new Label(m_Renderer);
	m_LabelBet->SetText("Bet", m_FontSmall, ColorBlack);
	m_LabelBet->SetX(curX + (g_GameFieldWidth - m_LabelBet->GetWidth()) / 2);
	m_LabelBet->SetY(g_GameMenuHeight - m_LabelBet->GetHeight());

	m_TextFieldBet = new TextField(m_Renderer);
	m_TextFieldBet->SetX(curX);
	m_TextFieldBet->SetY(g_GameMenuHeight);
	m_TextFieldBet->SetFieldSize(g_GameFieldHeight, g_GameFieldWidth);
	m_TextFieldBet->SetText("0", m_FontSmall, ColorWhite);

	m_ButtonBetMinus = new Button(m_Renderer);
	m_ButtonBetMinus->SetX(curX);
	m_ButtonBetMinus->SetY(g_GameMenuHeight + g_GameFieldHeight);
	m_ButtonBetMinus->SetFieldSize(g_GameFieldHeight, g_GameFieldWidth / 2);
	m_ButtonBetMinus->SetText("-", m_FontBig, ColorBlack);

	m_ButtonBetPlus = new Button(m_Renderer);
	m_ButtonBetPlus->SetX(curX + g_GameFieldWidth / 2);
	m_ButtonBetPlus->SetY(g_GameMenuHeight + g_GameFieldHeight);
	m_ButtonBetPlus->SetFieldSize(g_GameFieldHeight, g_GameFieldWidth / 2);
	m_ButtonBetPlus->SetText("+", m_FontBig, ColorBlack);

	curX += g_GameFieldWidth + g_GameMarginX;

	m_LabelLines = new Label(m_Renderer);
	m_LabelLines->SetText("Lines", m_FontSmall, ColorBlack);
	m_LabelLines->SetX(curX + (g_GameFieldWidth - m_LabelLines->GetWidth()) / 2);
	m_LabelLines->SetY(g_GameMenuHeight - m_LabelLines->GetHeight());

	m_TextFieldLines = new TextField(m_Renderer);
	m_TextFieldLines->SetX(curX);
	m_TextFieldLines->SetY(g_GameMenuHeight);
	m_TextFieldLines->SetFieldSize(g_GameFieldHeight, g_GameFieldWidth);
	m_TextFieldLines->SetText("0", m_FontSmall, ColorWhite);

	m_ButtonLinesMinus = new Button(m_Renderer);
	m_ButtonLinesMinus->SetX(curX);
	m_ButtonLinesMinus->SetY(g_GameMenuHeight + g_GameFieldHeight);
	m_ButtonLinesMinus->SetFieldSize(g_GameFieldHeight, g_GameFieldWidth / 2);
	m_ButtonLinesMinus->SetText("-", m_FontBig, ColorBlack);

	m_ButtonLinesPlus = new Button(m_Renderer);
	m_ButtonLinesPlus->SetX(curX + g_GameFieldWidth / 2);
	m_ButtonLinesPlus->SetY(g_GameMenuHeight + g_GameFieldHeight);
	m_ButtonLinesPlus->SetFieldSize(g_GameFieldHeight, g_GameFieldWidth / 2);
	m_ButtonLinesPlus->SetText("+", m_FontBig, ColorBlack);

	curX += g_GameFieldWidth + g_GameMarginX;

	m_ButtonMaxBet = new Button(m_Renderer);
	m_ButtonMaxBet->SetX(curX);
	m_ButtonMaxBet->SetY(g_GameMenuHeight);
	m_ButtonMaxBet->SetFieldSize(g_GameMaxBetHeight, g_GameMaxBetWidth);
	m_ButtonMaxBet->SetText("Max Bet", m_FontBig, ColorBlack);

	curX += g_GameMaxBetWidth + g_GameMarginX;

	m_LabelCurCredits = new Label(m_Renderer);
	m_LabelCurCredits->SetText("Credits", m_FontSmall, ColorBlack);
	m_LabelCurCredits->SetX(curX + (g_GameFieldWidth - m_LabelCurCredits->GetWidth()) / 2);
	m_LabelCurCredits->SetY(g_GameMenuHeight + g_GameFieldHeight - m_LabelCurCredits->GetHeight());

	m_TextFieldCurCredits = new TextField(m_Renderer);
	m_TextFieldCurCredits->SetX(curX);
	m_TextFieldCurCredits->SetY(g_GameMenuHeight + g_GameFieldHeight);
	m_TextFieldCurCredits->SetFieldSize(g_GameFieldHeight, g_GameFieldWidth);
	m_TextFieldCurCredits->SetText("0", m_FontSmall, ColorWhite);

	curX += g_GameFieldWidth + g_GameMarginX;

	m_LabelTotalBet = new Label(m_Renderer);
	m_LabelTotalBet->SetText("Total Bet", m_FontSmall, ColorBlack);
	m_LabelTotalBet->SetX(curX + (g_GameFieldWidth - m_LabelTotalBet->GetWidth()) / 2);
	m_LabelTotalBet->SetY(g_GameMenuHeight + g_GameFieldHeight - m_LabelTotalBet->GetHeight());

	m_TextFieldTotalBet = new TextField(m_Renderer);
	m_TextFieldTotalBet->SetX(curX);
	m_TextFieldTotalBet->SetY(g_GameMenuHeight + g_GameFieldHeight);
	m_TextFieldTotalBet->SetFieldSize(g_GameFieldHeight, g_GameFieldWidth);
	m_TextFieldTotalBet->SetText("0", m_FontSmall, ColorWhite);

	curX += g_GameFieldWidth + g_GameMarginX;

	m_LabelPaid = new Label(m_Renderer);
	m_LabelPaid->SetText("Paid", m_FontSmall, ColorBlack);
	m_LabelPaid->SetX(curX + (g_GameFieldWidth - m_LabelPaid->GetWidth()) / 2);
	m_LabelPaid->SetY(g_GameMenuHeight + g_GameFieldHeight - m_LabelPaid->GetHeight());

	m_TextFieldPaid = new TextField(m_Renderer);
	m_TextFieldPaid->SetX(curX);
	m_TextFieldPaid->SetY(g_GameMenuHeight + g_GameFieldHeight);
	m_TextFieldPaid->SetFieldSize(g_GameFieldHeight, g_GameFieldWidth);
	m_TextFieldPaid->SetText("0", m_FontSmall, ColorWhite);

	curX += g_GameFieldWidth + g_GameMarginX;

	m_ButtonPlay = new Button(m_Renderer);
	m_ButtonPlay->SetX(curX);
	m_ButtonPlay->SetY(g_GameMenuHeight);
	m_ButtonPlay->SetFieldSize(g_GamePlayHeight, g_GamePlayWidth);
	m_ButtonPlay->SetText("Play", m_FontBig, ColorBlack);
}

Game::~Game()
{
	SDL_DestroyTexture(m_TextureBackground);

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

	TTF_CloseFont(m_FontBig);
	TTF_CloseFont(m_FontSmall);

	m_TextureBackground = NULL;

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

	m_FontBig = NULL;
	m_FontSmall = NULL;
}

void Game::Render(bool UpdateOnly)
{
	if(!UpdateOnly)
	{
		SDL_RenderCopy(m_Renderer, m_TextureBackground, NULL, NULL);
	}

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
}

void Game::EventHandler(SDL_Event& e)
{

}

void Game::SetCredits(unsigned int newCredits)
{

}




































