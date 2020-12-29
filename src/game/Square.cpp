#include "Square.hpp"

namespace MMORPG
{
    bool Square::Draw(olc::vf2d origin, olc::PixelGameEngine* game_engine)
    {
        auto verticles = GetVertices();

        olc::vf2d a = { verticles[0].x, verticles[0].y };
        olc::vf2d b = { verticles[1].x, verticles[1].y };
        olc::vf2d c = { verticles[2].x, verticles[2].y };
        olc::vf2d d = { verticles[3].x, verticles[3].y };
        game_engine->DrawLine(origin + a, origin + b, _color);
        game_engine->DrawLine(origin + a, origin + c, _color);
        game_engine->DrawLine(origin + b, origin + d, _color);
        game_engine->DrawLine(origin + c, origin + d, _color);

        return true;
    }
}
