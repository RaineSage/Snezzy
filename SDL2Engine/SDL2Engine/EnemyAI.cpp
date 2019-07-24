#include "EnemyAI.h"
#include "Engine.h"
#include "ContentManagement.h"
#include "Physic.h"
#include "Config.h"
#include "Bullet.h"

void GEnemyAI::Update(float _deltaTime)
{
	// if delta time zero return
	if (!_deltaTime)
		return;

	// check enemy is moveable
	bool moveable = true;

	if (m_type == SHOOTER) 
	{
		m_time += _deltaTime;

		if (m_time >= m_shotInter) 
		{
			// create bullet
			GBullet* pBullet = new GBullet(
				SVector2(m_position.X - (BLOCK_WIDTH + 8.0f), m_position.Y),
				SVector2(16.0f, 16.0f),
				"Texture/Character/Player/T_Attack.bmp"
			);

			// set collision type to dynamic
			pBullet->SetColType(ECollisionType::DYNAMIC);
			pBullet->SetTag("Bullet");

			// optional: force
			pBullet->AddForce(m_force);

			// add bullet to ctm
			CTM->AddPersistentEntity(pBullet);

			m_time = 0.0f;
		}
	}
	else
	{
		// calculate position next frame for collision check
		SVector2 nextPosition = m_position + m_movement * m_speed * _deltaTime;

		// check all persistent entities
		for (CEntity* pEntity : CTM->GetPersistentEntities())
		{
			// if current entity collision type is dynamic
			if (((CTexturedEntity*)pEntity)->GetColType() == ECollisionType::DYNAMIC)
			{
				// if current entity is an enemy
				if (pEntity->GetTag() == "Enemy")
					// if rect of next frame collides with enemy rect
					if (CPhysic::RectRectCollisionX(SRect(m_rect.w, m_rect.h, nextPosition.X, nextPosition.Y), ((CTexturedEntity*)pEntity)->GetRect()))
						// change walk direction
						m_movement.X = -(m_movement.X);

				// if current entity is an player
				if(pEntity->GetTag() == "Player")
					if (CPhysic::RectRectCollision(SRect(m_rect.w, m_rect.h, nextPosition.X, nextPosition.Y), ((CTexturedEntity*)pEntity)->GetPosition()))
					{
						// set not moveable and stop checking entities
						moveable = false;
						break;
					}						
			}

			// if current entity collision type is static
			else if (((CTexturedEntity*)pEntity)->GetColType() == ECollisionType::STATIC)
			{
				// if rect of next frame collides with entity rect
				if (CPhysic::RectRectCollisionX(SRect(m_rect.w, m_rect.h, nextPosition.X, nextPosition.Y), ((CTexturedEntity*)pEntity)->GetRect()))
				{
					// change walk direction
					m_movement.X = -(m_movement.X);
				}
			}
		}

		// check all scene entities
		for (CEntity* pEntity : CTM->GetSceneEntities())
		{
			// if current entity collision type is dynamic
			if (((CTexturedEntity*)pEntity)->GetColType() == ECollisionType::DYNAMIC)
			{
				// if current entity is an enemy
				if (pEntity->GetTag() == "Enemy")
					// if rect of next frame collides with enemy rect
					if (CPhysic::RectRectCollisionX(SRect(m_rect.w, m_rect.h, nextPosition.X, nextPosition.Y), ((CTexturedEntity*)pEntity)->GetRect()))
						// change walk direction
						m_movement.X = -(m_movement.X);

				// if current entity is an player
				if (pEntity->GetTag() == "Player")
					if (CPhysic::RectRectCollision(SRect(m_rect.w, m_rect.h, nextPosition.X, nextPosition.Y), ((CTexturedEntity*)pEntity)->GetPosition()))
					{
						// set not moveable and stop checking entities
						moveable = false;
						break;
					}
			}

			// if current entity collision type is static
			else if (((CTexturedEntity*)pEntity)->GetColType() == ECollisionType::STATIC)
			{
				// if rect of next frame collides with entity rect
				if (CPhysic::RectRectCollisionX(SRect(m_rect.w, m_rect.h, nextPosition.X, nextPosition.Y), ((CTexturedEntity*)pEntity)->GetRect()))
				{
					// change walk direction
					m_movement.X = -(m_movement.X);
				}
			}
		}

		// if still moveable set new position
		if(moveable)
			m_position = nextPosition;

		// update parent
		CTexturedEntity::Update(_deltaTime);

		// if enemy type JUMPER
		if (m_type == JUMPER)
		{
			m_time += _deltaTime;

			if (m_time >= m_jumpTime)
			{
				// set fall time negative one
				m_fallTime = -0.5f;

				// calculate fall distance
				float fall = GRAVITY * PIXEL_PER_METER * -(m_fallTime * m_fallTime) * _deltaTime;

				// add fall distance to player y position
				m_position.Y += fall;

				// set m_time back to 0
				m_time = 0.0f;
			}
		}

		// increase fall time
		m_fallTime += _deltaTime;

		// calculate fall distance
		float fall = GRAVITY * PIXEL_PER_METER * m_fallTime * m_fallTime * _deltaTime;

		// if fall time negative set fall distance negative
		if (m_fallTime < 0.0f)
			fall *= -1.0f;

		// set next position to current position and add fall distance
		nextPosition = m_position;
		nextPosition.Y += fall;

		// check all scene entities
		for (CEntity* pEntity : CTM->GetSceneEntities())
		{
			// if current entity collision type is static
			if (((CTexturedEntity*)pEntity)->GetColType() == ECollisionType::STATIC)
			{
				// if rect of next frame collides with entity rect
				if (CPhysic::RectRectCollision(SRect(m_rect.w, m_rect.h, nextPosition.X, nextPosition.Y), ((CTexturedEntity*)pEntity)->GetRect()))
				{
					// reset fall time and stop checking entities
					m_fallTime = 0.0f;
					break;
				}
			}
		}

		// if still moveable set current position to next position
		m_position = nextPosition;
	}

	// update parent
	CTexturedEntity::Update(_deltaTime);
}

