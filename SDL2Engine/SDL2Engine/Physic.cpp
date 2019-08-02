#pragma region project include
#include "Physic.h"
#include "Rect.h"
#pragma endregion

#pragma region public function
// check collision of two rects
bool CPhysic::RectRectCollision(SRect _rectOne, SRect _rectTwo)
{
	// if first rect x + w smaller than second rect x no collision
	if (_rectOne.x + _rectOne.w < _rectTwo.x)
		return false;

	// if first rect x higher than second rect x + w no collision
	if (_rectOne.x > _rectTwo.x + _rectTwo.w)
		return false;

	// if first rect y + h smaller than second rect y no collision
	if (_rectOne.y + _rectOne.h < _rectTwo.y)
		return false;

	// if first rect y higher than second rect y + h no collision
	if (_rectOne.y > _rectTwo.y + _rectTwo.h)
		return false;

	// if collision return true
 	return true;
}
#pragma endregion