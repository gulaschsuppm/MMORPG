#pragma once
#include "olcPixelGameEngine.h"
#include "DrawingObject.hpp"
#include "RigidBody.hpp"
#include "InputListener.hpp"
#include "PhysicsEngine.hpp"
#include "Renderer.hpp"

namespace MMORPG
{
	class GameEngine : public olc::PixelGameEngine
	{
	public:
		GameEngine() { sAppName = "Game"; }

		void AddDrawingObject(std::shared_ptr<DrawingObject> object);
		void AddPhysicalObject(std::shared_ptr<RigidBody> object);
		void AddInputRegister(std::shared_ptr<InputListener> object);
		bool OnUserCreate() override;
		bool OnUserUpdate(float fElapsedTime) override;

	private:
		PhysicsEngine _physics_engine;
		Renderer _renderer;
		std::list<std::shared_ptr<InputListener>> _input_listeners;
		olc::vf2d origin;
	};
}
