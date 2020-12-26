#pragma once
#include "olcPixelGameEngine.h"

namespace MMORPG
{
    class GameObject
    {
    public:
        GameObject() = default;

        virtual bool OnUserCreate() = 0;
        virtual bool OnUserUpdate(olc::PixelGameEngine* pge) = 0;
    protected:
        //virtual ~GameObject() {}
    };
}