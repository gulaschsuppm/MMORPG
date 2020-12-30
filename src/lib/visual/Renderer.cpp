#include "Renderer.hpp"

namespace MMORPG
{
    void Renderer::AddObject(Shape* object)
    {
        _objects.push_back(object);
    }

    olc::vf2d Renderer::Transform(olc::vf2d pos)
    {
        return (_origin + pos);
    }

    void Renderer::Run(olc::PixelGameEngine* pge)
    {
        for (auto focus = _objects.begin(); focus != _objects.end(); ++focus)
        {
            (*focus)->Draw(pge, _origin, _projection);
        }
    }

    //bool Renderer::DrawObject(olc::PixelGameEngine* pge, Body* body, Circle* circle)
    //{
    //    olc::vf2d center = { circle->GetPosition().x , circle->GetPosition().y };
    //    pge->DrawCircle(Transform(center), int(circle->GetRadius()), olc::WHITE);
    //    return true;
    //}

    //void Renderer::DrawObject(olc::PixelGameEngine* pge, Body* body, Box* box)
    //{
    //    auto verticles = box->GetVertices();

    //    olc::vf2d a = { verticles[0].x, verticles[0].y };
    //    olc::vf2d b = { verticles[1].x, verticles[1].y };
    //    olc::vf2d c = { verticles[2].x, verticles[2].y };
    //    olc::vf2d d = { verticles[3].x, verticles[3].y };
    //    pge->DrawLine(Transform(a), Transform(b), olc::WHITE);
    //    pge->DrawLine(Transform(a), Transform(c), olc::WHITE);
    //    pge->DrawLine(Transform(b), Transform(d), olc::WHITE);
    //    pge->DrawLine(Transform(c), Transform(d), olc::WHITE);
    //}
}