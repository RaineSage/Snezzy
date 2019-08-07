#pragma once

#include "TexturedEntity.h"
#include "EItemTypes.h"

class GItems : public CTexturedEntity
{
public:
	GItems(SVector2 _pos, SVector2 _size, const char* _pFileName)
		: CTexturedEntity(_pos, _size, _pFileName) {}

	virtual void Update(float _deltaSeconds) override;

	void SetType(ItemTypes _type) { m_type = _type; }

	

protected:
	ItemTypes m_type = BUTTON;
};

