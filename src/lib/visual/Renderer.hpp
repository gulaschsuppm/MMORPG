#pragma once
#include "olcPixelGameEngine.h"
#include "Shape.hpp"

namespace MMORPG
{
    class Renderer
    {
    public:
        Renderer() : _origin() {}

        //void AddObject(Shape* object);

        void SetOrigin(olc::vf2d vec) { _origin = vec; }
        void SetProjection(olc::vf2d vec) { _projection = vec; }
        void Run(olc::PixelGameEngine* pge, std::list<Body*> objects);
    private:
        //olc::vf2d Renderer::Transform(olc::vf2d pos);

        //std::list<Shape*> _objects;
        olc::vf2d _origin;
        olc::vf2d _projection;
    };
}