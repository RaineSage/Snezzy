#pragma region project include
#include "MainScene.h"
#include "ContentManagement.h"
#include "Engine.h"
#include "Renderer.h"
#include "Game.h"
#include "MoveEntity.h"
#include "Input.h"
#include "World.h"
#include "Text.h"
#include "Music.h"
#pragma endregion

#pragma region public override function
// initialize scene
void GMainScene::Init()
{
	ENGINE->SetMouseVisible(false);

	// create world
	m_pWorld = new GWorld("Texture/Environment/World/T_WorldSide.png");
	m_pWorld->Init();

	// create fps text
	CText* pText = new CText("Hello World", GAME->m_PFreescript, SRect(128, 32, 10, 10), SColor(255, 255, 255));
	pText->SetInWorld(false);
	CTM->AddUIEntity(pText);

	// create music
	m_pAmbient = new CMusic("Audio/Music/S_Ambient.wav");
	m_pAmbient->Play(true);
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