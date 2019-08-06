#include "Timer.h"

float GTimer::m_timeHealth = 0.0f;

void GTimer::Update(float _deltaTime)
{
	m_timeHealth -= _deltaTime;

	sprintf_s(m_cTimeHealth, "%d", (int) m_timeHealth);
	m_pText = m_cTimeHealth;
	Load();
}

