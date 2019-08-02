#pragma once

#pragma region project include
#include "MoveEntity.h"
#include "EEnemyTypes.h"
#pragma endregion

#pragma region forward declaration
class CSound;
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
	/// <param name="_deltaSeconds">time since last frame</param>
	virtual void Update(float _deltaSeconds) override;

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
	/// set type of enemy
	/// </summary>
	void SetType(EEnemyTypes _eType) { m_eType = _eType; }
#pragma endregion

private:
#pragma region private pointer
	/// <summary>
	/// shot sound
	/// </summary>
	CSound* m_pShot = nullptr;
#pragma region

#pragma region private variable
	/// <summary>
	/// set enemy type
	/// </summary>
	EEnemyTypes m_eType = WALKER;
#pragma endregion

#pragma region private primitive variable
	/// <summary>
	/// time counter
	/// </summary>
	float m_time = 0.0f;

	/// <summary>
	/// interval of jump
	/// </summary>
	float m_jumpInter = 2.0f;

	/// <summary>
	/// interval of shot
	/// </summary>
	float m_shotInter = 3.0f;
#pragma endregion
};