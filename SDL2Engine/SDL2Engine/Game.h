#pragma once

#pragma region project include
#include "Engine.h"
#include "MainScene.h"
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
		// change scene to new main scene
		ENGINE->ChangeScene(new GMainScene());
	}
#pragma endregion
};