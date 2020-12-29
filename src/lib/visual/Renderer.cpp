#include "Renderer.hpp"

namespace MMORPG
{
    void Renderer::AddObject(std::shared_ptr<DrawingObject> object)
    {
        _drawing_objects.push_back(object);
    }

    void Renderer::Draw(olc::PixelGameEngine* pge, olc::vf2d origin)
    {
        // Apply movement
        for (auto obj_it = _drawing_objects.begin(); obj_it != _drawing_objects.end(); ++obj_it)
        {
            (*obj_it)->Draw(origin, pge);
        }
    }

    //void Renderer::Draw(const AABB& aabb, olc::Pixel color)
    //{
    //    auto min = aabb.GetMin();
    //    auto max = aabb.GetMax();
    //    olc::vf2d start = { min.x, min.y };
    //    olc::vf2d size = { max.x - min.x, max.y - min.y };
    //    _pge->DrawRect(Transform(start), size, color);
    //}

    //void Renderer::Draw(const Box& box, olc::Pixel color)
    //{
    //    auto verticles = box.GetVertices();

    //    olc::vf2d a = { verticles[0].x, verticles[0].y };
    //    olc::vf2d b = { verticles[1].x, verticles[1].y };
    //    olc::vf2d c = { verticles[2].x, verticles[2].y };
    //    olc::vf2d d = { verticles[3].x, verticles[3].y };
    //    _pge->DrawLine(Transform(a), Transform(b), color);
    //    _pge->DrawLine(Transform(a), Transform(c), color);
    //    _pge->DrawLine(Transform(b), Transform(d), color);
    //    _pge->DrawLine(Transform(c), Transform(d), color);
    //}
}