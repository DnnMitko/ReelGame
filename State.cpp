#include "State.h"

State::State()
{
	m_Renderer = NULL;

	m_bSwitch = false;
	m_bTransitionIn = false;
	m_bTransitionOut = false;
}

State::State(SDL_Renderer* newRenderer)
{
	m_Renderer = newRenderer;

	m_bSwitch = false;
	m_bTransitionIn = false;
	m_bTransitionOut = false;
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
