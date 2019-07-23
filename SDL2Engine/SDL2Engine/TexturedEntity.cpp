#pragma region project include
#include "TexturedEntity.h"
#include "Texture.h"
#include "Engine.h"
#include "Renderer.h"
#pragma endregion

#pragma region constructor
// constructor
CTexturedEntity::CTexturedEntity(SVector2 _pos, SVector2 _size)
{
	// set position of entity
	m_position = _pos;

	// set rect width and height
	m_rect.w = _size.X;
	m_rect.h = _size.Y;
}

// constructor
CTexturedEntity::CTexturedEntity(SVector2 _pos, SVector2 _size, const char * _pFileName)
	: CTexturedEntity(_pos, _size)
{
	// create texture
	m_pTexture = new CTexture(_pFileName);
}
#pragma endregion

#pragma region public override function
// update every frame
void CTexturedEntity::Update(float _deltaTime)
{
	// set position of rect
	m_rect.x = m_position.X;
	m_rect.y = m_position.Y;
}

// render every frame
void CTexturedEntity::Render()
{
	// render texture at rect
	RENDERER->RenderTexture(m_pTexture, &m_rect, &m_srcRect, 0.0f, SVector2(), m_isWorld);
}
#pragma endregion