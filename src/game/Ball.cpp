#include "Ball.hpp"

namespace MMORPG
{
    bool Ball::OnUserCreate()
    {
        return true;
    }

    bool Ball::OnUserUpdate(float fElapsedTime, olc::PixelGameEngine* pge)
    {
        _position += (_trajectory * fElapsedTime);
        pge->FillCircle(_position, 3, _color);
        return true;
    }
}
