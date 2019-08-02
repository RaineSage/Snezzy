#pragma region project include
#include "Text.h"
#include "Engine.h"
#include "Renderer.h"
#include "Font.h"
#include "Texture.h"
#pragma endregion

#pragma region constructor
// constructor
CText::CText(const char* _pText, CFont* _pFont, SRect _rect, SColor _color)
{
	// set variable
	m_pText = _pText;
	m_pFont = _pFont;
	m_rect = _rect;
	m_color = _color;

	m_position = SVector2(m_rect.x, m_rect.y);

	// create blank texture
	m_pTexture = new CTexture(nullptr);

	// load text
	Load();
}
#pragma endregion

#pragma region destructor
// destructor
CText::~CText()
{
	
}
#pragma endregion

#pragma region public override function
// update every frame
void CText::Update(float _deltaTime)
{
	CTexturedEntity::Update(_deltaTime);
}

// render every frame
void CText::Render()
{
	CTexturedEntity::Render();
}
#pragma endregion

#pragma region private function
// load text
void CText::Load()
{
	SDL_FreeSurface(m_pSurface);

	m_pSurface = TTF_RenderText_Blended(m_pFont->GetFont(), m_pText, m_color);
	
	SDL_DestroyTexture(m_pTexture->GetSDLTexture());

	m_pTexture->SetSDLTexture(SDL_CreateTextureFromSurface(RENDERER->GetSDLRenderer(), m_pSurface));
}
#pragma endregion