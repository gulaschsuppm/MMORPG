#pragma once
#include "Vector.hpp"

namespace MMORPG
{
    class Collider
    {
    public:
        //virtual float GetInertiaTensor(float mass) = 0;

    protected:
        Vector _offset;
    };
}