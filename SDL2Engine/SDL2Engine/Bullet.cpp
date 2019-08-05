#pragma region project include
#include "Bullet.h"
#include "Engine.h"
#include "ContentManagement.h"
#pragma endregion

#pragma region public override function
// update every frame
void GBullet::Update(float _deltaSeconds)
{
	// if collision
	if (m_pColTarget)
	{
		// remove bullet
		CTM->RemoveObject(this);

		// if player defenseless
		if (!CMoveEntity::m_Attack)
		{
			// if collision target is player delete
			if (m_pColTarget->GetTag() == "Player")
				CTM->RemoveObject(m_pColTarget);
		}

	}



	// update parent
	CMoveEntity::Update(_deltaSeconds);
}

// render every frame
void GBullet::Render()
{
	CMoveEntity::Render();
}
#pragma endregion