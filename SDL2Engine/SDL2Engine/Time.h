#pragma once

#pragma region system include
#include <time.h>
#pragma endregion

/// <summary>
/// time class
/// </summary>
class CTime
{
public:
#pragma region constructor
	/// <summary>
	/// constructor
	/// </summary>
	CTime() {}
#pragma endregion

#pragma region public inline function
	/// <summary>
	/// get time since last frame in seconds
	/// </summary>
	/// <returns>time since last frame in seconds</returns>
	static inline float GetDeltaTime() { return m_deltaTime > 0.2f ? 0.0f : m_deltaTime; }

	/// <summary>
	/// get frames per second
	/// </summary>
	/// <returns>frames per second</returns>
	static inline int GetFPS() { return m_fps; }
#pragma endregion

#pragma region public function
	/// <summary>
	/// update time
	/// </summary>
	void Update();
#pragma endregion

private:
#pragma region private primitive variable
	/// <summary>
	/// frames per second
	/// </summary>
	static short m_fps;

	/// <summary>
	/// frames since last update
	/// </summary>
	int m_framesSinceLastUpdate = 0;

	/// <summary>
	/// time since last update in seconds
	/// </summary>
	static float m_deltaTime;

	/// <summary>
	/// last update time stamp
	/// </summary>
	clock_t m_lastUpdate = 0.0f;

	/// <summary>
	/// time since last time stamp
	/// </summary>
	clock_t m_timeSinceLastTimeStamp = 0.0f;
#pragma endregion
};