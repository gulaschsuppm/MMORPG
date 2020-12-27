#pragma once
#include "olcPixelGameEngine.h"

namespace MMORPG
{
    class DrawingObject
    {
    public:
        DrawingObject(olc::Pixel color = olc::WHITE) :
            _color(color)
        {}

        virtual bool Draw(olc::PixelGameEngine* game_engine) = 0;

    protected:
        olc::Pixel _color;
    };
}