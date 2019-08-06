#pragma once

#pragma region project include
#include "Text.h"
#include <cstdio>
#pragma endregion

/// <summary>
/// class fot Timer objects
/// </summary>
class GTimer : public CText
{
#pragma region inline constructor
public:
	GTimer(int _timeHealth, CFont* _pFont, SRect _rect = SRect(), SColor _color = SColor()) : CText("Hallo", _pFont, _rect, _color) { m_timeHealth = _timeHealth; }
#pragma endregion

#pragma region public override function
	/// <summary>
	/// update every frame
	/// </summary>
	/// <param name="_deltaTime">time since last frame</param>
	void Update(float _deltaTime) override;
#pragma endregion

#pragma region public inline function
	/// <summary>
	/// removes time (enemy hits player)
	/// </summary>
	static void RemoveTime(int _time) { m_timeHealth -= _time; }

	/// <summary>
	/// adds time
	/// </summary>
	/// <param name="_time"></param>
	static void AddTime(int _time) { m_timeHealth += _time; }

	/// <summary>
	/// return time
	/// </summary>
	static float GetTime() { return m_timeHealth; }
#pragma endregion

private:
#pragma region private primitive variable
	/// <summary>
	/// start time/health
	/// </summary>
	static float m_timeHealth;

	/// <summary>
	/// time/health as char
	/// </summary>
	char m_cTimeHealth[10];
#pragma endregion

};

