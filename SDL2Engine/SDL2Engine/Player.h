#pragma once

#pragma region project include
#include "MoveEntity.h"
#pragma endregion

#pragma region forward decleration
class CAnimation;
class CSound;
#pragma endregion

/// <summary>
/// player class
/// </summary>
class GPlayer :	public CMoveEntity
{
public:
#pragma region constructor
	/// <summary>
	/// constructor
	/// </summary>
	/// <param name="_pos">position of object</param>
	/// <param name="_size">width (x) and height (y) of object</param>
	GPlayer(SVector2 _pos = SVector2(), SVector2 _size = SVector2()) : CMoveEntity(_pos, _size) {}

	/// <summary>
	/// constructor
	/// </summary>
	/// <param name="_pos">position of object</param>
	/// <param name="_size">width and height of object</param>
	/// <param name="_pFileName">absolute file path name</param>
	GPlayer(SVector2 _pos, SVector2 _size, const char* _pFileName) : CMoveEntity(_pos, _size, _pFileName) {}
#pragma endregion

#pragma region destructor
	/// <summary>
	/// destructor
	/// </summary>
	virtual ~GPlayer()
	{
		// delete animations
		delete m_pIdleAnim;
		delete m_pRunAnim;
		delete m_pAttackAnim;
	}
#pragma endregion

#pragma region public override function
	/// <summary>
	/// update every frame
	/// </summary>
	/// <param name="_deltaSeconds">time since last frame</param>
	virtual void Update(float _deltaSeconds) override;

	/// <summary>
	/// render every frame
	/// </summary>
	virtual void Render() override;
#pragma endregion

#pragma region public function
	/// <summary>
	/// initialize player
	/// </summary>
	void Init();
#pragma endregion

private:
#pragma region private pointer
	/// <summary>
	/// current animation
	/// </summary>
	CAnimation* m_pCurrentAnim = nullptr;

	/// <summary>
	/// idle animation
	/// </summary>
	CAnimation* m_pIdleAnim = nullptr;

	/// <summary>
	/// run animation
	/// </summary>
	CAnimation* m_pRunAnim = nullptr;

	/// <summary>
	/// attack animation
	/// </summary>
	CAnimation* m_pAttackAnim = nullptr;

	/// <summary>
	/// shot sound
	/// </summary>
	CSound* m_pShot = nullptr;
#pragma endregion

#pragma region private primitive variable
	/// <summary>
	/// time counter
	/// </summary>
	float m_time = 0.0f;

	/// <summary>
	/// attack time
	/// </summary>
	float m_attackTime = 1.0f;

	/// <summary>
	/// damage time
	/// </summary>
	float m_dammageTime = 2.0f;

	/// <summary>
	/// got damage
	/// </summary>
	bool m_gotDamage = false;
#pragma endregion
};