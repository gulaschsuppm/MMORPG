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

        virtual olc::vf2d Project(olc::PixelGameEngine* game_engine, float x, float y)
        {
            olc::vf2d origin = {float(game_engine->ScreenWidth()) / 2.0f, float(game_engine->ScreenHeight()) / 2.0f };
            olc::vf2d physical_pos = { x, y };

            return (origin + physical_pos);
        }

    protected:
        olc::Pixel _color;
    };
}