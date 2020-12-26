#pragma once
#include "GameObject.hpp"

namespace MMORPG
{
    class Ball : public GameObject
    {
    public:
        Ball(int x, int y);
        virtual bool OnUserCreate();
        virtual bool OnUserUpdate(olc::PixelGameEngine* pge);
    private:
        olc::vf2d position;
    };
}
