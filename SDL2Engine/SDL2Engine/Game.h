#pragma once

#pragma region project include
#include "Engine.h"
#include "ContentManagement.h"
#include "MenuScene.h"
#include "Font.h"
#include "Texture.h"
#pragma endregion

#pragma region value macro
#define GAME GGame::Get() 
#pragma endregion

/// <summary>
/// core game class
/// </summary>
class GGame
{
public:
#pragma region constructor
	/// <summary>
	/// constructor
	/// </summary>
	GGame() {}
#pragma endregion

	CFont* m_PFreescript = nullptr;

#pragma region public inline function
	/// <summary>
	/// get game reference
	/// </summary>
	/// <returns>game reference</returns>
	inline static GGame* Get()
	{
		// static local variable is used as global
		static GGame* pGame = new GGame();

		// return game reference
		return pGame;
	}
#pragma endregion

#pragma region public function
	/// <summary>
	/// initialize game
	/// </summary>
	void Init()
	{
		m_PFreescript = new CFont("Font/F_Freescript.TTF", 32);

		CTM->Clear();

		// change scene to new main scene
		ENGINE->ChangeScene(new GMenuScene());
	}

	void QuitGame()
	{
		ENGINE->Stop();
	}
#pragma endregion
};