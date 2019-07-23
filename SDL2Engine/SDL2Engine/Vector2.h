#pragma once

/// <summary>
/// vector 2 struct
/// </summary>
struct SVector2
{
public:
#pragma region constructor
	/// <summary>
	/// constructor
	/// </summary>
	/// <param name="_x">x value</param>
	/// <param name="_y">y value</param>
	SVector2(float _x = 0.0f, float _y = 0.0f)
	{
		X = _x;
		Y = _y;
	}
#pragma endregion

#pragma region public primitive variable
	/// <summary>
	/// x value
	/// </summary>
	float X = 0.0f;

	/// <summary>
	/// y value
	/// </summary>
	float Y = 0.0f;
#pragma endregion

#pragma region operator
	/// <summary>
	/// vector 2 + vector 2
	/// </summary>
	/// <param name="_vec">other vector 2d</param>
	/// <returns>new vector 2d</returns>
	SVector2 operator + (SVector2 _vec)
	{
		// return new vector by add other vector components to this components
		return SVector2(X + _vec.X, Y + _vec.Y);
	}

	/// <summary>
	/// vector 2 * float
	/// </summary>
	/// <param name="_value">float to multiply</param>
	/// <returns>new vector 2d with every component multiplied by value</returns>
	SVector2 operator * (float _value)
	{
		// return new vector by multiply x and y value with given float value
		return SVector2(X * _value, Y * _value);
	}
#pragma endregion
};