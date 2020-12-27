#include "Ball.hpp"
#include "VectorFunctions.hpp"

namespace MMORPG
{
    bool Ball::Draw(olc::PixelGameEngine* game_engine)
    {
        game_engine->FillCircle(_position, 3, _color);
        return true;
    }
}
