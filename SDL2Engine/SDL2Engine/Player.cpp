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
#pragma endregion

#pragma region public override function
// update every frame
void GPlayer::Update(float _deltaSeconds)
{
	// if key w is pressed down jump
	if (CInput::GetKeyDown(SDL_SCANCODE_SPACE) && m_grounded)
		SetFallTime(-GConfig::s_PlayerJump);

	// if key lshift is pressed
	if (!m_attack && CInput::GetKeyDown(SDL_SCANCODE_LSHIFT))
	{
		m_attack = true;
	}

	// if m_attack true
	if (m_attack)
	{
		m_movement.X = 0.0f;

		// set current animation to attack
		m_pCurrentAnim = m_pAttackAnim;
		m_time += _deltaSeconds;

		if (m_time >= 1.0f)
		{
			m_attack = false;
			m_time = 0.0f;
		}		
	}

	// if key a is pressed
	else if (CInput::GetKey(SDL_SCANCODE_A))
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
	else if (!m_attack)
	{
		m_movement.X = 0.0f;

		// set current animation to idle
		m_pCurrentAnim = m_pIdleAnim;
	}

	// update animation
	m_pCurrentAnim->Update(_deltaSeconds);

	// set source from animation
	m_srcRect = SRect(
		m_pCurrentAnim->GetSize().X,
		m_pCurrentAnim->GetSize().Y,
		m_pCurrentAnim->GetCurrentTexturePosition().X,
		m_pCurrentAnim->GetCurrentTexturePosition().Y
	);

	// destroy enemy when attack
	if (m_pColTarget && (((m_attack || m_fallTime > 0) && m_pColTarget->GetTag() == "Enemy") || (m_attack &&  m_pColTarget->GetTag() == "Bullet")))
		CTM->RemoveObject(m_pColTarget);	

	// if collision target valid and is enemy destroy all and back to menu
	else if (m_pColTarget && (m_pColTarget->GetTag() == "Enemy" || m_pColTarget->GetTag() == "Bullet"))
		ENGINE->ChangeScene(new GMenuScene());	

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
	// create idle animation
	m_pIdleAnim = new CAnimation(SVector2(0.0f, GConfig::s_PlayerSrcRectHeight),
		SVector2(GConfig::s_PlayerSrcRectWidth, GConfig::s_PlayerSrcRectHeight), 1);

	// create run animation
	m_pRunAnim = new CAnimation(SVector2(), SVector2(GConfig::s_PlayerSrcRectWidth, GConfig::s_PlayerSrcRectHeight), 10);
	m_pRunAnim->SetAnimationTime(0.5f);

	// create attack animation
	m_pAttackAnim = new CAnimation(SVector2(0.0f, GConfig::s_PlayerSrcRectHeight),
		SVector2(GConfig::s_PlayerSrcRectWidth, GConfig::s_PlayerSrcRectHeight), 1);

	// set idle to current animation
	m_pCurrentAnim = m_pIdleAnim;

	// create shot sound
	m_pShot = new CSound("Audio/S_Shot.wav");
}
#pragma endregion