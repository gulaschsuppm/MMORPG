#pragma once
#include "GameEngine.hpp"
#include "DrawingObject.hpp"
#include "PhysicalObject.hpp"

namespace MMORPG
{
    class Ball : public DrawingObject, public PhysicalObject
    {
    public:
        Ball(olc::vf2d pos, olc::Pixel color = olc::WHITE, olc::vf2d traj = { 0.0f,0.0f }) :
            DrawingObject(color), PhysicalObject(pos, traj)
        {}

        virtual bool Draw(olc::PixelGameEngine* game_engine);
    };
}
