#pragma once
#include "Vector.hpp"
#include <string>

namespace MMORPG
{
    struct Shape;

    struct Body
    {
        Body(Shape* shape_, Vector pos);

        void ApplyForce(const Vector& f)
        {
            force += f;
        }

        void ApplyImpulse(const Vector& impulse, const Vector& contactVector)
        {
            velocity += impulse * im;
            angularVelocity += iI * contactVector.cross(impulse);
        }

        void SetStatic(void)
        {
            I = 0.0f;
            iI = 0.0f;
            m = 0.0f;
            im = 0.0f;
        }

        void SetOrient(float radians);

        Vector position;
        Vector velocity;

        float angularVelocity;
        float torque;
        float orient; // radians

        std::string name;

        Vector force;

        // Set by shape
        float I;  // moment of inertia
        float iI; // inverse inertia
        float m;  // mass
        float im; // inverse mass

        // http://gamedev.tutsplus.com/tutorials/implementation/how-to-create-a-custom-2d-physics-engine-friction-scene-and-jump-table/
        float staticFriction;
        float dynamicFriction;
        float restitution;

        // Shape interface
        Shape* shape;

        // Store a color in RGB format
        float r, g, b;
    };
}
