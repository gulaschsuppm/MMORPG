#pragma once
#include "Vector.hpp"
#include "RigidBody.hpp"

namespace MMORPG
{
    class AABB : public RigidBody
    {
    public:
        AABB() :
            RigidBody(), _length(), _height()
        {}

        AABB(Vector pos, float l, float h) : 
            RigidBody(pos), _length(l), _height(h)
        {

        }

        Vector GetMin() const
        {
            Vector min = {GetPosition().x - (_length / 2.0f), GetPosition().y - (_height / 2.0f)};
            return min;
        }

        Vector GetMax() const
        {
            Vector max = { GetPosition().x + (_length / 2.0f), GetPosition().y + (_height / 2.0f) };
            return max;
        }

    private:
        float _length;
        float _height;
    };
}