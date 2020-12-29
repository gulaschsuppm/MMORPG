#pragma once
#include "GameEngine.hpp"
#include "DrawingObject.hpp"
#include "Circle.hpp"

namespace MMORPG
{
    class Ball : public DrawingObject, public Circle
    {
    public:
        Ball(Vector pos, float radius, olc::Pixel color = olc::WHITE) :
            DrawingObject(color), Circle(pos, radius)
        {}

        virtual bool Draw(olc::vf2d origin, olc::PixelGameEngine* game_engine);
    };
}
