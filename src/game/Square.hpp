#pragma once
#include "GameEngine.hpp"
#include "DrawingObject.hpp"
#include "Circle.hpp"

namespace MMORPG
{
    class Square : public DrawingObject, public Box
    {
    public:
        Square(Vector pos, float length, olc::Pixel color = olc::WHITE) :
            DrawingObject(color), Box(pos, length, length)
        {}

        Square(Vector pos, float rot, float length, olc::Pixel color = olc::WHITE) :
            DrawingObject(color), Box(pos, rot, length, length)
        {}

        virtual bool Draw(olc::vf2d origin, olc::PixelGameEngine* game_engine);
    };
}
