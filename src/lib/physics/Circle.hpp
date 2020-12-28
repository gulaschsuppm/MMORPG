#pragma once
#include "Vector.hpp"
#include "RigidBody.hpp"

namespace MMORPG
{
    class Circle
    {
    public:
        Circle() : _radius(0.0f) {}

        Circle(float r) : _radius(r) {}

        float GetRadius() const { return _radius; }
        void SetRadius(float r) { _radius = r; }

        Vector GetCenter() const { return _rigid_body.GetPosition(); }
    protected:
        float _radius;
        RigidBody _rigid_body;
    };
}