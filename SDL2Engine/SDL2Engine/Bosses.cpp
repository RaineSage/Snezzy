#pragma region project include
#include "Bosses.h"
#include "Config.h"
#include "Bullet.h"
#include "ContentManagement.h"
#include "Engine.h"
#include "Sound.h"
#include "Timer.h"
#pragma endregion

#pragma region public override function
// update every frame
void GBosses::Update(float _deltaSeconds)
{
	// update parent
	CMoveEntity::Update(_deltaSeconds);

	// update cm health
	m_health = CMoveEntity::m_BossHealth;

	if (m_eType == CUTEULHU) 
	{
		m_jumpTime += _deltaSeconds;
		m_shotTime += _deltaSeconds;

		if (m_jumpTime >= m_jumpInter)
		{
			SetFallTime(-GConfig::s_PlayerJump * 0.5f);
			m_jumpTime = 0.0f;
		}

		if (m_shotTime >= m_shotInter)
		{
			// create bullet
			GBullet* pBullet = new GBullet(SVector2(), SVector2(8, 8), "Texture/Bullet/T_Bullet.png");

			// spawn left (-1) or right (1) from player
			int spawnSide = -1;

			// if mirror set spawn side left
			if (!m_mirror.X)
				spawnSide = 1;

			// set values
			pBullet->SetTag("Bullet");
			pBullet->SetPosition(SVector2(m_position.X + spawnSide * m_rect.w, m_position.Y + m_rect.h * 0.25f));
			pBullet->SetColType(ECollisionType::WALL);
			pBullet->SetSpeed(GConfig::s_BulletSpeed);
			pBullet->SetMovement(SVector2(spawnSide, 0.0f));

			// add bullet to content management
			CTM->AddPersistantObject(pBullet);

			// play shot sound
			//m_pShot->Play();

			// Reset shot time
			m_shotTime = 0.0f;
		}
	}

	if (m_pColTarget && CMoveEntity::m_Attack && m_pColTarget->GetTag() == "Player")
	{
		CMoveEntity::m_BossHealth--;
		
		if (m_pColTarget->GetPosition().X >= m_position.X)
		{
			AddPosition(SVector2(-55.0f, 0.0f));
		}
		else
		{
			AddPosition(SVector2(55.0f, 0.0f));
		}
	}
	else if (m_pColTarget && !CMoveEntity::m_Attack && m_pColTarget->GetTag() == "Player")
	{
		GTimer::RemoveTime(10);

		if (m_position.X >= m_pColTarget->GetPosition().X)
		{
			m_pColTarget->AddPosition(SVector2(-50.0f, 0.0f));
		}
		else
		{
			m_pColTarget->AddPosition(SVector2(50.0f, 0.0f));
		}
	}

	if (m_health <= 0)
	{
		CTM->RemoveObject(this);
	}
}

// render every frame
void GBosses::Render()
{
	// render parent
	CMoveEntity::Render();
}
#pragma endregion

#pragma region public function
// initialize move enemy
void GBosses::Init()
{
	// set tag
	m_pTag = "Boss";

	// set gravity and speed
	m_gravity = true;
	m_speed = GConfig::s_MoveEnemySpeed;

	// set col type
	m_colType = ECollisionType::MOVE;

	// random movement x
	if (rand() % 2)
		m_movement.X = 1.0f;
	else
		m_movement.X = -1.0f;

	// create shot sound
	m_pShot = new CSound("Audio/S_Shot.wav");
}
#pragma endregion