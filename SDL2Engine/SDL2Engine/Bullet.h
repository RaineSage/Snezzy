#pragma once

#pragma region project include
#include "TexturedEntity.h"
#pragma endregion

class GBullet : public CTexturedEntity
{
public:
	GBullet(SVector2 _pos, SVector2 _size, const char* _pFileName)
		: CTexturedEntity(_pos, _size, _pFileName) { m_movement.X = -1.0f; }

	virtual void Update(float _deltaTime) override;

	void AddForce(float _force) { m_force = _force; }

private:
	SVector2 m_movement = SVector2();
	float m_force = 100.0f;
	float m_fallTime = 0.0f;

};

