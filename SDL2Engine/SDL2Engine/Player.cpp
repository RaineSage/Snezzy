#pragma region project include
#include "Player.h"
#include "Input.h"
#include "Engine.h"
#include "Renderer.h"
#include "ContentManagement.h"
#include "Config.h"
#include "MenuScene.h"
#include "MainScene.h"
#include "Animation.h"
#include "Sound.h"
#include "Timer.h"
#pragma endregion

#pragma region public override function
// update every frame
void GPlayer::Update(float _deltaSeconds)
{
	bool attack = CMoveEntity::m_Attack;

	// if key w is pressed down jump
	if (CInput::GetKeyDown(SDL_SCANCODE_SPACE) && m_grounded)
		SetFallTime(-GConfig::s_PlayerJump);

	// if key lshift is pressed
	if (!attack && CInput::GetKeyDown(SDL_SCANCODE_LSHIFT))
		attack = true;


	// if key a is pressed
	if (CInput::GetKey(SDL_SCANCODE_A))
	{
		// set negative x movement and mirror horizontal
		m_movement.X = -10.0f;
		m_mirror.X = 1.0f;

		// set current animation to run 
		m_pCurrentAnim = m_pRunAnim;
	}

	// if key d is pressed
	else if (CInput::GetKey(SDL_SCANCODE_D))
	{
		// set positive x movement and mirror none
		m_movement.X = 10.0f;
		m_mirror.X = 0.0f;

		// set current animation to run 
		m_pCurrentAnim = m_pRunAnim;
	}
	// else no x movement
	else if (!attack)
	{
		m_movement.X = 0.0f;

		// set current animation to idle
		m_pCurrentAnim = m_pIdleAnim;
	}

	// if m_attack true
	if (attack)
	{
		// set current animation to attack
		m_pCurrentAnim = m_pAttackAnim;

		m_time += _deltaSeconds;

		if (m_time >= m_attackTime)
		{
			m_time = 0.0f;
			attack = false;
		}
	}

	CMoveEntity::m_Attack = attack;

	// update animation
	m_pCurrentAnim->Update(_deltaSeconds);

	// set source from animation
	m_srcRect = SRect(
		m_pCurrentAnim->GetSize().X,
		m_pCurrentAnim->GetSize().Y,
		m_pCurrentAnim->GetCurrentTexturePosition().X,
		m_pCurrentAnim->GetCurrentTexturePosition().Y
	);

	// destroy enemy when attack else get damage
	if (m_pColTarget && attack && ((m_pColTarget->GetTag() == "Enemy") || (m_pColTarget->GetTag() == "Bullet")))
	{
		CTM->RemoveObject(m_pColTarget);
	}
	else if (m_pColTarget && !attack && !m_gotDamage && ((m_pColTarget->GetTag() == "Enemy") || (m_pColTarget->GetTag() == "Bullet")))
	{
		m_gotDamage = true;
		GTimer::RemoveTime(10);
	}

	if (GTimer::GetTime() <= 0.0f)
	{
		ENGINE->ChangeScene(new GMenuScene());
	}

	// how long player can't take damage
	if (m_gotDamage)
	{
		m_time += _deltaSeconds;
	
		if (m_time >= m_dammageTime)
		{
			m_time = 0.0f;
			m_gotDamage = false;
		}
	}

	// update parent
	CMoveEntity::Update(_deltaSeconds);

	// parent camera to player
	RENDERER->SetCamera(m_position);
}

// render every frame
void GPlayer::Render()
{
	CMoveEntity::Render();
}
#pragma endregion

#pragma region public function
// initialize player
void GPlayer::Init()
{
	// set col type
	m_colType = ECollisionType::MOVE;

	// create idle animation
	m_pIdleAnim = new CAnimation(SVector2(0.0f, GConfig::s_PlayerSrcRectHeight),
		SVector2(GConfig::s_PlayerSrcRectWidth, GConfig::s_PlayerSrcRectHeight), 1);

	// create run animation
	m_pRunAnim = new CAnimation(SVector2(), SVector2(GConfig::s_PlayerSrcRectWidth, GConfig::s_PlayerSrcRectHeight), 10);
	m_pRunAnim->SetAnimationTime(0.5f);

	// create attack animation
	m_pAttackAnim = new CAnimation(SVector2(GConfig::s_PlayerSrcRectWidth, GConfig::s_PlayerSrcRectHeight),
		SVector2(GConfig::s_PlayerSrcRectWidth, GConfig::s_PlayerSrcRectHeight), 1);

	// set idle to current animation
	m_pCurrentAnim = m_pIdleAnim;

	// create shot sound
	m_pShot = new CSound("Audio/S_Shot.wav");
}
#pragma endregion