#pragma region project include
#include "Player.h"
#include "Input.h"
#include "Engine.h"
#include "Renderer.h"
#include "Config.h"
#include "Animation.h"
#include "Sound.h"
#pragma endregion

#pragma region public override function
GPlayer::GPlayer(SVector2 _pos, SVector2 _size, const char * _pFileName)
	: CMoveEntity(_pos, _size, _pFileName)
{
	// create idle animation
	m_pIDLEAnim = new CAnimation(SVector2(0.0f, 0.0f),
		SVector2(CConfig::s_PlayerSrcRectWidth, CConfig::s_PlayerSrcRectHeight), 1);

	// set animation time of idle
	m_pIDLEAnim->SetAnimationTime(2.0f);

	// create walk animation
	m_pWalkAnim = new CAnimation(SVector2(0.0f, 0.0f),
		SVector2(CConfig::s_PlayerSrcRectWidth, CConfig::s_PlayerSrcRectHeight), 10);

	// create attack animation
	m_pAttackAnim = new CAnimation(SVector2(0, CConfig::s_PlayerSrcRectHeight),
		SVector2(CConfig::s_PlayerSrcRectWidth, CConfig::s_PlayerSrcRectHeight), 1);;

	// set animation time of walk
	m_pWalkAnim->SetAnimationTime(1.5f);

	// create jump sound
	m_pJump = new CSound("Audio/Sounds/S_Jump.wav");
	m_pJump->SetVolume(50);
}
#include "Physic.h"

// update every frame
void GPlayer::Update(float _deltaTime)
{
	// if delta time zero return
	if (!_deltaTime)
		return;

	// reset movement
	m_movement = SVector2();

	// update CMoveEntity m_attack for collison check
	CMoveEntity::m_attack = m_attack;

	// if shift pressed attack
	if (CInput::GetKeyDown(SDL_SCANCODE_LSHIFT))
	{
		m_attack = true;
	}


	// attack time baby!
	if (m_attack)
	{
		m_pCurrentAnim = m_pAttackAnim;
		m_time += _deltaTime;
		
	
		if (m_time >= m_attackTime)
		{
			m_attack = false;
			m_time = 0.0f;
		}
	}

	// movement left
	else if (CInput::GetKey(SDL_SCANCODE_A))
	{
		// set movement, mirror and walk animation
		m_movement.X = -1.0f;
		m_mirror.X = true;
		m_pCurrentAnim = m_pWalkAnim;
	}

	// movement right
	else if (CInput::GetKey(SDL_SCANCODE_D))
	{
		// set movement, mirror and walk animation
 		m_movement.X = 1.0f;
		m_mirror.X = false;
		m_pCurrentAnim = m_pWalkAnim;
	}

	// no input movement
	else if (!m_attack)
	{
		// set idle animation
		m_pCurrentAnim = m_pIDLEAnim;
	}

	// update current animation
	m_pCurrentAnim->Update(_deltaTime);

	// set source rect by current animation
	m_srcRect = SRect(
		m_pCurrentAnim->GetSize().X,
		m_pCurrentAnim->GetSize().Y,
		m_pCurrentAnim->GetCurrentTexturePosition().X,
		m_pCurrentAnim->GetCurrentTexturePosition().Y
	);

	// if space pressed and grounded jump + attack false
	if (CInput::GetKey(SDL_SCANCODE_SPACE) && m_isGrounded && !m_attack)
	{
		m_fallTime = -1.0f;
		m_pJump->Play();
	}

	// update parent
	CMoveEntity::Update(_deltaTime);

	SRect rect = SRect(SVector2(1.0f, 1.0f), SVector2(
		m_position.X + m_rect.w + 1.0f,
		m_position.Y + m_rect.h * 0.5f
	));

	for (CEntity* pEntity : m_pColEntities)
	{
		CPhysic::RectRectCollision(rect, ((CTexturedEntity*)pEntity)->GetRect());

	}

	SRect rectP = SRect(SVector2(1.0f, 1.0f), SVector2(
		m_position.X + m_rect.w + 2.0f,
		m_position.Y + m_rect.h * 0.5f
	));

	for (CEntity* pEntity : m_pColEntities)
	{
		CPhysic::RectRectCollision(rectP, ((CTexturedEntity*)pEntity)->GetRect());

	}

	// set camera position
	RENDERER->SetCamera(m_position);
}

// render every frame
void GPlayer::Render()
{
	CMoveEntity::Render();
}
#pragma endregion