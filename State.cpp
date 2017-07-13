#include "State.h"

State::State()
{
	m_Renderer = NULL;
	m_bSwitch = false;
}

State::State(SDL_Renderer* newRenderer)
{
	m_Renderer = newRenderer;
	m_bSwitch = false;
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
