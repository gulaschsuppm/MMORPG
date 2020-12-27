#pragma once
#include "GameEngine.hpp"
#include "GameObject.hpp"

namespace MMORPG
{
    class Ball : public GameObject
    {
    public:
        Ball(float x, float y, olc::Pixel color = olc::WHITE, float x_traj = 0.0f, float y_traj = 0.0f) :
            GameObject(x, y, color, x_traj, y_traj)
        {}

        Ball(olc::vf2d pos, olc::Pixel color = olc::WHITE, olc::vf2d traj = { 0.0f,0.0f }) :
            GameObject(pos, color, traj)
        {}

        virtual bool OnUserCreate();
        virtual bool OnUserUpdate(float fElapsedTime, GameEngine* game_engine);
    };
}
