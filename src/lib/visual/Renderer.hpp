#pragma once
#include "olcPixelGameEngine.h"
#include "Circle.hpp"
#include "AABB.hpp"
#include "Box.hpp"

namespace MMORPG
{
    class Renderer
    {
    public:
        Renderer(olc::PixelGameEngine* game_engine) : pge(game_engine) {}
        void Draw(const Circle& circle, olc::Pixel color);
        void Draw(const AABB& aabb, olc::Pixel color);
        void Draw(const Box& box, olc::Pixel color);
    private:
        olc::PixelGameEngine* pge;
    };
}