#pragma once
#include "olcPixelGameEngine.h"
#include "GameObject.hpp"
#include "InputListener.hpp"

namespace MMORPG
{
	class GameEngine : public olc::PixelGameEngine
	{
	public:
		GameEngine() { sAppName = "Game"; }

		void AddObject(std::shared_ptr<GameObject> object);
		void AddInputRegister(std::shared_ptr<InputListener> object);
		bool OnUserCreate() override;
		bool OnUserUpdate(float fElapsedTime) override;

	private:
		std::list<std::shared_ptr<InputListener>> _input_listeners;
		std::list<std::shared_ptr<GameObject>> _game_objects;
	};
}
