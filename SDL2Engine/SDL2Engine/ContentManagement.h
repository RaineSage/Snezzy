#pragma once

#pragma region system include
#include <list>
#pragma endregion

#pragma region project include
#include "Entity.h"
#pragma endregion

#pragma region using
using namespace std;
#pragma endregion

/// <summary>
/// class to manage update, render and delete of all entities
/// </summary>
class CContentManagement :	public CEntity
{
public:
#pragma region constructor
	/// <summary>
	/// constructor
	/// </summary>
	CContentManagement() {}
#pragma endregion

#pragma region destructor
	/// <summary>
	/// destructor
	/// </summary>
	~CContentManagement();
#pragma endregion

#pragma region public override function
	/// <summary>
	/// update every frame
	/// </summary>
	/// <param name="_deltaTime">time since last frame</param>
	virtual void Update(float _deltaTime) override;

	/// <summary>
	/// render every frame
	/// </summary>
	virtual void Render() override;
#pragma endregion

#pragma region public inline function
	/// <summary>
	/// get all scene entities
	/// </summary>
	/// <returns>list of all scene entities</returns>
	inline list<CEntity*> GetSceneEntities() { return m_pSceneEntities; }

	/// <summary>
	/// add entity to scene entities
	/// </summary>
	/// <param name="_pEntity">entity reference to add</param>
	inline void AddSceneEntity(CEntity* _pEntity) { AddEntity(_pEntity, m_pSceneEntities); }

	/// <summary>
	/// get all ui entities
	/// </summary>
	/// <returns>list of all ui entities</returns>
	inline list<CEntity*> GetUIEntities() { return m_pUIEntities; }

	/// <summary>
	/// add entity to ui entities
	/// </summary>
	/// <param name="_pEntity">entity reference to add</param>
	inline void AddUIEntity(CEntity* _pEntity) { AddEntity(_pEntity, m_pUIEntities); }

	/// <summary>
	/// get all persistent entities
	/// </summary>
	/// <returns>list of all persistent entities</returns>
	inline list<CEntity*> GetPersistentEntities() { return m_pPersistentEntities; }

	/// <summary>
	/// add entity to persistent entities
	/// </summary>
	/// <param name="_pEntity">entity reference to add</param>
	inline void AddPersistentEntity(CEntity* _pEntity) { AddEntity(_pEntity, m_pPersistentEntities); }

	/// <summary>
	/// add entity to remove entities
	/// </summary>
	/// <param name="_pEntity">entity reference to remove</param>
	inline void RemoveEntity(CEntity* _pEntity) { m_pRemoveEntities.push_back(_pEntity); }
#pragma endregion

private:
#pragma region private variable
	/// <summary>
	/// list with all scene entity references
	/// </summary>
	list<CEntity*> m_pSceneEntities;

	/// <summary>
	/// list with all ui entity references
	/// </summary>
	list<CEntity*> m_pUIEntities;

	/// <summary>
	/// list with all persistent entity references
	/// </summary>
	list<CEntity*> m_pPersistentEntities;

	/// <summary>
	/// list of all entities to remove next frame
	/// </summary>
	list<CEntity*> m_pRemoveEntities;
#pragma endregion

private:
#pragma region private function
	/// <summary>
	/// add entity to list
	/// </summary>
	/// <param name="_pEntity">entity reference to add</param>
	/// <param name="_pList">list reference to add to</param>
	void AddEntity(CEntity* _pEntity, list<CEntity*>& _pList);
#pragma endregion
};