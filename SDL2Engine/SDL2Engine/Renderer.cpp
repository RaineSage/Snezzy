#pragma region sdl include
#include <SDL.h>
#pragma endregion

#pragma region project include
#include "Renderer.h"
#include "Rect.h"
#include "Texture.h"
#include "Macro.h"
#pragma endregion

#pragma region constructor
// constructor
CRenderer::CRenderer(SDL_Window * _pWindow)
{
	// initialize renderer nullptr
	m_pRenderer = nullptr;

	// create renderer
	m_pRenderer = SDL_CreateRenderer(
		_pWindow,						// window reference
		-1,								// index
		SDL_RENDERER_ACCELERATED |		// flags
		SDL_RENDERER_PRESENTVSYNC
	);
}
#pragma endregion

#pragma region destructor
// destructor
CRenderer::~CRenderer()
{
	// if renderer valid destroy renderer
	if (m_pRenderer)
		SDL_DestroyRenderer(m_pRenderer);
}
#pragma endregion

#pragma region public function
// clear screen
void CRenderer::ClearScreen()
{
	SDL_RenderClear(m_pRenderer);
}

// render texture
void CRenderer::RenderTexture(CTexture* _pTexture, SRect* _dstRect, SRect* _srcRect, 
	float _angle, SVector2 _mirror, bool _inWorld)
{
	// get rect
	SRect* pDstRect = new SRect();

	// if given dst rect valid set values of temp dest rect
	if(_dstRect)
		*pDstRect = SRect(SVector2(_dstRect->w, _dstRect->h),
		SVector2(_dstRect->x, _dstRect->y));

	// if texture not valid return
	if (!_pTexture)
		return;

	// if destination rect has no width or height set to nullptr
	if (pDstRect && (pDstRect->w == 0.0f || pDstRect->h == 0.0f))
		pDstRect = nullptr;

	// if source rect has no width or height set to nullptr
	if (_srcRect && (_srcRect->w == 0.0f || _srcRect->h == 0.0f))
		_srcRect = nullptr;

	// rotation point
	SDL_Point rotationPoint;

	// if destination rect valid
	if (pDstRect)
	{
		// set rotation point to center
		rotationPoint.x = pDstRect->w / 2;
		rotationPoint.y = pDstRect->h / 2;

		// if object is rendered in world
		if (_inWorld)
		{
			// add camera offset to destination rect
			pDstRect->x -= m_camera.X - SCREEN_WIDTH / 2;
			pDstRect->y -= m_camera.Y - SCREEN_HEIGHT / 2;
		}
	}

	// flip enum default none
	SDL_RendererFlip flip = SDL_RendererFlip::SDL_FLIP_NONE;

	// if mirror x not 0 flip texture horizontal
	if (_mirror.X != 0 && _mirror.Y == 0)
		flip = SDL_RendererFlip::SDL_FLIP_HORIZONTAL;

	// if mirror y not 0 flip texture vertical
	else if (_mirror.X == 0 && _mirror.Y != 0)
		flip = SDL_RendererFlip::SDL_FLIP_VERTICAL;

	// render texture with angle
	SDL_RenderCopyEx(
		m_pRenderer,					// sdl renderer reference
		_pTexture->GetSDLTexture(),		// sdl texture reference
		_srcRect,						// source rect
		pDstRect,						// destination rect
		_angle,							// angle
		&rotationPoint,					// position of
		flip							// flip flags
	);

	// delete temp destination rect
	delete pDstRect;
}

// present rendered screen
void CRenderer::Present()
{
	SDL_RenderPresent(m_pRenderer);
}
#pragma endregion