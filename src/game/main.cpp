#include "GameEngine.hpp"
#include "Ball.hpp"

int main()
{
	using namespace MMORPG;

	GameEngine game_engine;

	//std::unique_ptr<GameObject> ball1 = std::make_unique<Ball>(10, 10);
	//std::unique_ptr<GameObject> ball2 = std::make_unique<Ball>(20, 20);

	//game_engine.RegisterObject(std::move(ball1));
	//game_engine.RegisterObject(std::move(ball2));

	if (game_engine.Construct(256, 240, 4, 4))
	{
		game_engine.Start();
	}

	return 0;
}