#pragma once
#include "GameObject.hpp"

namespace MMORPG
{
    class Ball : public GameObject
    {
    public:
        Ball(float x, float y, olc::Pixel color = olc::WHITE, float x_traj = 0.0f, float y_tray = 0.0f) :
            GameObject(x, y, color, x_traj, y_tray)
        {}
        virtual bool OnUserCreate();
        virtual bool OnUserUpdate(float fElapsedTime, olc::PixelGameEngine* pge);
    };
}
