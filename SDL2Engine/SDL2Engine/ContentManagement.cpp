#pragma region project include
#include "ContentManagement.h"
#include "MoveEntity.h"
#include "Config.h"
#include "Engine.h"
#include "Renderer.h"
#pragma endregion

#pragma region destructor
// destructor
CContentManagement::~CContentManagement()
{
	// remove first entity of scene entities until no more left
	while (m_pSceneEntities.size() > 0)
		m_pSceneEntities.pop_front();

	// remove first entity of persistent entities until no more left
	while (m_pPersistentEntities.size() > 0)
		m_pPersistentEntities.pop_front();

	// remove first entity of ui entities until no more left
	while (m_pUIEntities.size() > 0)
		m_pUIEntities.pop_front();
}
#pragma endregion

#pragma region public override function
// update every frame
void CContentManagement::Update(float _deltaTime)
{
	// until no more entities to remove
	while (m_pRemoveEntities.size() > 0)
	{
		// get first entity reference
		CEntity* pEntity = m_pRemoveEntities.front();

		// remove reference of lists
		m_pSceneEntities.remove(pEntity);
		m_pPersistentEntities.remove(pEntity);
		m_pUIEntities.remove(pEntity);
		m_pColEntities.remove(pEntity);

		if (dynamic_cast<CMoveEntity*>(pEntity))
		{
			m_pMoveEntities.remove((CMoveEntity*)pEntity);

			m_colCheckTime = CConfig::s_ColTimer / m_pMoveEntities.size();
		}

		// remove and delete first entity to remove
		m_pRemoveEntities.remove(pEntity);
		delete pEntity;
	}

	// update every scene entity
	for (CEntity* _pEntity : m_pSceneEntities)
		_pEntity->Update(_deltaTime);

	// update every ui entity
	for (CEntity* _pEntity : m_pUIEntities)
		_pEntity->Update(_deltaTime);

	// update every persistent entity
	for (CEntity* _pEntity : m_pPersistentEntities)
		_pEntity->Update(_deltaTime);

	m_colTimer -= _deltaTime;

	if (m_colTimer > 0 || !m_pMoveEntities.size())
		return;

	CMoveEntity* pMoveEntity = m_pMoveEntities.front();
	m_pMoveEntities.front()->SetCollisionList();
	m_pMoveEntities.remove(pMoveEntity);
	m_pMoveEntities.push_back(pMoveEntity);

	m_colTimer = CConfig::s_ColTimer;

	int i = 0;
	
	while (i < m_pMoveEntities.size())
	{
		i++;

		CMoveEntity* pMoveEntity = m_pMoveEntities.front();

		if (pMoveEntity->GetPosition().X > RENDERER->GetCamera().X - CConfig::s_ScreenWidth * 0.6f
			&& pMoveEntity->GetPosition().X < RENDERER->GetCamera().X + CConfig::s_ScreenWidth * 0.6f
			&& pMoveEntity->GetPosition().Y > RENDERER->GetCamera().Y - CConfig::s_ScreenHeight * 0.6f
			&& pMoveEntity->GetPosition().Y < RENDERER->GetCamera().Y + CConfig::s_ScreenHeight * 0.6f)
		{
			m_pMoveEntities.front()->SetCollisionList();
		}

		m_pMoveEntities.remove(pMoveEntity);
		m_pMoveEntities.push_back(pMoveEntity);

		m_colTimer = m_colCheckTime;
	}
	
}

// render every frame
void CContentManagement::Render()
{
	// order is important for layering

	// render every scene entity
	for (CEntity* _pEntity : m_pSceneEntities)
		_pEntity->Render();

	// render every persistent entity
	for (CEntity* _pEntity : m_pPersistentEntities)
		_pEntity->Render();

	// render every ui entity
	for (CEntity* _pEntity : m_pUIEntities)
		_pEntity->Render();
}
#pragma endregion

void CContentManagement::SetupCollision(int _width)
{
	for (int i = 0; i < _width; i += 5)
	{
		m_colRowColumn.push_back(list<CEntity*>());
	}

	for (int i = 0; i < _width; i++)
	{
		for (CEntity* pEntity : m_pSceneEntities)
		{
			if (pEntity->GetPosition().X >= i * CConfig::s_BlockWidth && pEntity->GetPosition().X < (i + 1) * CConfig::s_BlockWidth)
			{
				list<list<CEntity*>>::iterator it = m_colRowColumn.begin();

				// Advance the iterator by 2 positions,
				advance(it, i / 5);
				it->push_back(pEntity);

			}
		}
	}

	for (CEntity* pEntity : m_pSceneEntities)
	{
		if (dynamic_cast<CTexturedEntity*>(pEntity))
		{
			if (((CTexturedEntity*)pEntity)->GetColType() != ECollisionType::NONE)
				m_pColEntities.push_back(pEntity);
		}
	}
}

void CContentManagement::Clear()
{
	for (CEntity* pEntity : m_pSceneEntities)
		m_pRemoveEntities.push_back(pEntity);

	for (CEntity* pEntity : m_pPersistentEntities)
		m_pRemoveEntities.push_back(pEntity);

	for (CEntity* pEntity : m_pUIEntities)
		m_pRemoveEntities.push_back(pEntity);
}

list<CEntity*> CContentManagement::GetCollisionRowColumn(SVector2 _pos)
{
	for (list<CEntity*> pList : m_colRowColumn)
	{
		if (_pos.X > pList.front()->GetPosition().X && _pos.X < pList.back()->GetPosition().X + CConfig::s_BlockWidth)
		{
			return pList;
		}
	}

	return list<CEntity*>();
}

#pragma region private function
// add entity to list
void CContentManagement::AddEntity(CEntity * _pEntity, list<CEntity*>& _pList)
{
	_pList.push_back(_pEntity);

	if (dynamic_cast<CMoveEntity*>(_pEntity))
	{
		m_pMoveEntities.push_back((CMoveEntity*)_pEntity);

		m_colCheckTime = CConfig::s_ColTimer / m_pMoveEntities.size();
	}
}
#pragma endregion