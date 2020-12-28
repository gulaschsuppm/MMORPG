#pragma once
#include "Vector.hpp"

namespace MMORPG
{
    class RigidBody
    {
    public:
        RigidBody() : _position(), _rotation(0.0f) {}

        RigidBody(Vector vec, float rot = 0.0f) : _position(vec), _rotation(rot) {}

        Vector GetPosition() const { return _position; }
        float GetRotation() const { return _rotation; }
    protected:
        Vector _position;
        float _rotation;
    };
}