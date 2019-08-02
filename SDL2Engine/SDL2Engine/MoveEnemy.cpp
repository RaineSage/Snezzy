#pragma region project include
#include "MoveEnemy.h"
#include "Config.h"
#include "Bullet.h"
#include "TextureManagement.h"
#include "Texture.h"
#include "Engine.h"
#include "ContentManagement.h"
#pragma endregion

#pragma region public override function
// update every frame
void GMoveEnemy::Update(float _deltaTime)
{
	CMoveEntity::Update(_deltaTime);

	CMoveEntity::m_eType = m_eType;

	if (m_eType == JUMPER && m_isGrounded)
	{
		m_time += _deltaTime;

		if (m_time >= m_jumpInter)
		{
			m_fallTime = -0.5f;
			m_time = 0.0f;
		}
	}

	if (m_eType == SHOOTER) 
	{
		//m_time += _deltaTime;
		//
		//if (m_time >= m_shotInter)
		//{
		//	// create bullet
		//	GBullet* pBullet = new GBullet(
		//		SVector2(m_position.X - (CConfig::s_BlockWidth + 10.0f), m_position.Y - 10.0f),
		//		SVector2(CConfig::s_BlockWidth, CConfig::s_BlockHeight),
		//		nullptr
		//	);
		//	
		//	CTexture* pTexture = TTM->GetTexture("Bullet");
		//	
		//	if (!pTexture)
		//	{
		//		TTM->AddTexture("Bullet", new CTexture("Texture/Bullet/T_Bullet.bmp"));
		//		pTexture = TTM->GetTexture("Bullet");
		//	}
		//	
		//	pBullet->SetTexture(pTexture);
		//	
		//	// set player tag, collision type to dynamic and speed
		//	pBullet->SetTag("Bullet");
		//	pBullet->SetColType(ECollisionType::DYNAMIC);
		//	pBullet->ActiveGravity();
		//	
		//	// add player to ctm
		//	CTM->AddPersistentEntity(pBullet);
		//	
		//	m_time = 0.0f;
		//}
	}
}

// render every frame
void GMoveEnemy::Render()
{
	CMoveEntity::Render();
}
#pragma endregion

#pragma region public function
// initialize move enemy
void GMoveEnemy::Init()
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