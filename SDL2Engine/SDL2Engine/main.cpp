#pragma region project include
#include "Engine.h"
#include "Game.h"
#pragma endregion

/// <summary>
/// main entry point
/// </summary>
/// <param name="argc">number of arguments</param>
/// <param name="argv">arguments array</param>
/// <returns>shutdown code</returns>
int main(int argc, char* argv[])
{
	// result by initialize engine
	int result = ENGINE->Init();

	// if result 0
	if (!result)
	{
		// initialize game
		GAME->Init();

		// run engine
		ENGINE->Run();
	}

	// clean engine
	ENGINE->Clean();

	// shut down correctly
	return 0;
}