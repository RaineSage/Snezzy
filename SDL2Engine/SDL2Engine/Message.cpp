#include "Message.h"
#include "Helper.h"
#include "Engine.h"
#include "Renderer.h"
#include <SDL_ttf.h>
#include <iostream>

CMessage::CMessage(const char* _font_path, int _font_size, const char* _message, const SDL_Color _color, SVector2 _pos, SVector2 _size) : CTexturedEntity(_pos, _size)
{
	m_font_path = _font_path;
	m_font_size = _font_size;
	m_message = _message;
	m_color = _color;
}

void CMessage::Update(float _deltaTime)
{
	TTF_Font* font = TTF_OpenFont(GetAssetPath(m_font_path, 4).c_str(), m_font_size);

	auto text_surface = TTF_RenderText_Solid(font, m_message, m_color);

	m_msg_texture = SDL_CreateTextureFromSurface(RENDERER->GetSDLRenderer(), text_surface);

	SDL_FreeSurface(text_surface);

	SDL_RenderCopy(RENDERER->GetSDLRenderer(), m_msg_texture, nullptr, &m_rect);

	// update parent
	CTexturedEntity::Update(_deltaTime);
}