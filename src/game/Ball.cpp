#include "Ball.hpp"

namespace MMORPG
{
    bool Ball::Draw(olc::PixelGameEngine* game_engine)
    {
        auto pos = Project(game_engine, _position.x, _position.y);
        game_engine->FillCircle(pos, 3, _color);
        return true;
    }
}
