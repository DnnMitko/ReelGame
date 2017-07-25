#include "Chest.h"

// Default value for static member.
SDL_Texture* Chest::m_TextureChestClosed = NULL;
SDL_Texture* Chest::m_TextureChestOpen = NULL;

Chest::Chest()
{
	// Null all members.
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
	// Save renderer.
	m_Renderer = newRenderer;

	// If textures are not loaded,
	// load textures
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

	// Position and set size for chests to be drawn on screen.
	m_FieldRect.x = 0;
	m_FieldRect.y = 0;
	m_FieldRect.w = g_BonusChestWidth;
	m_FieldRect.h = g_BonusChestHeight;

	// Set change flag to true.
	m_bHasChanged = true;

	// Set open flag to false.
	m_bIsOpened = false;
}

Chest::~Chest()
{
	// Free textures.
	SDL_DestroyTexture(m_TextureChestClosed);
	SDL_DestroyTexture(m_TextureChestOpen);

	// Null the pointers.
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
	// If we want updates.
	if(UpdateOnly)
	{
		// Check for changes.
		if(m_bHasChanged)
		{
			// Gray-out the chest.
			SDL_SetRenderDrawColor(m_Renderer, 0x33, 0x33, 0x33, 0xFF);
			SDL_RenderFillRect(m_Renderer, &m_FieldRect);

			// Draw the chest.
			Render(false);
		}
	}
	else
	{
		// If chest is opened.
		if(m_bIsOpened)
			// Draw the open chest texture.
			SDL_RenderCopy(m_Renderer, m_TextureChestOpen, NULL, &m_FieldRect);
		else
			// Draw the closed chest texture.
			SDL_RenderCopy(m_Renderer, m_TextureChestClosed, NULL, &m_FieldRect);
	}
}

bool Chest::IsIn(int x, int y)
{
	// If x is outside the rect.
	if(x < m_FieldRect.x || x > (m_FieldRect.x + m_FieldRect.w))
		return false;
	else if(y < m_FieldRect.y || y > (m_FieldRect.y + m_FieldRect.h))
		return false;

	return true;
}

void Chest::Open()
{
	// We changed.
	m_bHasChanged = true;

	// Open the chest.
	m_bIsOpened = true;
}

void Chest::Close()
{
	// We changed.
	m_bHasChanged = true;

	// Close the chest.
	m_bIsOpened = false;
}






















