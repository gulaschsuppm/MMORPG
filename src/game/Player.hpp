#pragma once
#include "GameEngine.hpp"
#include "InputListener.hpp"
#include "Ball.hpp"

namespace MMORPG
{
    class Player : public InputListener, public Ball
    {
    public:
        using Ball::Ball;

        virtual bool OnInput(GameEngine* game_engine);
    };
}