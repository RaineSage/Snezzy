#pragma region project include
#include "Input.h"
#pragma endregion

// static varaible has to be initialized
#pragma region variable
bool CInput::s_keyIsDown[];
bool CInput::s_keyWasDown[];
#pragma endregion

#pragma region public function
// parse event from sdl to input class
void CInput::ParseEvent(SDL_Event _event)
{
	// if event key scancode is in range of this class variable
	if (_event.key.keysym.scancode < 256)
		// set key value of this frame depending on event type
		s_keyIsDown[_event.key.keysym.scancode] = _event.type == SDL_KEYDOWN;
}

// refresh state of key values
void CInput::RefreshState()
{
	// set last frame values to this frame
	for (int i = 0; i < 256; i++)
		s_keyWasDown[i] = s_keyIsDown[i];
}

// get key is pressed
bool CInput::GetKey(SDL_Scancode _key)
{
	return s_keyIsDown[_key];
}

// get key is pressed down this frame
bool CInput::GetKeyDown(SDL_Scancode _key)
{
	return s_keyIsDown[_key] && !s_keyWasDown[_key];
}

// get key is released this frame
bool CInput::GetKeyUp(SDL_Scancode _key)
{
	return !s_keyIsDown[_key] && s_keyWasDown[_key];
}
#pragma endregion