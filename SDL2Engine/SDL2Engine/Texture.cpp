#pragma region SDL2 include
#include <SDL_image.h>
#pragma endregion

#pragma region project include
#include "Texture.h"
#include "Engine.h"
#include "Renderer.h"
#include "Helper.h"
#pragma endregion

#pragma region constructor
// constructor
CTexture::CTexture(const char * _pFileName)
{
	// if texture null return
	if (!_pFileName)
		return;

	// load texture
	m_pTexture = IMG_LoadTexture(
		RENDERER->GetSDLRenderer(),			// sdl renderer
		GetAssetPath(_pFileName, 4).c_str());	// absolute asset path
}
#pragma endregion

#pragma region destructor
// destructor
CTexture::~CTexture()
{
	// destroy texture
	SDL_DestroyTexture(m_pTexture);
}
#pragma endregion