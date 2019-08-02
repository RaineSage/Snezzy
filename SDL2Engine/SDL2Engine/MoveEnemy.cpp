#pragma region project include
#include "MoveEnemy.h"
#include "Config.h"
#include "Bullet.h"
#include "ContentManagement.h"
#include "Engine.h"
#include "Sound.h"
#pragma endregion

#pragma region public override function
// update every frame
void GMoveEnemy::Update(float _deltaSeconds)
{
	// update parent
	CMoveEntity::Update(_deltaSeconds);

	// jumping for enemy type JUMPER
	if (m_eType == JUMPER && m_grounded)
	{
		m_time += _deltaSeconds;

		if (m_time >= m_jumpInter)
		{
			m_fallTime = -0.5f;
			m_time = 0.0f;
		}
	}

	// shooting for enemy type Shooter
	if (m_eType == SHOOTER)
	{
		m_time += _deltaSeconds;
		
		if (m_time >= m_shotInter)
		{
			// create bullet
			GBullet* pBullet = new GBullet(SVector2(), SVector2(8, 8), "Texture/Bullet/T_Bullet.png");

			// spawn left (-1) or right (1) from player
			int spawnSide = -1;

			// set values
			pBullet->SetTag("Bullet");
			pBullet->SetPosition(SVector2(m_position.X + spawnSide * m_rect.w, m_position.Y + m_rect.h * 0.25f));
			pBullet->SetColType(ECollisionType::WALL);
			pBullet->SetSpeed(GConfig::s_BulletSpeed);
			pBullet->SetMovement(SVector2(spawnSide, 0.0f));

			// add bullet to content management
			CTM->AddPersistantObject(pBullet);

			// play shot sound
			m_pShot->Play();

			m_time = 0.0f;
		}
	}
}

// render every frame
void GMoveEnemy::Render()
{
	// render parent
	CMoveEntity::Render();
}
#pragma endregion

#pragma region public function
// initialize move enemy
void GMoveEnemy::Init()
{
	// set tag
	m_pTag = "Enemy";

	// set gravity and speed
	m_gravity = true;
	m_speed = GConfig::s_MoveEnemySpeed;

	// set col type
	m_colType = ECollisionType::MOVE;

	if (m_eType != SHOOTER)
	{
		// random movement x
		if (rand() % 2)
			m_movement.X = 1.0f;
		else
			m_movement.X = -1.0f;
	}

	// create shot sound
	m_pShot = new CSound("Audio/S_Shot.wav");
}
#pragma endregion