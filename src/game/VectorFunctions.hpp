#pragma once
#include "olcPixelGameEngine.h"

namespace MMORPG
{
    class VectorFunctions
    {
    public:
        static bool OutOfBounds(olc::vf2d pos, olc::vf2d bounds)
        {
            if ((pos.x > bounds.x || pos.x < 0) || (pos.y > bounds.y || pos.y < 0))
            {
                return true;
            }
            return false;
        }
    };
}
