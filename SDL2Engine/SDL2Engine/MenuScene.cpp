#pragma region project include
#include "MenuScene.h"
#include "Engine.h"
#include "Game.h"
#include "ContentManagement.h"
#include "Texture.h"
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

	// Load UI Texture
	CTexturedEntity* m_UI = new CTexturedEntity(SVector2(0.0f, 0.0f), SVector2(0.0f, 0.0f), "Texture/UI/T_UIMenu.jpg");
	CTM->AddSceneObject(m_UI);

	// Add start button
	m_pStartButton = new CTexturedEntity(SVector2(290.0f, 310.0f), SVector2(340.0f, 120.0f), "T_ButtonTest.png");
	m_pStartButton->SetInWorld(false);
	CTM->AddUIObject(m_pStartButton);

	// Add new game button
	//m_pNGButton = new CTexturedEntity(SVector2(650.0f, 310.0f), SVector2(340.0f, 120.0f), "T_ButtonTest.png");
	//m_pNGButton->SetInWorld(false);
	//CTM->AddUIObject(m_pNGButton);

	// Add Exit button
	//m_pExitButton = new CTexturedEntity(SVector2(470.0f, 120.0f), SVector2(340.0f, 145.0f), "T_ButtonTest.png");
	//m_pExitButton->SetInWorld(false);
	//CTM->AddUIObject(m_pExitButton);
}

// clean scene
void GMenuScene::Clean()
{
	// remove texts
	CTM->RemoveObject(m_pStartButton);
	//CTM->RemoveObject(m_pNGButton);
	//CTM->RemoveObject(m_pExitButton);
}

// update every frame
void GMenuScene::Update(float _deltaSeconds)
{

	// if mouse button left pressed and mouse position in start button load main scene
	if (CInput::GetMouseButtonDown(0) &&
		CInput::GetMousePosition().X >= m_pStartButton->GetRect().x &&
		CInput::GetMousePosition().X <= m_pStartButton->GetRect().x + m_pStartButton->GetRect().w &&
		CInput::GetMousePosition().Y >= m_pStartButton->GetRect().y &&
		CInput::GetMousePosition().Y <= m_pStartButton->GetRect().y + m_pStartButton->GetRect().h)
	{
		ENGINE->ChangeScene(new GMainScene());
	}

	// if mouse button is left pressed and mouse position in New button, load new game
	//if (CInput::GetMouseButtonDown(0) &&
	//	CInput::GetMousePosition().X >= m_pNGButton->GetRect().x &&
	//	CInput::GetMousePosition().X <= m_pNGButton->GetRect().x + m_pNGButton->GetRect().w &&
	//	CInput::GetMousePosition().Y >= m_pNGButton->GetRect().y &&
	//	CInput::GetMousePosition().Y <= m_pNGButton->GetRect().y + m_pNGButton->GetRect().h)
	//{
	//	ENGINE->ChangeScene(new GMainScene());
	//}

	// if mouse button left pressed and mouse position in exit button, close game
	//if (CInput::GetMouseButtonDown(0) &&
	//	CInput::GetMousePosition().X >= m_pExitButton->GetRect().x &&
	//	CInput::GetMousePosition().X <= m_pExitButton->GetRect().x + m_pExitButton->GetRect().w &&
	//	CInput::GetMousePosition().Y >= m_pExitButton->GetRect().y &&
	//	CInput::GetMousePosition().Y <= m_pExitButton->GetRect().y + m_pExitButton->GetRect().h)
	//{
	//	ENGINE->Stop();
	//}
}

// render every frame
void GMenuScene::Render()
{
	
}
#pragma endregion