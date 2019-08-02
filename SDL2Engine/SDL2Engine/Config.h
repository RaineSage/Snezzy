#pragma once

/// <summary>
/// static config class
/// </summary>
static class CConfig
{
public:
	static int s_ScreenWidth;
	static int s_ScreenHeight;
	static int s_BlockWidth;
	static int s_BlockHeight;
	static int s_BlockAtlasWidth;
	static int s_BlockAtlasHeight;
	static float s_Gravity;
	static int s_PixelPerMeter;
	static float s_PlayerJump;
	static float s_PlayerSpeed;
	static float s_ColTimer;
	static int s_PlayerSrcRectWidth;
	static int s_PlayerSrcRectHeight;
	static int s_BulletSpeed;
	static int s_MoveEnemyWidth;
	static int s_MoveEnemyHeight;
	static float s_MoveEnemySpeed;

#pragma region public function
	/// <summary>
	/// load config from file
	/// </summary>
	/// <param name="_pFile">file name</param>
	static void LoadConfig(const char* _pFile);
#pragma endregion
};