#pragma once

#pragma region project include
#include <SDL.h>
#include "TexturedEntity.h"
#pragma endregion

class CMessage : public CTexturedEntity
{

public:
	CMessage(const char* _font_path, int _font_size, const char* _message, const SDL_Color _color, SVector2 _pos, SVector2 _size);

	virtual void Update(float _deltaTime) override;

private:
	SDL_Texture* m_msg_texture = nullptr;
	const char* m_font_path = NULL;
	int m_font_size = NULL;
	const char* m_message = NULL;
	SDL_Color m_color = {255, 255, 255};
};

