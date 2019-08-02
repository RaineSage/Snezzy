#pragma once

#include "Vector2.h"

#pragma region forward decleration
class SDL_Window;
class SDL_Surface;
class CRenderer;
class CTexture;
class CScene;
class CTime;
class CContentManagement;
class CTextureManagement;
class CMouse;
#pragma endregion

#pragma region macro value
#define ENGINE CEngine::Get()
#define RENDERER CEngine::Get()->GetRenderer()
#define CTM CEngine::Get()->GetCTM()
#define TTM CEngine::Get()->GetTTM()
#define SURFACE CEngine::Get()->GetSurface()
#pragma endregion

/// <summary>
/// core engine class
/// </summary>
class CEngine
{
public:
#pragma region constructor
	/// <summary>
	/// constructor
	/// </summary>
	CEngine() {}
#pragma endregion
	
#pragma region public function
	inline void Stop() { m_isRunning = false; }

	void SetMouseVisible(bool _visible);

	void SetMouseCenter(SVector2 _center);

	void SetMouseTexture(CTexture* _pTexture);

	/// <summary>
	/// initialize engine
	/// </summary>
	/// <returns>error code</returns>
	int Init();

	/// <summary>
	/// run engine
	/// </summary>
	void Run();

	/// <summary>
	/// clean engine
	/// </summary>
	void Clean();

	/// <summary>
	/// change active scene
	/// </summary>
	/// <param name="_pScene">new scene</param>
	void ChangeScene(CScene* _pScene);
#pragma endregion

#pragma region public inline function
	/// <summary>
	/// get engine
	/// </summary>
	/// <returns>engine reference</returns>
	inline static CEngine* Get()
	{
		// static local variable is used as global
		static CEngine* pEngine = new CEngine();

		// return engine reference
		return pEngine;
	}

	/// <summary>
	/// get renderer
	/// </summary>
	/// <returns>renderer reference</returns>
	CRenderer* GetRenderer() { return m_pRenderer; }

	/// <summary>
	/// get content management
	/// </summary>
	/// <returns>content management reference</returns>
	CContentManagement* GetCTM() { return m_pCTM; }

	/// <summary>
	/// get texture management
	/// </summary>
	/// <returns>texture management reference</returns>
	CTextureManagement* GetTTM() { return m_pTTM; }

	/// <summary>
	/// get sdl surface
	/// </summary>
	/// <returns>sdl surface from window</returns>
	SDL_Surface* GetSurface() { return m_pSurface; }
#pragma endregion

private:
#pragma region private primitive variable
	/// <summary>
	/// engine is running
	/// </summary>
	bool m_isRunning = false;
#pragma endregion

#pragma region private pointer
	/// <summary>
	/// sdl window reference
	/// </summary>
	SDL_Window* m_pWindow = nullptr;

	/// <summary>
	/// sdl surface reference
	/// </summary>
	SDL_Surface* m_pSurface = nullptr;

	/// <summary>
	/// renderer reference
	/// </summary>
	CRenderer* m_pRenderer = nullptr;

	/// <summary>
	/// current active scene reference
	/// </summary>
	CScene* m_pScene = nullptr;

	/// <summary>
	/// time class reference
	/// </summary>
	CTime* m_pTime = nullptr;

	/// <summary>
	/// content management reference
	/// </summary>
	CContentManagement* m_pCTM = nullptr;

	/// <summary>
	/// texture management reference
	/// </summary>
	CTextureManagement* m_pTTM = nullptr;

	CMouse* m_pMouse = nullptr;
#pragma endregion

#pragma region private function
	/// <summary>
	/// update every frame
	/// </summary>
	void Update();

	/// <summary>
	/// render every frame
	/// </summary>
	void Render();
#pragma endregion
};