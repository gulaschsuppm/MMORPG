#include "Renderer.hpp"

namespace MMORPG
{
    void Renderer::Draw(const Circle& circle, olc::Pixel color)
    {
        olc::vf2d center = { circle.GetCenter().x , circle.GetCenter().y};
        pge->DrawCircle(center, circle.GetRadius(), color);
    }

    void Renderer::Draw(const AABB& aabb, olc::Pixel color)
    {
        olc::vf2d min = { aabb.GetMin().x, aabb.GetMin().y };
        olc::vf2d max = { aabb.GetMax().x, aabb.GetMax().y };
        pge->DrawRect(min, max, color);
    }

    void Renderer::Draw(const Box& box, olc::Pixel color)
    {
        auto verticles = box.GetVertices();

        olc::vf2d a = { verticles[0].x, verticles[0].y };
        olc::vf2d b = { verticles[1].x, verticles[1].y };
        olc::vf2d c = { verticles[2].x, verticles[2].y };
        olc::vf2d d = { verticles[3].x, verticles[3].y };
        pge->DrawLine(a, b, color);
        pge->DrawLine(b, c, color);
        pge->DrawLine(c, d, color);
        pge->DrawLine(d, a, color);
    }
}