#include "Timer.h"
#include "SDL.h"

Timer* Timer::s_Instance = nullptr;

void Timer::Tick() {
	auto curr_Time = SDL_GetTicks();

	m_DeltaTime = (curr_Time - m_LastTime) * (TARGET_FPS / 1000.0f);

	if (m_DeltaTime > TARGET_DELTATIME)
		m_DeltaTime = TARGET_DELTATIME;

	m_LastTime = curr_Time;
}