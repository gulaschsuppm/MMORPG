#pragma once
#include "olcPixelGameEngine.h"
#include "DrawingObject.hpp"
#include "PhysicalObject.hpp"
#include "InputListener.hpp"
#include "PhysicsEngine.hpp"

namespace MMORPG
{
	class GameEngine : public olc::PixelGameEngine
	{
	public:
		GameEngine() { sAppName = "Game"; }

		void AddDrawingObject(std::shared_ptr<DrawingObject> object);
		void AddPhysicalObject(std::shared_ptr<PhysicalObject> object);
		void AddInputRegister(std::shared_ptr<InputListener> object);
		bool OnUserCreate() override;
		bool OnUserUpdate(float fElapsedTime) override;

	private:
		PhysicsEngine _physics_engine;
		std::list<std::shared_ptr<InputListener>> _input_listeners;
		std::list<std::shared_ptr<DrawingObject>> _drawing_objects;
	};
}
