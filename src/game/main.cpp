#include "GameEngine.hpp"

int main()
{
	using namespace MMORPG;

	GameEngine game_engine;

	if (game_engine.Construct(256, 240, 4, 4))
	{
		game_engine.Start();
	}

	return 0;
}