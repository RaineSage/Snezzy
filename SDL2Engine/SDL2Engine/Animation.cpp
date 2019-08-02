#pragma region project include
#include "Animation.h"  
#pragma endregion

#pragma region public function
// update every frame
void CAnimation::Update(float _deltaTime)
{
	// inhcrease time since last animation frame update
	m_time += _deltaTime;

	// if time lower than time for one animation frame return
	if (m_time < m_animationTime / m_count)
		return;

	// increase current animation frame
	m_current++;

	// if current animation frame higher than count reset to begin
	if (m_current > m_count)
		m_current = 1;

	// reset time
	m_time = 0.0f;
}

// get current position in texture
SVector2 CAnimation::GetCurrentTexturePosition()
{
	// create vector2
	SVector2 v = SVector2();

	// set x of vector2 by start position x plus width of frame * current
	v.X = m_startPos.X + m_size.X * (m_current - 1);

	// set y of vector2 by start position y
	v.Y = m_startPos.Y;

	// return position of current frame in texture
	return v;
}
#pragma endregion