#pragma region project include
#include "Mouse.h"
#include "Input.h"
#pragma endregion

#pragma region public override function
// update every frame
void CMouse::Update(float _deltaTime)
{
	m_position.X = CInput::GetMousePosition().X - m_center.X * m_rect.w;
	m_position.Y = CInput::GetMousePosition().Y - m_center.Y * m_rect.h;

	CTexturedEntity::Update(_deltaTime);
}

// render every frame
void CMouse::Render()
{
	if (m_visible)
		CTexturedEntity::Render();
}
#pragma endregion

#pragma region public function
// set texture of mouse
void CMouse::SetTexture(CTexture* _pTexture)
{
	if (m_pTexture)
		delete m_pTexture;

	m_pTexture = _pTexture;
}
#pragma endregion