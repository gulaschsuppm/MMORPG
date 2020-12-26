#include "Ball.hpp"

namespace MMORPG
{
    Ball::Ball(int x, int y) :
        position(x, y)
    {

    }

    bool Ball::OnUserCreate()
    {
        return true;
    }

    bool Ball::OnUserUpdate(olc::PixelGameEngine* pge)
    {
        pge->FillCircle(position, 3);
        return true;
    }
}
