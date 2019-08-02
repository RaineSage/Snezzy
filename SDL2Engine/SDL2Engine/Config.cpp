#pragma region project include
#include "Config.h"
#include "Helper.h"
#pragma endregion

#pragma region variables
int CConfig::s_ScreenWidth = 640;
int CConfig::s_ScreenHeight = 480;
int CConfig::s_BlockWidth = 64;
int CConfig::s_BlockHeight = 64;
int CConfig::s_BlockAtlasWidth = 26;
int CConfig::s_BlockAtlasHeight = 26;
float CConfig::s_Gravity = 9.81f;
int CConfig::s_PixelPerMeter = 32;
float CConfig::s_PlayerJump = 1.0f;
float CConfig::s_PlayerSpeed = 128.0f;
float CConfig::s_ColTimer = 0.1f;
int CConfig::s_PlayerSrcRectWidth = 36;
int CConfig::s_PlayerSrcRectHeight = 46;
int CConfig::s_BulletSpeed = 250.0f;
int CConfig::s_MoveEnemyWidth = 32;
int CConfig::s_MoveEnemyHeight = 32;
float CConfig::s_MoveEnemySpeed = 125.0f;
#pragma endregion

#pragma region public function
// load config from file
void CConfig::LoadConfig(const char* _pFile)
{
	string text = LoadStringFromFile(_pFile);

	string variable = "";
	string value = "";

	while (text.length() > 0)
	{
		variable = "";
		value = "";

		while (text[0] != '?')
		{
			variable += text[0];

			text.erase(0, 1);
		}

		text.erase(0, 1);

		while (text[0] != '\n')
		{
			value += text[0];

			text.erase(0, 1);
		}

		text.erase(0, 1);

		if (variable == "ScreenWidth")
			s_ScreenWidth = stoi(value);

		else if (variable == "ScreenHeight")
			s_ScreenHeight = stoi(value);

		else if (variable == "BlockWidth")
			s_BlockWidth = stoi(value);

		else if (variable == "BlockHeight")
			s_BlockHeight = stoi(value);

		else if (variable == "BlockAtlasWidth")
			s_BlockAtlasWidth = stoi(value);

		else if (variable == "BlockAtlasHeight")
			s_BlockAtlasHeight = stoi(value);

		else if (variable == "Gravity")
			s_Gravity = stoi(value) * 0.01f;

		else if (variable == "PixelPerMeter")
			s_PixelPerMeter = stoi(value);

		else if (variable == "PlayerJump")
			s_PlayerJump = stoi(value) * 0.01f;

		else if (variable == "PlayerSpeed")
			s_PlayerSpeed = stoi(value) * 0.01f;

		else if (variable == "ColTimer")
			s_ColTimer = stoi(value) * 0.0001f;

		else if (variable == "PlayerSrcRectWidth")
			s_PlayerSrcRectWidth = stoi(value);

		else if (variable == "PlayerSrcRectHeight")
			s_PlayerSrcRectHeight = stoi(value);

		else if (variable == "BulletSpeed")
			s_BulletSpeed = stoi(value) * 0.01f;

		else if (variable == "MoveEnemyWidth")
			s_MoveEnemyWidth = stoi(value);

		else if (variable == "MoveEnemyHeight")
			s_MoveEnemyHeight = stoi(value);

		else if (variable == "MoveEnemySpeed")
			s_MoveEnemySpeed = stoi(value) * 0.01f;
	}
}
#pragma endregion