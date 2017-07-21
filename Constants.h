#ifndef CONSTANTS_H_
#define CONSTANTS_H_

#include <string>


const int g_ScreenWidth = 1280;
const int g_ScreenHeight = 720;

const char g_FontLabel[] = "fonts/Roboto-Medium.ttf";
const char g_FontTitle[] = "fonts/Digitalt.ttf";

const int g_TransitionStep = 20;

const char g_BackgroundSound[] =  "sounds/BackgroundSound.mp3";
const char g_IntroButtonNewGame[] = "Start new game";
const char g_IntroButtonResumeGame[] = "Resume game";
const char g_IntroLabelInsertCredit[] = "Credit";
const char g_IntroButtonInfo[] = "Info";
const char g_IntroLabelCredits[] = "Credits";
const char g_IntroLabelVolume[] = "Volume";
const char g_IntroButtonPlus[] = "+";
const char g_IntroButtonMinus[] = "-";
const int g_IntroLabelButtonX = 572;
const int g_IntroLabelButtonY = 625;
const int g_IntroLabelCreditX = 587;
const int g_IntroLabelCreditY = 465;
const int g_IntroButtonWidth = 300;
const int g_IntroButtonHeight = 70;
const int g_IntroButtonVolumePlusX = 715;
const int g_IntroCreditsWidth = 280;
const int g_IntroCreditsHeight = 50;
const int g_IntroFontSize = 40;
const int g_IntroFirstButtonY = 300;
const int g_IntroCreditIncrement = 25;
const int g_IntroVolumeStart = 64;
const int g_IntroVolumeIncrement = 16;

const char g_InfoScreen1[] = "images/info_1.png";
const char g_InfoScreen2[] = "images/info_2.png";
const int g_InfoWidth = 596;
const int g_InfoHeight = 357;
const int g_InfoFontSize = 30;
const int g_InfoButtonWidth = 50;
const int g_InfoButtonHeight = 40;
const int g_InfoButtonNextOffsetX = -10;
const int g_InfoButtonNextOffsetY = -10;
const std::string g_InforButtonNext[2] = { "<<", ">>" };
const int g_InfoButtonExitOffsetX = -10;
const int g_InfoButtonExitOffsetY = 10;
const char g_InfoButtonExit[] = "X";

const int g_GameMenuHeight = g_ScreenHeight - 80;
const char g_GameBackground[] = "images/GameBackground.png";
const char g_GameLabelBet[] = "Bet";
const char g_GameLabelLines[] = "Lines";
const char g_GameButtonMaxBet[] = "Max Bet";
const char g_GameLabelCredits[] = "Credits";
const char g_GameLabelTotalBet[] = "Total Bet";
const char g_GameLabelPaid[] = "Paid";
const char g_GameButtonPlay[] = "Play";
const char g_GameButtonCashOut[] = "Cash Out";
const int g_GameOffsetX = 5;
const int g_GameMarginX = 20;
const int g_GameFontSizeBig = 30;
const int g_GameFontSizeSmall = 20;
const int g_GamePayTableWidth = 150;
const int g_GamePayTableHeight = 60;
const int g_GameMaxBetWidth = 130;
const int g_GameMaxBetHeight = 60;
const int g_GamePlayHeight = 60;
const int g_GamePlayWidth = 80;
const int g_GameCashOutWidth = 150;
const int g_GameCashOutHeight = 60;
const int g_GameFieldWidth = 120;
const int g_GameFieldHeight = 30;
const int g_GameBetIncriment = 25;
const int g_GameMaxBetAmmount = 500;
const int g_GameMaxLines = 15;

const int g_BonusWidth = 598;
const int g_BonusHeight = 334;
const int g_BonusHeightTransition = -347;
const char g_BonusTitle[] = "Bonus Game";
const char g_BonusSubTitle[] = "Choose your treasure!";
const int g_BonusFontSizeCredits = 55;
const int g_BonusFontSizeWin = 80;
const int g_BonusTitleOffsetY = -120;
const int g_BonusCreditsWidth = 550;
const int g_BonusCreditHeight = 80;
const int g_BonusCreditOffsetY = 115;
const int g_BonusChest1OffsetX = 45;
const int g_BonusChest2OffsetX = 242;
const int g_BonusChest3OffsetX = 439;
const int g_BonusChestOffsetY = 94;
const int g_BonusChestWidth = 114;
const int g_BonusChestHeight = 119;
const int g_BonusLowerLimit = 2;
const int g_BonusUpperLimit = 30;
const int g_BonusDelay = 3000;
const char g_BonusWinMessage[] = "YOU WON: ";
const char g_BonusGameBackground[] = "images/BonusGameBackground.png";
const char g_BonusGameBackgroundInit[] = "images/BonusGameBackgroundInit.png";
const char g_BonusTempWinMessage[] = "So far, you won:";
const int g_BonusTempWinOffsetX = 60;
const int g_BonusTempWinOffsetY = -120;
const int g_BonusTempWinFieldWidth = 300;
const int g_BonusTempWinFieldHeight = 60;
const int g_BonusStartOffsetX = -180;
const int g_BonusStartOffsetY = -120;
const int g_BonusStartWidth = 160;
const int g_BonusStartHeight = 90;
const char g_BonusSound[] = "sounds/Bonus.wav";

const float g_Denominator = 0.01;
const int g_OutroDelay = 10000;
const int g_OutroWidth = 700;
const int g_OutroHeight = 360;
const int g_OutroHeightTransition = -360;
const int g_OutroFontSizeMoney = 70;
const int g_OutroFontSizeWin = 150;
const int g_OutroWinSignLimits[2] = {100, 1000};
const int g_OutroWinOffsetY = -80;
const std::string g_OutroWinSign[3] = { "Win", "Super Win", "Mega Win" };
const int g_OutroMoneyWidth = 550;
const int g_OutroMoneyHeight = 100;
const int g_OutroMoneyOffsetY = 115;
const char g_OutroBackground[] = "images/OutroBackground.png";
const char g_OutroSound[] = "sounds/Clap.wav";

const int g_WinWidth = 640;
const int g_WinHeight = 427;
const int g_WinHeightTransition = -434;
const int g_WinDelay = 3000;
const int g_WinFontSizeCredits = 70;
const int g_WinFontSizeSign = 150;
const int g_WinSignOffsetY = -80;
const char g_WinSign[] = "You won:";
const int g_WinCreditsWidth = 550;
const int g_WinCreditHeight = 100;
const int g_WinCreditOffsetY = 115;
const char g_WinBackground[] = "images/WinBackground.png";
const char g_WinSound[] = "sounds/Win.wav";

const char g_ButtonSprite[] = "images/ButtonSprite.png";
const int g_ButtonSpriteWidth = 296;
const int g_ButtonSpriteHeight = 174;
const char g_ButtonSound[] = "sounds/ButtonClick.wav";

const float g_LinesFigure1x3 = 1.2;
const float g_LinesFigure2x3 = 1.4;
const float g_LinesFigure3x3 = 1.5;
const float g_LinesFigure4x3 = 1.8;
const float g_LinesFigure5x3 = 2.0;
const float g_LinesFigure1x4 = 2.2;
const float g_LinesFigure2x4 = 2.4;
const float g_LinesFigure3x4 = 2.5;
const float g_LinesFigure4x4 = 2.8;
const float g_LinesFigure5x4 = 3.0;
const float g_LinesFigure1x5 = 3.2;
const float g_LinesFigure2x5 = 3.4;
const float g_LinesFigure3x5 = 3.5;
const float g_LinesFigure4x5 = 3.8;
const float g_LinesFigure5x5 = 4.0;
const int g_LinesMax = 15;

const char g_Figure[] = "images/Figures.png";
const int g_FigureSize = 185;
const char g_FigureID_1 = '1';
const char g_FigureID_2 = '2';
const char g_FigureID_3 = '3';
const char g_FigureID_4 = '4';
const char g_FigureID_5 = '5';
const char g_FigureID_6 = '6';




















#endif /* CONSTANTS_H_ */
