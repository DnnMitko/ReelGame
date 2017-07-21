#include "Chest.h"

SDL_Texture* Chest::m_TextureChestClosed = NULL;
SDL_Texture* Chest::m_TextureChestOpen = NULL;

Chest::Chest()
{
	m_Renderer = NULL;

	m_FieldRect.x = 0;
	m_FieldRect.y = 0;
	m_FieldRect.w = 0;
	m_FieldRect.h = 0;

	m_bHasChanged = true;
	m_bIsOpened = false;
}

Chest::Chest(SDL_Renderer* newRenderer)
{
	m_Renderer = newRenderer;

	if(!m_TextureChestClosed)
	{
		m_TextureChestClosed = IMG_LoadTexture(newRenderer, "images/ChestClosed.png");
		if(!m_TextureChestClosed)
		{
			std::cerr << "Failed to load ChestClosed.png. IMG Error: " << IMG_GetError() << "\n";
		}
	}

	if(!m_TextureChestOpen)
	{
		m_TextureChestOpen = IMG_LoadTexture(newRenderer, "images/ChestOpen.png");
		if(!m_TextureChestOpen)
		{
			std::cerr << "Failed to load ChestOpen.png. IMG Error: " << IMG_GetError() << "\n";
		}
	}

	m_FieldRect.x = 0;
	m_FieldRect.y = 0;
	m_FieldRect.w = g_BonusChestWidth;
	m_FieldRect.h = g_BonusChestHeight;

	m_bHasChanged = true;
	m_bIsOpened = false;
}

Chest::~Chest()
{
	SDL_DestroyTexture(m_TextureChestClosed);
	SDL_DestroyTexture(m_TextureChestOpen);

	m_TextureChestClosed = NULL;
	m_TextureChestOpen = NULL;
}

void Chest::SetX(int newX)
{
	m_FieldRect.x = newX;
}

void Chest::SetY(int newY)
{
	m_FieldRect.y = newY;
}

void Chest::Render(bool UpdateOnly)
{
	if(UpdateOnly)
	{
		if(m_bHasChanged)
		{
			SDL_SetRenderDrawColor(m_Renderer, 0x33, 0x33, 0x33, 0xFF);
			SDL_RenderFillRect(m_Renderer, &m_FieldRect);

			Render(false);
		}
	}
	else
	{
		if(m_bIsOpened)
			SDL_RenderCopy(m_Renderer, m_TextureChestOpen, NULL, &m_FieldRect);
		else
			SDL_RenderCopy(m_Renderer, m_TextureChestClosed, NULL, &m_FieldRect);
	}
}

bool Chest::IsIn(int x, int y)
{
	if(x < m_FieldRect.x || x > (m_FieldRect.x + m_FieldRect.w))
		return false;
	else if(y < m_FieldRect.y || y > (m_FieldRect.y + m_FieldRect.h))
		return false;

	return true;
}

void Chest::Open()
{
	m_bHasChanged = true;
	m_bIsOpened = true;
}

void Chest::Close()
{
	m_bHasChanged = true;
	m_bIsOpened = false;
}






















