#pragma once
#include "Vector.hpp"
#include "RigidBody.hpp"

namespace MMORPG
{
    class AABB
    {
    public:
        AABB() :
            _size(), _half_size()
        {}

        AABB(const Vector& min, const Vector& max) : 
            _size(min - max), _half_size(_size / 2.0f)
        { }

        Vector GetMin() const
        {
            return (_rigid_body.GetPosition() - _half_size);
        }

        Vector GetMax() const
        {
            return (_rigid_body.GetPosition() + _half_size);
        }

    private:
        Vector _size;
        Vector _half_size;
        RigidBody _rigid_body;
    };
}