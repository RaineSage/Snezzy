#pragma region project include
#include "MoveEntity.h"
#include "Engine.h"
#include "ContentManagement.h"
#include "Physic.h"
#include "Game.h"
#include "Config.h"
#include "Renderer.h"
#pragma endregion

#pragma region public override function
// update every frame
void CMoveEntity::Update(float _deltaTime)
{
	if (m_position.X > RENDERER->GetCamera().X - CConfig::s_ScreenWidth * 0.6f
		&& m_position.X < RENDERER->GetCamera().X + CConfig::s_ScreenWidth * 0.6f
		&& m_position.Y > RENDERER->GetCamera().Y - CConfig::s_ScreenHeight * 0.6f
		&& m_position.Y < RENDERER->GetCamera().Y + CConfig::s_ScreenHeight * 0.6f)
	{
		// check collision movement
		CheckCollision(_deltaTime, false);

		// check collision gravity
		CheckCollision(_deltaTime, true);

		// update parent
		CTexturedEntity::Update(_deltaTime);
	}
}

// render every frame
void CMoveEntity::Render()
{
	CTexturedEntity::Render();
}
#pragma endregion

#pragma region private function
// fill collision list with all entities near
void CMoveEntity::SetCollisionList()
{
	// clear list with collision entities
	m_pColEntities.clear();

	// set rect for collision check around entity
	SRect rect = m_rect;
	rect.x -= m_rect.w;
	rect.y -= m_rect.h;
	rect.w = m_rect.w * 3.0f;
	rect.h = m_rect.h * 3.0f;

	// check all persistent entities
	for (CEntity* pEntity : CTM->GetPersistentEntities())
	{
		// if current entity collision type is dynamic or static
		if (((CTexturedEntity*)pEntity)->GetColType() == ECollisionType::DYNAMIC ||
			((CTexturedEntity*)pEntity)->GetColType() == ECollisionType::STATIC)
		{
			// if self check next entity
			if (pEntity == this)
				continue;

			// if rect of next frame collides with entity rect
			if (CPhysic::RectRectCollision(rect, ((CTexturedEntity*)pEntity)->GetRect()))
				m_pColEntities.push_back((CTexturedEntity*)pEntity);
		}
	}

	// check all persistent entities
	for (CEntity* pEntity : CTM->GetCollisionEntities())
	{
		if (pEntity->GetPosition().X < RENDERER->GetCamera().X - CConfig::s_ScreenWidth * 0.75f
			|| pEntity->GetPosition().X > RENDERER->GetCamera().X + CConfig::s_ScreenWidth * 0.75f
			|| pEntity->GetPosition().Y < RENDERER->GetCamera().Y - CConfig::s_ScreenHeight * 0.75f
			|| pEntity->GetPosition().Y > RENDERER->GetCamera().Y + CConfig::s_ScreenHeight * 0.75f)
			continue;

		// if current entity collision type is dynamic or static
		if (((CTexturedEntity*)pEntity)->GetColType() == ECollisionType::DYNAMIC ||
			((CTexturedEntity*)pEntity)->GetColType() == ECollisionType::STATIC)
		{
			// if self check next entity
			if (pEntity == this)
				continue;

			// if rect of next frame collides with entity rect
			if (CPhysic::RectRectCollision(rect, ((CTexturedEntity*)pEntity)->GetRect()))
				m_pColEntities.push_back((CTexturedEntity*)pEntity);
		}
	}
}

// check collision by movement and gravity
void CMoveEntity::CheckCollision(float _deltaTime, bool _useGravity)
{
	// if use gravity but gravity disabled return
	if (_useGravity && !m_gravity)
		return;

	// check player is moveable
	bool moveable = true;

	// calculate next position by movement
	SVector2 nextPos = m_position + m_movement * m_speed * _deltaTime;

	// if gravity used
	if (_useGravity)
	{
		// increase fall time
		m_fallTime += _deltaTime;

		// calculate next position by gravity and fall time
		nextPos = m_position;
		nextPos.Y += m_fallTime * _deltaTime * CConfig::s_Gravity * CConfig::s_PixelPerMeter;
	}

	// check all collision entities
	for (CEntity* pEntity : m_pColEntities)
	{
		if (moveable)
		{
			moveable = !(CPhysic::RectRectCollision(SRect(m_rect.w, m_rect.h, nextPos.X, nextPos.Y),
				SRect(((CTexturedEntity*)pEntity)->GetRect().w, ((CTexturedEntity*)pEntity)->GetRect().h,
				((CTexturedEntity*)pEntity)->GetPosition().X, ((CTexturedEntity*)pEntity)->GetPosition().Y)));
		}

		// if rect of next frame collides with entity rect
		if (_useGravity && m_pTag == "Player" && pEntity->GetTag() == "Enemy")
		{ 
			SRect myRect = SRect(m_rect.w, m_rect.h, nextPos.X, nextPos.Y);
			SRect otherRect = SRect(((CTexturedEntity*)pEntity)->GetRect().w, ((CTexturedEntity*)pEntity)->GetRect().h,
				((CTexturedEntity*)pEntity)->GetPosition().X, ((CTexturedEntity*)pEntity)->GetPosition().Y);

			if(CPhysic::RectRectCollision(myRect, otherRect))
				CTM->RemoveEntity(pEntity);
		}

		// if rect of next frame collides with entity rect (enemy into player while attack is true)
		if (m_attack && !_useGravity && m_pTag == "Player" && pEntity->GetTag() == "Enemy")
		{
			CTM->RemoveEntity(pEntity);
		}
	}

	if (m_pTag == "Enemy" && !_useGravity && !moveable)
	{
		m_movement.X *= -1;
		m_position.X += m_movement.X;
	}

	// if still moveable
	if (moveable)
	{
		if (m_eType == SHOOTER)
		{
			// set position to next position (remove the X)
			m_position.Y = nextPos.Y;
		}
		else
		{
			// set position to next position
			m_position = nextPos;
		}


		// if gravity used set grounded false
		if (_useGravity)
			m_isGrounded = false;
	}

	// if gravity used and not moveable
	if (_useGravity && !moveable)
	{
		// reset fall time
		m_fallTime = 0.0f;

		// set grounded true
		m_isGrounded = true;
	}
}
#pragma endregion