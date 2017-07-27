#include "Reel.h"

Reel::Reel()
{
	m_Renderer = NULL;

	m_TextureFrame = NULL;
	m_TextureBackground = NULL;

	m_Sound = NULL;

	m_bTransitionIn = false;
	m_bTransitionOut = false;

	m_bIsAnimated = false;

	m_iY = 0;

	for(int i = 0; i < 5; i++)
		m_Slots[i] = NULL;
}

Reel::Reel(SDL_Renderer* newRenderer)
{
	m_Renderer = newRenderer;

	m_bTransitionIn = false;
	m_bTransitionOut = false;

	m_bIsAnimated = false;

	m_TextureFrame = IMG_LoadTexture(m_Renderer, g_ReelFrame);
		if (m_TextureFrame == NULL)
			std::cerr << "Failed to load texture Background!! SDL ERROR: " << IMG_GetError() << std::endl;

	m_TextureBackground = IMG_LoadTexture(m_Renderer, g_GameBackground);
		if (m_TextureBackground == NULL)
			std::cerr << "Failed to load texture Background!! SDL ERROR: " << IMG_GetError() << std::endl;

	m_Sound = Mix_LoadWAV(g_ReelSound);
	if(m_Sound == NULL)
			std::cerr << "Failed to load slot sound effect! SDL Error: " << Mix_GetError() << std::endl;

	m_iY = 0;

	for(int i = 0; i < 5; i++)
	{
		m_Slots[i] = new Slot(m_Renderer);
		m_Slots[i]->SetX(g_ReelSlotX + i * (g_FigureSize + g_ReelSlotMargin));
		m_Slots[i]->SetY(m_iY + g_ReelSlotY);
		m_Slots[i]->SetDelay(i * g_ReelDelayDiff + g_SlotRollTime);
	}
}

Reel::~Reel()
{
	SDL_DestroyTexture(m_TextureFrame);
	m_TextureFrame = NULL;

	SDL_DestroyTexture(m_TextureBackground);
	m_TextureBackground = NULL;

	Mix_FreeChunk(m_Sound);
	m_Sound = NULL;

	for(int i = 0; i < 5; i++)
	{
		delete m_Slots[i];
		m_Slots[i] = NULL;
	}
}

void Reel::Render(bool UpdateOnly)
{
	if(!m_Renderer || !m_TextureBackground || !m_TextureFrame)
		return;

	if(m_bTransitionIn)
		TransitionIn();
	else if(m_bTransitionOut)
		TransitionOut();

	for(int i = 0; i < 5; i++)
		m_Slots[i]->Render(UpdateOnly);

	if(!UpdateOnly || !HasStopped() || m_bIsAnimated)
	{
		SDL_Rect tempRect;
		tempRect.x = 0;
		tempRect.y = m_iY;
		tempRect.w = g_ScreenWidth;
		tempRect.h = g_ScreenHeight;
		SDL_RenderCopy(m_Renderer, m_TextureFrame, NULL, &tempRect);
	}
}

void Reel::PrepTransitionIn()
{
	m_bTransitionIn = true;

	m_iY = -g_ScreenHeight;

	for(int i = 0; i < 5; i++)
		m_Slots[i]->SetY(m_iY + g_ReelSlotY);
}

bool Reel::InTransition()
{
	if(m_bTransitionIn || m_bTransitionOut)
		return true;

	return false;
}

void Reel::Hide()
{
	m_bTransitionOut = true;
}

void Reel::SetResult(std::string newResult)
{
	for(int i = 0; i < 5; i++)
		m_Slots[i]->SetResult(newResult.substr(i * 3, 3));
}

std::string Reel::GetResult()
{
	std::string strResult = "";

	for(int i = 0; i < 5; i++)
		strResult += m_Slots[i]->GetResult();

	return strResult;
}

void Reel::Spin()
{
	for(int i = 0; i < 5; i++)
	{
		m_Slots[i]->Stop();

		if(i % 2 == 0)
			m_Slots[i]->Spin(true);
		else
			m_Slots[i]->Spin(false);
	}

	Mix_PlayChannel(-1, m_Sound, 0);
}

bool Reel::HasStopped()
{
	bool bResult = true;

	for(int i = 0; i < 5; i++)
		bResult = bResult && m_Slots[i]->HasStopped();

	return bResult;
}

void Reel::Animate(std::string strAnimate)
{
	m_bIsAnimated = true;

	std::string tempStr;
	for(int i = 0; i < 5; i++)
	{
		tempStr = strAnimate.substr(i * 3, 3);
		m_Slots[i]->Animate(tempStr);
	}
}

void Reel::Pause()
{
	m_bIsAnimated = false;

	for(int i = 0; i < 5; i++)
		m_Slots[i]->Stop();
}

void Reel::TransitionIn()
{
	if(m_iY == 0)
		m_bTransitionIn = false;
	else
	{
		m_iY += g_TransitionStep;

		for(int i = 0; i < 5; i++)
			m_Slots[i]->SetY(m_iY + g_ReelSlotY);
	}
}

void Reel::TransitionOut()
{
	if(m_iY == -g_ScreenHeight)
		m_bTransitionOut = false;
	else
	{
		m_iY -= g_TransitionStep;

		for(int i = 0; i < 5; i++)
			m_Slots[i]->SetY(m_iY + g_ReelSlotY);
	}
}






















