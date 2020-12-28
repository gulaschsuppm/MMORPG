#pragma once
#include "Vector.hpp"
#include "RigidBody.hpp"

namespace MMORPG
{
    class AABB
    {
    public:
        AABB() :
            _size(), _half_size(), _rigid_body(new RigidBody())
        {}

        AABB(const Vector& min, const Vector& max) : 
            _size(max - min), _half_size(_size / 2.0f), _rigid_body(new RigidBody())
        {
            assert(max.x >= min.x && max.y >= min.y);
        }

        RigidBody* GetRigidBody() const { return _rigid_body; }

        Vector GetMin() const
        {
            return (_rigid_body->GetPosition() - _half_size);
        }

        Vector GetMax() const
        {
            return (_rigid_body->GetPosition() + _half_size);
        }

    private:
        Vector _size;
        Vector _half_size;
        RigidBody* _rigid_body;
    };
}