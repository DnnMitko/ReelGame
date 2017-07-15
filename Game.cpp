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

	SDL_Color blackColor = {0x00, 0x00, 0x00, 0xFF};

	m_ButtonPayTable = new Button(m_Renderer);
	m_ButtonPayTable->SetX(0);
	m_ButtonPayTable->SetY(g_ScreenHeight - 60);
	m_ButtonPayTable->SetText("Pay Table", m_FontBig, blackColor);
	m_ButtonPayTable->SetFieldSize(60, 200);

	m_LabelBet = new Label(m_Renderer);
	m_LabelBet->SetText("Bet", m_FontSmall, blackColor);
	m_LabelBet->SetX(220 + (120 - m_LabelBet->GetWidth()) / 2);
	m_LabelBet->SetY(g_ScreenHeight - 60 - m_LabelBet->GetHeight());

	m_TextFieldBet = new TextField(m_Renderer);
	m_TextFieldBet->SetX(220);
	m_TextFieldBet->SetY(g_ScreenHeight - 60);
	m_TextFieldBet->SetFieldSize(30, 120);
	m_TextFieldBet->SetText("0", m_FontSmall, {255,255,255,255});

	m_ButtonBetMinus = new Button(m_Renderer);
	m_ButtonBetMinus->SetX(220);
	m_ButtonBetMinus->SetY(g_ScreenHeight - 30);
	m_ButtonBetMinus->SetFieldSize(30, 60);
	m_ButtonBetMinus->SetText("-", m_FontSmall, blackColor);

	m_ButtonBetPlus = new Button(m_Renderer);
	m_ButtonBetPlus->SetX(280);
	m_ButtonBetPlus->SetY(g_ScreenHeight - 30);
	m_ButtonBetPlus->SetFieldSize(30, 60);
	m_ButtonBetPlus->SetText("+", m_FontSmall, blackColor);

	m_LabelLines = new Label(m_Renderer);
	m_LabelLines->SetText("Lines", m_FontSmall, blackColor);
	m_LabelLines->SetX(360 + (120 - m_LabelLines->GetWidth()) / 2);
	m_LabelLines->SetY(g_ScreenHeight - 60 - m_LabelLines->GetHeight());

	m_TextFieldLines = new TextField(m_Renderer);
	m_TextFieldLines->SetX(360);
	m_TextFieldLines->SetY(g_ScreenHeight - 60);
	m_TextFieldLines->SetFieldSize(30, 120);
	m_TextFieldLines->SetText("0", m_FontSmall, {255,255,255,255});

	m_ButtonLinesMinus = new Button(m_Renderer);
	m_ButtonLinesMinus->SetX(360);
	m_ButtonLinesMinus->SetY(g_ScreenHeight - 30);
	m_ButtonLinesMinus->SetFieldSize(30, 60);
	m_ButtonLinesMinus->SetText("-", m_FontSmall, blackColor);

	m_ButtonLinesPlus = new Button(m_Renderer);
	m_ButtonLinesPlus->SetX(420);
	m_ButtonLinesPlus->SetY(g_ScreenHeight - 30);
	m_ButtonLinesPlus->SetFieldSize(30, 60);
	m_ButtonLinesPlus->SetText("+", m_FontSmall, blackColor);

	m_ButtonMaxBet = new Button(m_Renderer);
	m_ButtonMaxBet->SetX(500);
	m_ButtonMaxBet->SetY(g_ScreenHeight - 60);
	m_ButtonMaxBet->SetFieldSize(60, 150);
	m_ButtonMaxBet->SetText("Max Bet", m_FontBig, blackColor);

	m_LabelCurCredits = new Label(m_Renderer);
	m_LabelCurCredits->SetText("Credits", m_FontSmall, blackColor);
	m_LabelCurCredits->SetX(670 + (120 - m_LabelCurCredits->GetWidth()) / 2);
	m_LabelCurCredits->SetY(g_ScreenHeight - 30 - m_LabelCurCredits->GetHeight());

	m_TextFieldCurCredits = new TextField(m_Renderer);
	m_TextFieldCurCredits->SetX(670);
	m_TextFieldCurCredits->SetY(g_ScreenHeight - 30);
	m_TextFieldCurCredits->SetFieldSize(30, 120);
	m_TextFieldCurCredits->SetText("0", m_FontSmall, {255,255,255,255});
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
}

void Game::EventHandler(SDL_Event& e)
{

}

void Game::SetCredits(unsigned int newCredits)
{

}




































