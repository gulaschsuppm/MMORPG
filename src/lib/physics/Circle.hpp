#pragma once
#include "Vector.hpp"
#include "RigidBody.hpp"

namespace MMORPG
{
    class Circle : public RigidBody
    {
    public:
        Circle() : RigidBody({ 0.0f,0.0f }), _radius(0.0f) {}

        Circle(Vector pos, float r) : RigidBody(pos), _radius(r) {}

        float GetRadius() const { return _radius; }
        void SetRadius(float r) { _radius = r; }

        Vector GetCenter() const { return GetPosition(); }

    private:
        float _radius;
    };
}