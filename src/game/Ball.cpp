#include "Ball.hpp"
#include "VectorFunctions.hpp"

namespace MMORPG
{
    bool Ball::OnUserCreate()
    {
        return true;
    }

    bool Ball::OnUserUpdate(float fElapsedTime, GameEngine* game_engine)
    {
        _position += (_trajectory * fElapsedTime);
        if (VectorFunctions::OutOfBounds(_position, { float(game_engine->ScreenWidth()), float(game_engine->ScreenHeight()) }))
        {
            return false;
        }
        else
        {
            game_engine->FillCircle(_position, 3, _color);
        }
        return true;
    }
}
