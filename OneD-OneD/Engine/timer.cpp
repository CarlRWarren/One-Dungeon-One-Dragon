#include "timer.h"
#include <cassert>
#include <algorithm>

bool Timer::Initialize(Engine* engine)
{
	m_engine = engine;
	m_timeScale = 1;
	m_paused = false;
	return true;
}

void Timer::Shutdown()
{
}

void Timer::Update()
{
	Uint32 ticks = SDL_GetTicks();
	Uint32 milliseconds = ticks - m_prevTicks;
	m_prevTicks = ticks;

	m_dt = (m_paused) ? 0.0f : milliseconds / 1000.0f;
	m_dt = std::min<float>(m_dt, 1.0f);

}

void Timer::Reset()
{
	m_prevTicks = SDL_GetTicks();
//	m_startTicks = SDL_GetTicks();
	// m_framecounter =  SDL_GetTicks();;
}

