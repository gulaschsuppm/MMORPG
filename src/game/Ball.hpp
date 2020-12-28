#pragma once
#include "GameEngine.hpp"
#include "DrawingObject.hpp"
#include "PhysicalObject.hpp"

namespace MMORPG
{
    class Ball : public DrawingObject, public PhysicalObject
    {
    public:
        Ball(Vector pos, olc::Pixel color = olc::WHITE, Vector traj = { 0.0f,0.0f }) :
            DrawingObject(color), PhysicalObject(pos, traj)
        {}

        virtual bool Draw(olc::PixelGameEngine* game_engine);
    };
}
