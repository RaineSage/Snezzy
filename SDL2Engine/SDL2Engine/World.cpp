#pragma region system include
#include <string>
#pragma endregion

#pragma region project include
#include "World.h"
#include "Config.h"
#include "Engine.h"
#include "ContentManagement.h"
#include "Player.h"
#include "EnemyAI.h"
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
	// E = enemy WALKER
	// F = enemy SHOOTER
	// J = enemy JUMPER
	world += "XXXX00000000000000000000000000000000000000000000000000000000000000000000000000000XXXX\n";
	world += "XXXX00000000000000000000000000000000000000000000000000000000000000000000000000000XXXX\n";
	world += "XXXX00000000000000000000000000000000000000000000000000000000000000000000000000000XXXX\n";
	world += "XXXX00000000000000000000000000000000000000000000000000000000000000000000000000000XXXX\n";
	world += "XXXX00000000000000000000000000000000000000000000000000000000000000000000000000000XXXX\n";
	world += "XXXX00000000000000000000000000000000000000000000000000000000000000000000000000000XXXX\n";
	world += "XXXX00000000000000000000000000000000000000000000000000000000000000000000000000000XXXX\n";
	world += "XXXX00000000000000000000000000000000000000000000000000000000000000000000000000000XXXX\n";
	world += "XXXX00000000000000000000000000000000000000000000000000000000000000000000000000000XXXX\n";
	world += "XXXX00000000000000000000000000000000000000000000000000F00000000000000000000000000XXXX\n";
	world += "XXXX00000000000000000000000000000000000F00000000000000W00000000000000000000000000XXXX\n";
	world += "XXXX000000000000000000000000000000000WWWWWWWW00000000WX00000000000000000000000000XXXX\n";
	world += "XXXX000000000000000000000000000000000000000000000000WXX0000000000000000Fa00000000XXXX\n";
	world += "XXXX000000000WW000000000000WWWWWW000000000000000000WXXX000000000000000WWWWWWW0000XXXX\n";
	world += "XXXX00S00000WXXW0000000000000XX0000000000000000000WXXXX00000000000000000000000000XXXX\n";
	world += "XXXX0000000WXXXXW000000E0000WXXW00000J00000J00000WXXXXX00000000F00W00000E00000000XXXX\n";
	world += "XXXXWWWWWWWXXXXXXWWWWWWWWWWWWXXWWWWWWWWWWWWWWWWWWXXXXXXWWWWWW00W00WWWWWWWWWWWWWWWXXXX\n";
	world += "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX00X00XXXXXXXXXXXXXXXXXXX\n";
	world += "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX00X00XXXXXXXXXXXXXXXXXXX\n";
	world += "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX00X00XXXXXXXXXXXXXXXXXXX";

	// width and height
	int width = 0, height = 0;

	// check every char of world
	for (int i = 0; i < world.length(); i++)
	{
		// create textured entity
		CTexturedEntity* pObj = new CTexturedEntity(
			SVector2(width * BLOCK_WIDTH, height * BLOCK_HEIGHT),
			SVector2(BLOCK_WIDTH, BLOCK_HEIGHT),
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
			xPosInTexture = 1 * BLOCK_ATLAS_WIDTH;

			// set collision type of dirt textured entity to static
			pObj->SetColType(ECollisionType::STATIC);
			break;
		}

		// W char (way)
		case 'W':
		{
			// set x position of texture in atlas
			xPosInTexture = 2 * BLOCK_ATLAS_WIDTH;

			// set collision type of way textured entity to static
			pObj->SetColType(ECollisionType::STATIC);
			break;
		}

		// L char (lava)
		case 'L':
		{
			// set x position of texture in atlas
			xPosInTexture = 3 * BLOCK_ATLAS_WIDTH;

			// set collision type of lava textured entity to static
			pObj->SetColType(ECollisionType::STATIC);
			break;
		}

		// S char (player start position)
		case 'S':
		{
			// create player
			GPlayer* pPlayer = new GPlayer(
				SVector2(width * BLOCK_WIDTH, height * BLOCK_HEIGHT),
				SVector2(BLOCK_WIDTH, BLOCK_HEIGHT),
				"Texture/Character/Player/T_Attack.bmp"
			);

			// set Player to Idle Texture
			pPlayer->SetSrcRect(SRect(193, 175, 0, 0));

			// set player tag, collision type to dynamic and speed
			pPlayer->SetTag("Player");
			pPlayer->SetColType(ECollisionType::DYNAMIC);
			pPlayer->SetSpeed(PLAYER_SPEED);

			// add player to ctm
			CTM->AddPersistentEntity(pPlayer);
			break;
		}

		// E char (enemy WALKER)
		case 'E':
		{
			// create enemy
			GEnemyAI* pEnemy = new GEnemyAI(
				SVector2(width * BLOCK_WIDTH, height * BLOCK_HEIGHT),
				SVector2(BLOCK_WIDTH, BLOCK_HEIGHT),
				"Texture/Character/Enemy/T_Enemy.bmp"
			);

			// set enemy tag, collision type to dynamic and speed
			pEnemy->SetTag("Enemy");
			pEnemy->SetColType(ECollisionType::DYNAMIC);
			pEnemy->SetSpeed(50.0f);

			// add enemy to ctm
			CTM->AddPersistentEntity(pEnemy);
			break;
		}

		// F char (enemy SHOOTER)
		case 'F':
		{
			// create enemy
			GEnemyAI* pEnemy = new GEnemyAI(
				SVector2(width * BLOCK_WIDTH, height * BLOCK_HEIGHT),
				SVector2(BLOCK_WIDTH, BLOCK_HEIGHT),
				"Texture/Character/Enemy/T_Enemy.bmp"
			);

			// set enemy tag, collision type to dynamic and enemy type
			pEnemy->SetTag("Enemy");
			pEnemy->SetColType(ECollisionType::DYNAMIC);
			pEnemy->SetType(SHOOTER);

			// add enemy to ctm
			CTM->AddPersistentEntity(pEnemy);
			break;
		}

		// J char (enemy JUMPER)
		case 'J':
		{
			// create enemy
			GEnemyAI* pEnemy = new GEnemyAI(
				SVector2(width * BLOCK_WIDTH, height * BLOCK_HEIGHT),
				SVector2(BLOCK_WIDTH, BLOCK_HEIGHT),
				"Texture/Character/Enemy/T_Enemy.bmp"
			);

			// set enemy tag, collision type to dynamic, speed, jump interval and enemy type
			pEnemy->SetTag("Enemy");
			pEnemy->SetColType(ECollisionType::DYNAMIC);
			pEnemy->SetSpeed(50.0f);
			pEnemy->SetJumpTime(1.5f);
			pEnemy->SetType(JUMPER);

			// add enemy to ctm
			CTM->AddPersistentEntity(pEnemy);
			break;
		}

		// default
		default:
			break;
		}

		// set source rect of current block
		pObj->SetSrcRect(SRect(BLOCK_ATLAS_WIDTH, BLOCK_ATLAS_HEIGHT, xPosInTexture, 0));

		// increase width
		width++;

		// if current char is new line
		if (world[i] == '\n')
		{
			// increase height and reset width
			height++;
			width = 0;
		}
	}
}
#pragma endregion