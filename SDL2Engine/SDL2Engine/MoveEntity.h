#pragma once

#pragma region system include
#include <list> 
#pragma endregion

#pragma region project include
#include "TexturedEntity.h" 
#include "EEnemyTypes.h"
#pragma endregion

#pragma region using
using namespace std;
#pragma endregion

/// <summary>
/// moveable entity class
/// </summary>
class CMoveEntity : public CTexturedEntity
{
public:
#pragma region constructor
	/// <summary>
	/// constructor
	/// </summary>
	/// <param name="_pos">position of object</param>
	/// <param name="_size">width (x) and height (y) of object</param>
	CMoveEntity(SVector2 _pos = SVector2(), SVector2 _size = SVector2()) : CTexturedEntity(_pos, _size) 
	{
		SetCollisionList();
	}

	/// <summary>
	/// constructor
	/// </summary>
	/// <param name="_pos">position of object</param>
	/// <param name="_size">width and height of object</param>
	/// <param name="_pFileName">absolute file path name</param>
	CMoveEntity(SVector2 _pos, SVector2 _size, const char* _pFileName) : CTexturedEntity(_pos, _size, _pFileName)
	{
		SetCollisionList();
	}
#pragma endregion

#pragma region destructor
	/// <summary>
	/// destructor
	/// </summary>
	virtual ~CMoveEntity() {}
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
	void Render() override;
#pragma endregion

#pragma region public inline function
	/// <summary>
	/// activate gravity
	/// </summary>
	inline void ActiveGravity() { m_gravity = true; }
	
	/// <summary>
	/// deactivate gravity
	/// </summary>
	inline void DeactivateGravity() { m_gravity = false; }

	/// <summary>
	/// get movement speed
	/// </summary>
	/// <returns>movement speed</returns>
	inline float GetSpeed() { return m_speed; }

	/// <summary>
	/// set movement speed
	/// </summary>
	/// <param name="_speed">movement speed to set</param>
	inline void SetSpeed(float _speed) { m_speed = _speed; }

	/// <summary>
	/// get movement values
	/// </summary>
	/// <returns>movement values</returns>
	inline SVector2 GetMovement() { return m_movement; }

	/// <summary>
	/// set movement values
	/// </summary>
	/// <param name="_movement">movement values</param>
	inline void SetMovement(SVector2 _movement) { m_movement = _movement; }
#pragma endregion

	/// <summary>
	/// fill collision list with all entities near
	/// </summary>
	void SetCollisionList();

protected:
#pragma region protected primitive variable
	/// <summary>
	/// gravity enabled
	/// </summary>
	bool m_gravity = false;

	/// <summary>
	/// entity is on ground
	/// </summary>
	bool m_isGrounded = false;

	/// <summary>
	/// movement speed
	/// </summary>
	float m_speed;

	/// <summary>
	/// time since fall begin
	/// </summary>
	float m_fallTime = 0.0f;
#pragma endregion

#pragma region protected variable
	/// <summary>
	/// movement values
	/// </summary>
	SVector2 m_movement;

	/// <summary>
	/// type of enemy
	/// </summary>
	EEnemyTypes m_eType = WALKER;
#pragma endregion

private:
#pragma region private primitive variable
	/// <summary>
	/// time until collision check
	/// </summary>
	float m_colTimer = 0.0f;
#pragma endregion

	protected:
#pragma region private primitive variable
	/// <summary>
	/// check if player attacks
	/// </summary>
	bool m_attack = false;
#pragma endregion

#pragma region private variable
	/// <summary>
	/// list of all entities near for collision check
	/// </summary>
	list<CTexturedEntity*> m_pColEntities;
#pragma endregion

	private:
#pragma region private function
	/// <summary>
	/// check collision by movement and gravity
	/// </summary>
	/// <param name="_deltaTime">time since last frame</param>
	/// <param name="_useGravity">use gravity for check</param>
	void CheckCollision(float _deltaTime, bool _useGravity);
#pragma endregion
};