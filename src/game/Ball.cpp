#include "Ball.hpp"

namespace MMORPG
{
    bool Ball::Draw(olc::vf2d origin, olc::PixelGameEngine* game_engine)
    {
        olc::vf2d center = { GetPosition().x , GetPosition().y };
        game_engine->DrawCircle((origin + center), int(GetRadius()), _color);
        return true;
    }
}
