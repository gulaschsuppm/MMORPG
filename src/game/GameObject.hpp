#pragma once
#include "olcPixelGameEngine.h"

namespace MMORPG
{
    class GameEngine;
}

namespace MMORPG
{
    class GameObject
    {
    public:
        GameObject(float x, float y, olc::Pixel color = olc::WHITE, float x_traj = 0.0f, float y_tray = 0.0f) :
            _position(x, y),
            _color(color),
            _trajectory(x_traj, y_tray)
        {}

        GameObject(olc::vf2d pos, olc::Pixel color = olc::WHITE, olc::vf2d traj = { 0.0f,0.0f }) :
            _position(pos),
            _color(color),
            _trajectory(traj)
        {}

        virtual bool OnUserCreate() = 0;
        virtual bool OnUserUpdate(float fElapsedTime, GameEngine* game_engine) = 0;
        olc::vf2d GetPosition() { return _position; }

    protected:
        olc::vf2d _position;
        olc::vf2d _trajectory;
        olc::Pixel _color;
    };
}