#pragma region project include
#include "Bullet.h"
#include "Config.h"
#pragma endregion

#pragma region public override function
// update every frame
void GBullet::Update(float _deltaTime)
{
	//CMoveEntity::Update(_deltaTime);

	m_movement.X *= -(m_addForce);
}

// render every frame
void GBullet::Render()
{
	CMoveEntity::Render();
}
#pragma endregion

#pragma region public function
// initialize move enemy
void GBullet::Init()
{
	m_gravity = true;
	m_speed = CConfig::s_MoveEnemySpeed;

	m_pTag = "Enemy";

	m_colType = ECollisionType::DYNAMIC;

	if (rand() % 2)
		m_movement.X = -1.0f;
	else
		m_movement.X = 1.0f;
}
#pragma endregion
