#pragma once
#include "Vector.hpp"
#include <stdint.h>

namespace MMORPG
{
    struct Body;

    // http://gamedev.tutsplus.com/tutorials/implementation/create-custom-2d-physics-engine-aabb-circle-impulse-resolution/
    struct Manifold
    {
        Manifold(Body* a, Body* b)
            : A(a)
            , B(b)
        {
        }

        void Solve(void);                 // Generate contact information
        void Initialize(float dt);            // Precalculations for impulse solving
        void ApplyImpulse(void);          // Solve impulse and apply
        void PositionalCorrection(void);  // Naive correction of positional penetration
        void InfiniteMassCorrection(void);

        Body* A;
        Body* B;

        float penetration;     // Depth of penetration from collision
        Vector normal;          // From A to B
        Vector contacts[2];     // Points of contact during collision
        uint32_t contact_count; // Number of contacts that occured during collision
        float e;               // Mixed restitution
        float df;              // Mixed dynamic friction
        float sf;              // Mixed static friction
    };
}
