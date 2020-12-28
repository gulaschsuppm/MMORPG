#pragma once
#include "Vector.hpp"

namespace MMORPG
{
    class RigidBody
    {
    public:
        RigidBody() : _position(), _rotation(0.0f) {}

        Vector GetPosition() const { return _position; }
    protected:
        Vector _position;
        float _rotation;
    };
}