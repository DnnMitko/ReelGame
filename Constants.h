#ifndef CONSTANTS_H_
#define CONSTANTS_H_



const int g_ScreenWidth = 1280;
const int g_ScreenHeight = 720;

const char g_LabelFont[] = "fonts/Roboto-Medium.ttf";
const char g_WinFont[] = "fonts/Digitalt.ttf";

const char g_ButtonNewGame[] = "Start new game";
const char g_ButtonResumeGame[] = "Resume game";
const char g_ButtonInsertCredit[] = "Insert credit";
const char g_ButtonInfo[] = "Info";

const int g_IntroButtonWidth = 300;
const int g_IntroButtonHeight = 70;
const int g_IntroFontSize = 40;
const int g_IntroFirstButtonY = 300;

const int g_GameMenuHeight = g_ScreenHeight - 80;
const int g_GameOffsetX = 50;
const int g_GameMarginX = 20;
const int g_GamePayTableWidth = 180;
const int g_GamePayTableHeight = 60;
const int g_GameMaxBetWidth = 150;
const int g_GameMaxBetHeight = 60;
const int g_GamePlayHeight = 60;
const int g_GamePlayWidth = 120;
const int g_GameFieldWidth = 120;
const int g_GameFieldHeight = 30;


const float g_Denominator = 0.01;
const int g_OutroWidth = 700;
const int g_OutroHeight = 360;
const int g_OutroFontSizeMoney = 70;
const int g_OutroFontSizeWin = 150;
const int g_OutroWinSignLimits[2] = {100, 1000};
const int g_OutroWinOffsetY = -80;
const std::string g_OutroWinSign[3] = { "Win", "Super Win", "Mega Win" };
const int g_OutroMoneyWidth = 550;
const int g_OutroMoneyHeight = 100;
const int g_OutroMoneyOffsetY = 115;
const char g_OutroBackground[] = "images/OutroBackground.png";

const int g_WinWidth = 640;
const int g_WinHeight = 427;
const int g_WinFontSizeCredits = 70;
const int g_WinFontSizeSign = 150;
const int g_WinSignOffsetY = -80;
const char g_WinSign[] = "You won:";
const int g_WinCreditsWidth = 550;
const int g_WinCreditHeight = 100;
const int g_WinCreditOffsetY = 115;
const char g_WinBackground[] = "images/WinBackground.png";

const char g_ButtonSprite[] = "images/ButtonSprite.png";
const int g_ButtonSpriteWidth = 296;
const int g_ButtonSpriteHeight = 174;


#endif /* CONSTANTS_H_ */
