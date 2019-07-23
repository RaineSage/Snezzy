#pragma region project include
#include "ContentManagement.h"
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

		// remove and delete first entity to remove
		m_pRemoveEntities.pop_front();
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

#pragma region private function
// add entity to list
void CContentManagement::AddEntity(CEntity * _pEntity, list<CEntity*>& _pList)
{
	_pList.push_back(_pEntity);
}
#pragma endregion