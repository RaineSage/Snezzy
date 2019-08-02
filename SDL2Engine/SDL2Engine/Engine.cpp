#pragma region system include
#include <stdio.h>
#include <iostream>
#pragma endregion

#pragma region SDL2 include
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#pragma endregion

#pragma region project include
#include "Engine.h"
#include "Renderer.h"
#include "Scene.h"
#include "Input.h"
#include "Time.h"
#include "ContentManagement.h"
#include "TextureManagement.h"
#include "Config.h"
#include "Mouse.h"
#pragma endregion

#pragma region using
using namespace std;
#pragma endregion

#pragma region public function
void CEngine::SetMouseVisible(bool _visible)
{
	m_pMouse->SetVisible(_visible);
}
void CEngine::SetMouseCenter(SVector2 _center)
{
	m_pMouse->SetCenter(_center);
}
void CEngine::SetMouseTexture(CTexture * _pTexture)
{
	m_pMouse->SetTexture(_pTexture);
}
// initialize engine
int CEngine::Init()
{
	CConfig::LoadConfig("Files/Config.ini");

	// initialize sdl video
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		// show error
		printf("SDL video not initialized! SDL Error: %s\n", SDL_GetError());
		return 101;
	}

	// initialize sdl ttf
	if (TTF_Init() < 0)
	{
		// show error
		printf("SDL font not initialized! SDL Error: %s\n", SDL_GetError());
		return 102;
	}

	// initialize sdl audio
	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096 < 0))
	{
		// show error
		printf("SDL audio not initialized! SDL Error: %s\n", SDL_GetError());
		return 103;
	}

	// create sdl window
	m_pWindow = SDL_CreateWindow(
		"SDL2Engine",			// name of window
		SDL_WINDOWPOS_CENTERED,	// position x
		SDL_WINDOWPOS_CENTERED,	// position y
		CConfig::s_ScreenWidth,	// width
		CConfig::s_ScreenHeight,// height
		SDL_WINDOW_SHOWN);		// flags (F12)

	// if window nullptr
	if (!m_pWindow)
	{
		// show error
		printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
		return 104;
	}

	// get surface from current window
	m_pSurface = SDL_GetWindowSurface(m_pWindow);

	// create renderer
	m_pRenderer = new CRenderer(m_pWindow);

	// if renderer nullptr
	if (!m_pRenderer)
	{
		// show error
		printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
		return 105;
	}

	// create time
	m_pTime = new CTime();

	// if time nullptr
	if (!m_pTime)
	{
		// show error
		printf("Time not intialized!");
		return 201;
	}

	// create content management
	m_pCTM = new CContentManagement();

	// if ctm nullptr
	if (!m_pCTM)
	{
		// show error
		printf("CTM not intialized!");
		return 202;
	}

	// create texture management
	m_pTTM = new CTextureManagement();

	// if ttm nullptr
	if (!m_pTTM)
	{
		// show error
		printf("TTM not intialized!");
		return 203;
	}

	m_pMouse = new CMouse(SVector2(32, 32));
	SDL_ShowCursor(SDL_DISABLE);

	if (!m_pCTM)
	{
		// show error
		printf("Mouse not intialized!");
		return 204;
	}

	m_pMouse->SetInWorld(false);

	// fill rect of surface with color
	SDL_FillRect(m_pSurface, nullptr, SDL_MapRGB(m_pSurface->format, 0xFF, 0x22, 0xFF));

	// update edited surface
	SDL_UpdateWindowSurface(m_pWindow);

	// set engine running true
	m_isRunning = true;

	// initialize successfully
	return 0;
}

// run engine
void CEngine::Run()
{
	// while engine is running
	while (m_isRunning)
	{
		// update every frame
		Update();

		// render every frame
		Render();
	}
}

// clean engine
void CEngine::Clean()
{
	// change scene to null scene
	ChangeScene(nullptr);

	// delete content management
	delete m_pCTM;

	// delete texture management
	delete m_pTTM;

	// close audio
	Mix_CloseAudio();

	// destroy used window
	SDL_DestroyWindow(m_pWindow);

	// shut down sdl 2
	SDL_Quit();
}

// change active scene
void CEngine::ChangeScene(CScene * _pScene)
{
	// if current active scene valid
	if (m_pScene)
	{
		// clean and delete current scene
		m_pScene->Clean();
		delete m_pScene;
	}

	// set current scene
	m_pScene = _pScene;

	// if current new scene valid
	if (m_pScene)
		// initialize scene
		m_pScene->Init();
}
#pragma endregion

#pragma region private function
// update every frame
void CEngine::Update()
{
	// update time
	m_pTime->Update();

	// log fps and delta time
	cout << "FPS: " << m_pTime->GetFPS() << ", DeltaTime: " << m_pTime->GetDeltaTime() << endl;

	// refresh input state
	CInput::RefreshState();

	// sdl event
	SDL_Event e;

	// get every sdl event
	while (SDL_PollEvent(&e))
	{
		// if event quit stop engine
		if (e.type == SDL_EventType::SDL_QUIT)
			m_isRunning = false;

		// if key pressed or released parse event to input class
		else if (e.type == SDL_EventType::SDL_KEYDOWN || e.type == SDL_EventType::SDL_KEYUP)
			CInput::ParseEvent(e);

		else if (e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP)
			CInput::ParseMouseEvent(e);
	}

	// update ctm
	CTM->Update(m_pTime->GetDeltaTime());

	m_pMouse->Update(m_pTime->GetDeltaTime());

	// update scene
	if (m_pScene)
		m_pScene->Update(m_pTime->GetDeltaTime());
}

// render every frame
void CEngine::Render()
{
	// clear screen
	m_pRenderer->ClearScreen();

	// render scene
	if (m_pScene)
		m_pScene->Render();

	// render ctm
	CTM->Render();

	// render mouse
	m_pMouse->Render();

	// present rendered image
	m_pRenderer->Present();
}
#pragma endregion