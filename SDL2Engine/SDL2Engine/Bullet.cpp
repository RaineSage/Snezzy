#include "Bullet.h"
#include "Engine.h"
#include "ContentManagement.h"
#include "Physic.h"
#include "Config.h"

void GBullet::Update(float _deltaTime)
{
	// if delta time zero return
	if (!_deltaTime)
		return;

	// calculate position next frame for collision check
	SVector2 nextPosition = m_position + m_movement * m_force * _deltaTime;

	// check all persistent entities
	for (CEntity* pEntity : CTM->GetPersistentEntities())
	{
		// if current entity collision type is dynamic
		if (((CTexturedEntity*)pEntity)->GetColType() == ECollisionType::DYNAMIC)
		{
				// if rect of next frame collides with enemy rect
				if (CPhysic::RectRectCollision(SRect(m_rect.w, m_rect.h, nextPosition.X, nextPosition.Y), ((CTexturedEntity*)pEntity)->GetRect()))
					// remove entity
					CTM->RemoveEntity(this);
		}

		// if current entity collision type is static
		else if (((CTexturedEntity*)pEntity)->GetColType() == ECollisionType::STATIC)
		{
			// if rect of next frame collides with entity rect
			if (CPhysic::RectRectCollision(SRect(m_rect.w, m_rect.h, nextPosition.X, nextPosition.Y), ((CTexturedEntity*)pEntity)->GetRect()))
			{
				// remove entity
				CTM->RemoveEntity(this);
				break;
			}
		}
	}

	// check all scene entities
	for (CEntity* pEntity : CTM->GetSceneEntities())
	{
		// if current entity collision type is dynamic
		if (((CTexturedEntity*)pEntity)->GetColType() == ECollisionType::DYNAMIC)
		{
				// if rect of next frame collides with enemy rect
				if (CPhysic::RectRectCollision(SRect(m_rect.w, m_rect.h, nextPosition.X, nextPosition.Y), ((CTexturedEntity*)pEntity)->GetRect()))
					// remove entity
					CTM->RemoveEntity(this);
		}

		// if current entity collision type is static
		else if (((CTexturedEntity*)pEntity)->GetColType() == ECollisionType::STATIC)
		{
			// if rect of next frame collides with entity rect
			if (CPhysic::RectRectCollision(SRect(m_rect.w, m_rect.h, nextPosition.X, nextPosition.Y), ((CTexturedEntity*)pEntity)->GetRect()))
			{
				// remove entity
				CTM->RemoveEntity(this);
				break;
			}
		}
	}

	// if still moveable set new position
	m_position = nextPosition;

	// update parent
	CTexturedEntity::Update(_deltaTime);



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

	// check all persistent entities
	for (CEntity* pEntity : CTM->GetPersistentEntities())
	{
		// if current entity collision type is static
		if (((CTexturedEntity*)pEntity)->GetColType() == ECollisionType::STATIC)
		{
			// if rect of next frame collides with entity rect
			if (CPhysic::RectRectCollision(SRect(m_rect.w, m_rect.h, nextPosition.X, nextPosition.Y), ((CTexturedEntity*)pEntity)->GetRect()))
			{
				// reset fall time and stop checking entities and remove entity
				m_fallTime = 0.0f;
				CTM->RemoveEntity(this);
				break;
			}
		}
	}

	// check all scene entities
	for (CEntity* pEntity : CTM->GetSceneEntities())
	{
		// if current entity collision type is dynamic
		if (((CTexturedEntity*)pEntity)->GetColType() == ECollisionType::DYNAMIC)
		{

			if (CPhysic::RectRectCollision(SRect(m_rect.w, m_rect.h, nextPosition.X, nextPosition.Y), ((CTexturedEntity*)pEntity)->GetRect()))
				// remove entity
				CTM->RemoveEntity(this);
		}

		// if current entity collision type is static
		else if (((CTexturedEntity*)pEntity)->GetColType() == ECollisionType::STATIC)
		{
			// if rect of next frame collides with entity rect
			if (CPhysic::RectRectCollision(SRect(m_rect.w, m_rect.h, nextPosition.X, nextPosition.Y), ((CTexturedEntity*)pEntity)->GetRect()))
			{
				// reset fall time and stop checking entities and remove entity
				m_fallTime = 0.0f;
				CTM->RemoveEntity(this);
				break;
			}
		}
	}

	// if still moveable set current position to next position
	m_position = nextPosition;

	// update parent
	CTexturedEntity::Update(_deltaTime);
}
