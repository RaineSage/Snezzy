#pragma once

#pragma region forward decleration
class SRect;
#pragma endregion

/// <summary>
/// class for physic function
/// </summary>
class CPhysic
{
public:
#pragma region public function
	/// <summary>
	/// check collision of two rects
	/// </summary>
	/// <param name="_rectOne">rect one</param>
	/// <param name="_rectTwo">rect two</param>
	/// <returns>return if collide</returns>
	static bool RectRectCollision(SRect _rectOne, SRect _rectTwo);

	/// <summary>
	/// check collision of two rects (enemy wall to wall walk)
	/// </summary>
	/// <param name="_rectOne">rect one</param>
	/// <param name="_rectTwo">rect two</param>
	/// <returns>return if collide</returns>
	static bool RectRectCollisionX(SRect _rectOne, SRect _rectTwo);

	/// <summary>
	/// check collision of two rects (enemy JUMPER)
	/// </summary>
	/// <param name="_rectOne">rect one</param>
	/// <param name="_rectTwo">rect two</param>
	/// <returns>return if collide</returns>
	static bool RectRectCollisionY(SRect _rectOne, SRect _rectTwo);
#pragma endregion
};