#include "Outro.h"

Outro::Outro(SDL_Renderer* newRenderer)
{
	// TODO trqbva da namestq rectangle trqbva da gi napravq const

	SetRenderer(newRenderer);

	m_TextureBackground = NULL;
	m_TextureBackground = IMG_LoadTexture(m_Renderer, "images/fon.png");
	if(m_TextureBackground == NULL )
		std::cerr << "Failed to load TextureBackground! SDL Error: " << IMG_GetError() << std::endl;

	m_TextureWin = NULL;
}

Outro::~Outro()
{
	Destroy();
}

void Outro::RenderSmart()
{

}

void Outro::RenderForce()
{
	SDL_RenderCopy(m_Renderer, m_TextureBackground, NULL, &m_PositionBackground);

	//TODO posle za nadpisite sushtoto,kato gornoto

	//TODO credit.renderForce-tova,shte narisuva kredita na dadena poziciq
}
