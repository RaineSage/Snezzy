#include "Items.h"
#include "Engine.h"
#include "ContentManagement.h"



void GItems::Update(float _deltaSeconds)
{
	// if deltaSeconds zero, return
	if (!_deltaSeconds)
		return;

	if (m_type == SPEEDBONBON)
	{
		
	}

	CTexturedEntity::Update(_deltaSeconds);

	
}
