#pragma once
#include "Vector.hpp"
#include "RigidBody.hpp"

namespace MMORPG
{
    class Circle
    {
    public:
        Circle() : _radius(0.0f) {}

        float GetRadius() const { return _radius; }

        Vector GetCenter() const { return _rigid_body.GetPosition(); }
    protected:
        float _radius;
        RigidBody _rigid_body;
    };
}