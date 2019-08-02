#pragma region project include
#include "MenuScene.h"
#include "Engine.h"
#include "Game.h"
#include "ContentManagement.h"
#include "Text.h"
#include "MainScene.h"
#include "Input.h"
#pragma endregion

#pragma region public function
// load scene
void GMenuScene::Load()
{
	// initialize mouse
	ENGINE->SetMouseCenter(0.5f, 0.5f);
	ENGINE->SetMouseVisible(true);

	// start game button
	m_pStart = new CText("Start Game", GAME->m_PArial, SRect(100, 50, 500, 300), SColor(255, 255, 255, 255));
	CTM->AddUIObject(m_pStart);
}

// clean scene
void GMenuScene::Clean()
{
	// remove texts
	CTM->RemoveObject(m_pStart);
}

// update every frame
void GMenuScene::Update(float _deltaSeconds)
{

	// if mouse button left pressed and mouse position in start button load main scene
	if (CInput::GetMouseButtonDown(0) &&
		CInput::GetMousePosition().X >= m_pStart->GetRect().x &&
		CInput::GetMousePosition().X <= m_pStart->GetRect().x + m_pStart->GetRect().w &&
		CInput::GetMousePosition().Y >= m_pStart->GetRect().y &&
		CInput::GetMousePosition().Y <= m_pStart->GetRect().y + m_pStart->GetRect().h)
	{
		ENGINE->ChangeScene(new GMainScene());
	}
}

// render every frame
void GMenuScene::Render()
{
	
}
#pragma endregion