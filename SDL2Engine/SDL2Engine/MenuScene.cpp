#pragma region project include
#include "MenuScene.h"
#include "MainScene.h"
#include "Engine.h"
#include "ContentManagement.h"
#include "Texture.h"
#include "Text.h"
#include "Game.h"
#include "Input.h"
#include "Physic.h"
#pragma endregion

#pragma region public function
// initialize scene
void GMenuScene::Init()
{
	CTexture* pMouse = new CTexture("Texture/Mouse/T_Mouse.bmp");
	ENGINE->SetMouseTexture(pMouse);
	ENGINE->SetMouseCenter(SVector2(0.5f, 0.5f));
	ENGINE->SetMouseVisible(true);

	m_pStartButton = new CText("Start Game", GAME->m_PFreescript, SRect(200, 100, 550, 300), SColor(0, 255, 0));
	m_pStartButton->SetInWorld(false);
	m_pQuitButton = new CText("Quit Game", GAME->m_PFreescript, SRect(200, 100, 550, 450), SColor(255, 0, 0));
	m_pQuitButton->SetInWorld(false);

	CTM->AddUIEntity(m_pStartButton);
	CTM->AddUIEntity(m_pQuitButton);
}

// clean scene
void GMenuScene::Clean()
{
	CTM->RemoveEntity(m_pStartButton);
	CTM->RemoveEntity(m_pQuitButton);
}

// update every frame
void GMenuScene::Update(float _deltaSeconds)
{
	if (CInput::GetMouseButtonDown(0))
	{
		if (CPhysic::RectRectCollision(m_pStartButton->GetRect(), SRect(1, 1, CInput::GetMousePosition().X, CInput::GetMousePosition().Y)))
		{
			CTM->Clear();
			ENGINE->ChangeScene(new GMainScene());
		}
		else if (CPhysic::RectRectCollision(m_pQuitButton->GetRect(), SRect(1, 1, CInput::GetMousePosition().X, CInput::GetMousePosition().Y)))
		{
			GAME->QuitGame();
		}
	}
}

// render every frame
void GMenuScene::Render()
{
	
}
#pragma endregion