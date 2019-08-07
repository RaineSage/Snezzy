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
class GBosses : public CMoveEntity
{
public:
#pragma region constructor
	/// <summary>
	/// constructor
	/// </summary>
	/// <param name="_pos">position of object</param>
	/// <param name="_size">width and height of object</param>
	/// <param name="_pFileName">absolute file path name</param>
	GBosses(SVector2 _pos, SVector2 _size, const char* _pFileName, int _health) : CMoveEntity(_pos, _size, _pFileName) { CMoveEntity::m_BossHealth = _health; }
#pragma endregion

#pragma region destructor
	/// <summary>
	/// destructor
	/// </summary>
	virtual ~GBosses() {}
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
	EEnemyTypes m_eType = CUTEULHU;
#pragma endregion

#pragma region private primitive variable
	/// <summary>
	/// jump time counter
	/// </summary>
	float m_jumpTime = 0.0f;

	/// <summary>
	/// shot time counter
	/// </summary>
	float m_shotTime = 0.0f;

	/// <summary>
	/// interval of jump
	/// </summary>
	float m_jumpInter = 2.0f;

	/// <summary>
	/// interval of shot
	/// </summary>
	float m_shotInter = 2.0f;

	/// <summary>
	/// push back
	/// </summary>
	float m_pushBack = -100;

	/// <summary>
	/// health of boss
	/// </summary>
	int m_health = 5;
#pragma endregion
};