#pragma once

#pragma region project include
#include "TexturedEntity.h"
#pragma endregion

/// <summary>
/// player class
/// </summary>
class GPlayer : public CTexturedEntity
{
public:
#pragma region constructor
	/// <summary>
	/// constructor
	/// </summary>
	/// <param name="_pos">position of entity</param>	
	/// <param name="_size">size of texture (x = width)</param>
	/// <param name="_pFileName">relative path name of texture</param>
	GPlayer(SVector2 _pos, SVector2 _size, const char* _pFileName)
		: CTexturedEntity(_pos, _size, _pFileName) {}
#pragma endregion

#pragma region destructor
	/// <summary>
	/// destructor
	/// </summary>
	virtual ~GPlayer() {}
#pragma endregion

#pragma region public override function
	/// <summary>
	/// update every frame
	/// </summary>
	/// <param name="_deltaTime">time since last frame</param>
	virtual void Update(float _deltaTime) override;
#pragma endregion

#pragma region public inline function
	/// <summary>
	/// set movement speed of player
	/// </summary>
	/// <param name="_speed">movement speed in pixel per second</param>
	inline void SetSpeed(float _speed) { m_speed = _speed; }
#pragma endregion

protected:
#pragma region protected primitive variable
	/// <summary>
	/// movement speed in pixel per second
	/// </summary>
	float m_speed = 0.0f;

	/// <summary>
	/// time since start falling in seconds
	/// </summary>
	float m_fallTime = 0.0f;
#pragma endregion

#pragma region protected variable
	/// <summary>
	/// movement direction
	/// </summary>
	SVector2 m_movement = SVector2();
	bool m_attack = false;
	bool m_jump = true;
	float m_time = 0.0f;
#pragma endregion
};