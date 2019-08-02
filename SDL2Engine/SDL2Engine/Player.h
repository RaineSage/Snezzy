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
class GPlayer : public CMoveEntity
{
public:
#pragma region constructor
	/// <summary>
	/// constructor
	/// </summary>
	/// <param name="_pos">position of entity</param>	
	/// <param name="_size">size of texture (x = width)</param>
	/// <param name="_pFileName">relative path name of texture</param>
	GPlayer(SVector2 _pos, SVector2 _size, const char* _pFileName);
#pragma endregion

#pragma region destructor
	/// <summary>
	/// destructor
	/// </summary>
	virtual ~GPlayer()
	{
		// delete animations
		delete m_pIDLEAnim;
		delete m_pWalkAnim;

		// current does not need to be deleted 
		// because it is used to point at the idle or walk animation
		delete m_pCurrentAnim;
	}
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

private:
#pragma region private pointer
	/// <summary>
	/// current animation pointer
	/// </summary>
	CAnimation* m_pCurrentAnim = nullptr;

	/// <summary>
	/// idle animation reference
	/// </summary>
	CAnimation* m_pIDLEAnim = nullptr;

	/// <summary>
	/// walk animation reference
	/// </summary>
	CAnimation* m_pWalkAnim = nullptr;

	/// <summary>
	/// attack animation reference
	/// </summary>
	CAnimation* m_pAttackAnim = nullptr;

	CSound* m_pJump = nullptr;
#pragma endregion

#pragma region private primitive variable
	/// <summary>
	/// time
	/// </summary>
	float m_time = 0.0f;

	/// <summary>
	/// if attack modus enabled
	/// </summary>
	bool m_attack = false;

	/// <summary>
	/// how long a attack should go
	/// </summary>
	float m_attackTime = 1.0f;
#pragma endregion
};