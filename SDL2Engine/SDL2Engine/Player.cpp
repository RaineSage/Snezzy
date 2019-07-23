#pragma region project include
#include "Player.h"
#include "Input.h"
#include "Engine.h"
#include "ContentManagement.h"
#include "Renderer.h"
#include "Config.h"
#include "Physic.h"
#pragma endregion

#pragma region public override function
// update every frame
void GPlayer::Update(float _deltaTime)
{
	// if delta time zero return
	if (!_deltaTime)
		return;	

	// check player is moveable
	bool moveable = true;

	// reset movement
	m_movement = SVector2();

	// handle horizontal movement
	if (CInput::GetKey(SDL_SCANCODE_A))
		m_movement.X = -1.0f;
	else if (CInput::GetKey(SDL_SCANCODE_D))
		m_movement.X = 1.0f;

	// handle vertical movement
	else if (CInput::GetKey(SDL_SCANCODE_W))
		m_movement.Y = -1.0f;
	else if (CInput::GetKey(SDL_SCANCODE_S))
		m_movement.Y = 1.0f;

	if (!m_attack && CInput::GetKeyDown(SDL_SCANCODE_LSHIFT))
	{
		m_attack = true;
	}

	// handle attack animation
	if (m_attack)
	{
		m_time += _deltaTime;

		if ((m_time >= 0.5f && m_time <= 0.6f) || (m_time >= 1.5f && m_time <= 1.6f))
		{
			SetSrcRect(SRect(193, 175, 193, 0));
		}

		if (m_time >= 1.0f && m_time <= 1.1f)
		{
			SetSrcRect(SRect(193, 175, 193 * 2, 0));
		}

		if (m_time >= 2.0f && m_time <= 2.1f)
		{
			SetSrcRect(SRect(193, 175, 0, 0));
			m_time = 0.0f;
			m_attack = false;
		}
	}

	// calculate position next frame for collision check
	SVector2 nextPosition = m_position + m_movement * m_speed * _deltaTime;

	// check all persistent entities
	for (CEntity* pEntity : CTM->GetPersistentEntities())
	{
		// if current entity collision type is dynamic
		if (((CTexturedEntity*)pEntity)->GetColType() == ECollisionType::DYNAMIC)
		{
			// if player check next entity
			if (pEntity->GetTag() == "Player")
				continue;

			// if current entity is an enemy
			if (pEntity->GetTag() == "Enemy")
				// if rect of next frame collides with enemy rect
				if (m_attack && CPhysic::RectRectCollision(SRect(m_rect.w, m_rect.h, nextPosition.X, nextPosition.Y), ((CTexturedEntity*)pEntity)->GetRect()))
					// remove enemy
					CTM->RemoveEntity(pEntity);
		}

		// if current entity collision type is static
		else if (((CTexturedEntity*)pEntity)->GetColType() == ECollisionType::STATIC)
		{
			// if rect of next frame collides with entity rect
			if (CPhysic::RectRectCollision(SRect(m_rect.w, m_rect.h, nextPosition.X, nextPosition.Y), ((CTexturedEntity*)pEntity)->GetRect()))
			{
				// set not moveable and stop checking entities
				moveable = false;
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
			// if player check next entity
			if (pEntity->GetTag() == "Player")
				continue;

			// if current entity is an enemy
			if (pEntity->GetTag() == "Enemy")
				// if rect of next frame collides with enemy rect
				if (CPhysic::RectRectCollision(SRect(m_rect.w, m_rect.h, nextPosition.X, nextPosition.Y), ((CTexturedEntity*)pEntity)->GetRect()))
					// remove enemy
					CTM->RemoveEntity(pEntity);
		}

		// if current entity collision type is static
		else if (((CTexturedEntity*)pEntity)->GetColType() == ECollisionType::STATIC)
		{
			// if rect of next frame collides with entity rect
			if (CPhysic::RectRectCollision(SRect(m_rect.w, m_rect.h, nextPosition.X, nextPosition.Y), ((CTexturedEntity*)pEntity)->GetRect()))
			{
				// set not moveable and stop checking entities
				moveable = false;
				break;
			}
		}
	}

	// if still moveable set new position
	if (moveable)
		m_position = nextPosition;

	// update parent
	CTexturedEntity::Update(_deltaTime);

	// if space pressed
	if (m_jump && CInput::GetKeyDown(SDL_SCANCODE_SPACE))
	{
		// set fall time negative one
		m_fallTime = -1.0f;

		// calculate fall distance
		float fall = GRAVITY * PIXEL_PER_METER * -(m_fallTime * m_fallTime) * _deltaTime;

		// add fall distance to player y position
		m_position.Y += fall;

		// disable jump
		m_jump = false;
	}
	
	// if not jumping and still moveable
	else if (moveable)
	{
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
			// if current entity collision type is dynamic
			if (((CTexturedEntity*)pEntity)->GetColType() == ECollisionType::DYNAMIC)
			{
				// if player check next entity
				if (pEntity->GetTag() == "Player")
					continue;

				// if current entity is an enemy
				if (pEntity->GetTag() == "Enemy")
					// if rect of next frame collides with enemy rect
					if (m_attack && CPhysic::RectRectCollision(SRect(m_rect.w, m_rect.h, nextPosition.X, nextPosition.Y), ((CTexturedEntity*)pEntity)->GetRect()))
						// remove enemy
						CTM->RemoveEntity(pEntity);
			}

			// if current entity collision type is static
			else if (((CTexturedEntity*)pEntity)->GetColType() == ECollisionType::STATIC)
			{
				// if rect of next frame collides with entity rect
				if (CPhysic::RectRectCollision(SRect(m_rect.w, m_rect.h, nextPosition.X, nextPosition.Y), ((CTexturedEntity*)pEntity)->GetRect()))
				{
					// set not moveable
					moveable = false;

					// reset fall time and stop checking entities
					m_fallTime = 0.0f;
					m_jump = true;
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
				// if player check next entity
				if (pEntity->GetTag() == "Player")
					continue;

				// if current entity is an enemy
				if (pEntity->GetTag() == "Enemy")
					// if rect of next frame collides with enemy rect
					if (CPhysic::RectRectCollision(SRect(m_rect.w, m_rect.h, nextPosition.X, nextPosition.Y), ((CTexturedEntity*)pEntity)->GetRect()))
						// remove enemy
						CTM->RemoveEntity(pEntity);
			}

			// if current entity collision type is static
			else if (((CTexturedEntity*)pEntity)->GetColType() == ECollisionType::STATIC)
			{
				// if rect of next frame collides with entity rect
				if (CPhysic::RectRectCollision(SRect(m_rect.w, m_rect.h, nextPosition.X, nextPosition.Y), ((CTexturedEntity*)pEntity)->GetRect()))
				{
					// set not moveable
					moveable = false;

					// reset fall time and stop checking entities
					m_fallTime = 0.0f;
					m_jump = true;
					break;
				}
			}
		}

		// if still moveable set current position to next position
		if (moveable)
			m_position = nextPosition;
	}

	// update parent
	CTexturedEntity::Update(_deltaTime);

	// set camera position
	RENDERER->SetCamera(m_position);
}
#pragma endregion