#pragma once

#pragma region project include
#include "MoveEntity.h"
#include "EEnemyTypes.h"
#pragma endregion

/// <summary>
/// move enemy class
/// </summary>
class GMoveEnemy : public CMoveEntity
{
public:
#pragma region constructor
	/// <summary>
	/// constructor
	/// </summary>
	/// <param name="_pos">position of object</param>
	/// <param name="_size">width (x) and height (y) of object</param>
	GMoveEnemy(SVector2 _pos = SVector2(), SVector2 _size = SVector2()) : CMoveEntity(_pos, _size) {}

	/// <summary>
	/// constructor
	/// </summary>
	/// <param name="_pos">position of object</param>
	/// <param name="_size">width and height of object</param>
	/// <param name="_pFileName">absolute file path name</param>
	GMoveEnemy(SVector2 _pos, SVector2 _size, const char* _pFileName) : CMoveEntity(_pos, _size, _pFileName) {}
#pragma endregion

#pragma region destructor
	/// <summary>
	/// destructor
	/// </summary>
	virtual ~GMoveEnemy() {}
#pragma endregion

#pragma region public override function
	/// <summary>
	/// update every frame
	/// </summary>
	/// <param name="_deltaTime">time since last frame</param>
	virtual void Update(float _deltaTime) override;

	/// <summary>
	/// render every frame
	/// </summary>
	virtual void Render() override;
#pragma endregion

#pragma region public function
	/// <summary>
	/// initialize move enemy
	/// </summary>
	void Init();
#pragma endregion

#pragma region public inline function
	/// <summary>
	/// set the type of enemy
	/// </summary>
	inline void SetType(EEnemyTypes _eType) { m_eType = _eType; }
#pragma endregion

private:
#pragma region private variable
	/// <summary>
	/// set enemy type (Default = WALKER)
	/// </summary>
	EEnemyTypes m_eType = WALKER;
#pragma endregion

#pragma region private primitive variable
	/// <summary>
	/// time
	/// </summary>
	float m_time = 0.0f;

	/// <summary>
	/// intervall of shot time
	/// </summary>
	float m_jumpInter = 1.0f;

	/// <summary>
	/// intervall of shot time
	/// </summary>
	float m_shotInter = 2.0f;
#pragma endregion
};