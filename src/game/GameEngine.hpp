#pragma once
#include "olcPixelGameEngine.h"
#include "GameObject.hpp"

namespace MMORPG
{
	class GameEngine : public olc::PixelGameEngine
	{
	public:
		GameEngine() { sAppName = "Game"; }

		bool RegisterObject(std::unique_ptr<GameObject> object);
		bool OnUserCreate() override;
		bool OnUserUpdate(float fElapsedTime) override;

	private:
		std::vector<std::unique_ptr<GameObject>> game_objects;
	};
}
