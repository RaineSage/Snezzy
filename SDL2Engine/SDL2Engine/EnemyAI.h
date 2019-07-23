#pragma once

#pragma region project include
#include "TexturedEntity.h"
#include "EEnemyTypes.h"
#pragma endregion

class GEnemyAI : public CTexturedEntity
{
public:
	GEnemyAI(SVector2 _pos, SVector2 _size, const char* _pFileName)
		: CTexturedEntity(_pos, _size, _pFileName) {m_movement.X = -1.0f;}

	virtual void Update(float _deltaTime) override;

	void SetSpeed(float _speed) { m_speed = _speed; }

	void SetType(EnemyTypes _type) { m_type = _type; }

	void SetJumpTime(float _jumpTime) { m_jumpTime = _jumpTime; }

	void SetShotInterval(float _shotInter) { m_shotInter = _shotInter; }

protected:
	SVector2 m_movement = SVector2();
	EnemyTypes m_type = WALKER;
	float m_speed = 0.0f;
	float m_fallTime = 0.0f;

	float m_time = 0.0f;
	float m_jumpTime = 1.0f;

	float m_shotInter = 1.0f;
};

