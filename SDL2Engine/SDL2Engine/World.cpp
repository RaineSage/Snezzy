#include <SDL_image.h>

#pragma region project include
#include "World.h"
#include "Config.h"
#include "Engine.h"
#include "ContentManagement.h"
#include "TextureManagement.h"
#include "Player.h"
#include "Helper.h"
#include "MoveEnemy.h"
#include "Texture.h"
#pragma endregion

#pragma region using
using namespace std;
#pragma endregion

#pragma region public function
// initlialize world
void GWorld::Init()
{
	// world in chars
	string world;

	// 0 = background
	// X = dirt
	// W = way
	// L = lava
	// S = player start position
	// E = move enemy
	/*world += "XXXX00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000XXXX\n";
	world += "XXXX00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000XXXX\n";
	world += "XXXX0S000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000XXXX\n";
	world += "XXXX00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000XXXX\n";
	world += "XXXX00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000XXXX\n";
	world += "XXXX00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000XXXX\n";
	world += "XXXX00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000XXXX\n";
	world += "XXXX00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000XXXX\n";
	world += "XXXX00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000XXXX\n";
	world += "XXXX00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000XXXX\n";
	world += "XXXX00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000XXXX\n";
	world += "XXXX000000000000000000000000000000000000000000000E0000000000000000000000000000000000000000000000XXXX\n";
	world += "XXXX000000000000000000000000000000000000000000000000000000E0000000000000000000000000000000E00000XXXX\n";
	world += "XXXX0000000000000000000000000000000000000000WWWWWWWWW000000000000000000000000000000E000000000000XXXX\n";
	world += "XXXX0000000000WWW000000000000000E000000WWWWWXXXXXXXXXWWWWWWWW0000000000E0000000000000WWWWWWWWWWWXXXX\n";
	world += "XXXX00000WWWWWXXXWWWW0000000000000WWWWWXXXXXXXXXXXXXXXXXXXXXXWW000000000000000000WWWWXXXXXXXXXXXXXXX\n";
	world += "XXXXWWWWWXXXXXXXXXXXXWWWLWWWWLWWWWXXXXXXXXXXXXXXXXXXXXXXXXXXXXXWWWWWLWWWWWLWWWWWWXXXXXXXXXXXXXXXXXXX\n";
	world += "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\n";
	world += "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\n";
	world += "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\n";*/

	bool loadString = true;

	if (loadString)
	{
		world = LoadStringFromFile("Files/World.ini");
	}
	else
	{
		world = LoadWorldFromImage("Texture/World/T_World.png");
	}

	// width and height
	int width = 0, height = 0;

	int widthOfWorld = 0;

	// check every char of world
	for (int i = 0; i < world.length(); i++)
	{
		// create textured entity
		CTexturedEntity* pObj = new CTexturedEntity(
			SVector2(width * CConfig::s_BlockWidth, height * CConfig::s_BlockHeight),
			SVector2(CConfig::s_BlockWidth, CConfig::s_BlockHeight),
			nullptr
		);

		// set texture of block
		pObj->SetTexture(m_pTexture);

		// add entity to ctm
		CTM->AddSceneEntity(pObj);

		// x position of texture in atlas texture
		int xPosInTexture = 0;

		// switch current char
		switch (world[i])
		{

		// X char (dirt)
		case 'X':
		{
			// set x position of texture in atlas
			xPosInTexture = 1 * CConfig::s_BlockAtlasWidth;
			break;
		}

		// W char (way)
		case 'W':
		{
			// set x position of texture in atlas
			xPosInTexture = 2 * CConfig::s_BlockAtlasWidth;

			// set collision type of way textured entity to static
			pObj->SetColType(ECollisionType::STATIC);
			break;
		}

		// L char (lava)
		case 'L':
		{
			// set x position of texture in atlas
			xPosInTexture = 3 * CConfig::s_BlockAtlasWidth;

			// set collision type of lava textured entity to static
			pObj->SetColType(ECollisionType::STATIC);
			break;
		}

		// S char (player start position)
		case 'S':
		{
			// create player
			GPlayer* pPlayer = new GPlayer(
				SVector2(width * CConfig::s_BlockWidth, height * CConfig::s_BlockHeight),
				SVector2(CConfig::s_BlockWidth, CConfig::s_BlockHeight * 1.75f),
				nullptr
			);

			CTexture* pTexture = TTM->GetTexture("Player");

			if (!pTexture)
			{
				TTM->AddTexture("Player", new CTexture("Texture/Character/Player/T_Player.png"));
				pTexture = TTM->GetTexture("Player");
			}

			pPlayer->SetTexture(pTexture);

			// set player tag, collision type to dynamic and speed
			pPlayer->SetTag("Player");
			pPlayer->SetColType(ECollisionType::DYNAMIC);
			pPlayer->SetSpeed(CConfig::s_PlayerSpeed);
			pPlayer->ActiveGravity();

			// add player to ctm
			CTM->AddPersistentEntity(pPlayer);
			break;
		}

		// create enemy WALKER
		case 'E':
		{
			GMoveEnemy* pEnemy = new GMoveEnemy(
				SVector2(width * CConfig::s_BlockWidth, height * CConfig::s_BlockHeight),
				SVector2(CConfig::s_MoveEnemyWidth, CConfig::s_MoveEnemyHeight),
				nullptr
			);

			CTexture* pTexture = TTM->GetTexture("MoveEnemy");

			if (!pTexture)
			{
				TTM->AddTexture("MoveEnemy", new CTexture("Texture/Character/Enemy/T_MoveEnemy.png"));
				pTexture = TTM->GetTexture("MoveEnemy");
			}

			pEnemy->SetTexture(pTexture);

			pEnemy->Init();
			CTM->AddPersistentEntity(pEnemy);
			break;
		}

		// create enemy JUMPER
		case 'J':
		{
			GMoveEnemy* pEnemy = new GMoveEnemy(
				SVector2(width * CConfig::s_BlockWidth, height * CConfig::s_BlockHeight),
				SVector2(CConfig::s_MoveEnemyWidth, CConfig::s_MoveEnemyHeight),
				nullptr
			);

			CTexture* pTexture = TTM->GetTexture("MoveEnemy");

			if (!pTexture)
			{
				TTM->AddTexture("MoveEnemy", new CTexture("Texture/Character/Enemy/T_MoveEnemy.png"));
				pTexture = TTM->GetTexture("MoveEnemy");
			}

			pEnemy->SetTexture(pTexture);
			pEnemy->SetType(JUMPER);

			pEnemy->Init();
			CTM->AddPersistentEntity(pEnemy);
			break;
		}

		// create enemy SHOOTER
		case 'F':
		{
			GMoveEnemy* pEnemy = new GMoveEnemy(
				SVector2(width * CConfig::s_BlockWidth, height * CConfig::s_BlockHeight),
				SVector2(CConfig::s_MoveEnemyWidth, CConfig::s_MoveEnemyHeight),
				nullptr
			);

			CTexture* pTexture = TTM->GetTexture("MoveEnemy");

			if (!pTexture)
			{
				TTM->AddTexture("MoveEnemy", new CTexture("Texture/Character/Enemy/T_MoveEnemy.png"));
				pTexture = TTM->GetTexture("MoveEnemy");
			}

			pEnemy->SetTexture(pTexture);
			pEnemy->SetType(SHOOTER);

			pEnemy->Init();
			CTM->AddPersistentEntity(pEnemy);
			break;
		}

		// default
		default:
			break;
		}

		// set source rect of current block
		pObj->SetSrcRect(SRect(CConfig::s_BlockAtlasWidth, CConfig::s_BlockAtlasHeight, xPosInTexture, 0));

		// increase width
		width++;

		// if current char is new line
		if (world[i] == '\n')
		{
			// increase height and reset width
			height++;
			widthOfWorld = width;
			width = 0;
		}
	}

	CTM->SetupCollision(widthOfWorld);
}
#pragma endregion

string GWorld::LoadWorldFromImage(const char* _pFileName)
{
	string text = "";

	SDL_Surface* pWorld = IMG_Load(GetAssetPath(_pFileName, 4).c_str());

	char* pPixels = (char*)pWorld->pixels;

	for (int i = 0; i < pWorld->w * pWorld->h; i++)
	{
		uint8_t r = pPixels[0];
		uint8_t g = pPixels[1];
		uint8_t b = pPixels[2];

		// black = 0 = background
		// white = X = dirt
		// blue = W = way
		// red = L = lava
		// green = S = player start position
		// yellow = E = move enemy

		if (r == 0 && g == 0 && b == 0)
			text += '0';
		else if (r == 255 && g == 255 && b == 255)
			text += 'X';
		else if (r == 0 && g == 0 && b == 255)
			text += 'W';
		else if (r == 255 && g == 0 && b == 0)
			text += 'L';
		else if (r == 0 && g == 255 && b == 0)
			text += 'S';
		else if (r == 255 && g == 255 && b == 0)
			text += 'E';


		pPixels += pWorld->format->BytesPerPixel;

		if ((i + 1) % pWorld->w == 0)
			text += '\n';
	}


	return text;
}