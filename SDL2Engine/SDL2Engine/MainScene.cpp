#pragma region project include
#include "MainScene.h"
#include "ContentManagement.h"
#include "Engine.h"
#include "Renderer.h"
#include "TexturedEntity.h"
#include "Input.h"
#include "World.h"
#pragma endregion

#pragma region public override function
// initialize scene
void GMainScene::Init()
{
	// create world
	m_pWorld = new GWorld("Texture/Environment/World/T_WorldSide.png");
	m_pWorld->Init();

	// // create enemy, set tag, collision type dynamic and add to ctm
	// m_pEnemy = new CTexturedEntity(SVector2(720.0f - 64.0f, 500.0f), SVector2(64.0, 64.0f), "Texture/Character/Enemy/T_Enemy.bmp");
	// m_pEnemy->SetTag("Enemy");
	// m_pEnemy->SetColType(ECollisionType::DYNAMIC);
	// CTM->AddPersistentEntity(m_pEnemy);
	// 
	// // create enemy, render on screen and add to ctm
	// m_pEnemy = new CTexturedEntity(SVector2(0.0f, 0.0f), SVector2(64.0, 64.0f), "Texture/Character/Enemy/T_Enemy.bmp");
	// m_pEnemy->SetInWorld(false);
	// CTM->AddPersistentEntity(m_pEnemy);
}

// update every frame
void GMainScene::Update(float _deltaTime)
{
	
}

// render every frame
void GMainScene::Render()
{

}

// clean scene
void GMainScene::Clean()
{
	
}
#pragma endregion