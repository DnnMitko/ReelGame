#include "State.h"

State::State()
{
	m_bSwitch = false;
	m_Renderer = NULL;
}

State::~State()
{
}

bool State::GetSwitch() const
{
	return m_bSwitch;
}

void State::ResetSwitch()
{
	m_bSwitch = false;
}

void State::SetRenderer(SDL_Renderer* newRenderer)
{
	m_Renderer = newRenderer;
}
