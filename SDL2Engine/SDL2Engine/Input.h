#pragma once

#pragma region SDL include
#include <SDL.h>
#pragma endregion

/// <summary>
/// input handle static class
/// </summary>
class CInput
{
public:
#pragma region public function
	/// <summary>
	/// parse event from sdl to input class
	/// </summary>
	/// <param name="_event">sdl event</param>
	static void ParseEvent(SDL_Event _event);

	/// <summary>
	/// refresh state of key values
	/// </summary>
	static void RefreshState();

	/// <summary>
	/// get key is pressed
	/// </summary>
	/// <param name="_key">key</param>
	/// <returns>is pressed</returns>
	static bool GetKey(SDL_Scancode _key);

	/// <summary>
	/// get key is pressed down this frame
	/// </summary>
	/// <param name="_key">key</param>
	/// <returns>pressed down this frame</returns>
	static bool GetKeyDown(SDL_Scancode _key);

	/// <summary>
	/// get key is released this frame
	/// </summary>
	/// <param name="_key">key</param>
	/// <returns>released this frame</returns>
	static bool GetKeyUp(SDL_Scancode _key);
#pragma endregion

private:
#pragma region private primitive variable
	/// <summary>
	/// key value informations for this frame
	/// </summary>
	static bool s_keyIsDown[256];

	/// <summary>
	/// key value informations of last frame
	/// </summary>
	static bool s_keyWasDown[256];
#pragma endregion
};