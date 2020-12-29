#pragma once
#include "olcPixelGameEngine.h"
#include "Circle.hpp"
#include "AABB.hpp"
#include "Box.hpp"
#include "DrawingObject.hpp"

namespace MMORPG
{
    class Renderer
    {
    public:
        Renderer() {}

        void AddObject(std::shared_ptr<DrawingObject> object);

        void Draw(olc::PixelGameEngine* pge, olc::vf2d origin);
    private:
        std::list<std::shared_ptr<DrawingObject>> _drawing_objects;
    };
}