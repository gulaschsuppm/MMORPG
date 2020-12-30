#pragma once
#include "Manifold.hpp"
#include "Collision.hpp"
#include "Utils.hpp"

namespace MMORPG
{
    void Manifold::Solve(void)
    {
        Dispatch[A->shape->GetType()][B->shape->GetType()](this, A, B);
    }

    void Manifold::Initialize(float dt)
    {
        // Calculate average restitution
        e = std::min(A->restitution, B->restitution);

        // Calculate static and dynamic friction
        sf = std::sqrt(A->staticFriction * B->staticFriction);
        df = std::sqrt(A->dynamicFriction * B->dynamicFriction);

        for (uint32_t i = 0; i < contact_count; ++i)
        {
            // Calculate radii from COM to contact
            Vector ra = contacts[i] - A->position;
            Vector rb = contacts[i] - B->position;

            Vector rv = B->velocity + rb.cross(B->angularVelocity) - A->velocity - ra.cross(A->angularVelocity);

            // Determine if we should perform a resting collision or not
            // The idea is if the only thing moving this object is gravity,
            // then the collision should be performed without any restitution
            if (rv.mag2() < (gravity * dt).mag2() + EPSILON)
                e = 0.0f;
        }
    }

    void Manifold::ApplyImpulse(void)
    {
        // Early out and positional correct if both objects have infinite mass
        if (Utils::Compare(A->im + B->im, 0))
        {
            InfiniteMassCorrection();
            return;
        }

        for (uint32_t i = 0; i < contact_count; ++i)
        {
            // Calculate radii from COM to contact
            Vector ra = contacts[i] - A->position;
            Vector rb = contacts[i] - B->position;

            // Relative velocity
            Vector vel_b = B->velocity;
            Vector vel_a = A->velocity;
            if (B->isExplosion)
            {
                vel_b = normal * -100.0f;
            }
            if (A->isExplosion)
            {
                vel_a = normal * 100.0f;
            }
            Vector rv = vel_b + rb.cross(B->angularVelocity) - vel_a - ra.cross(A->angularVelocity);

            // Relative velocity along the normal
            float contactVel = rv.dot(normal);

            // Do not resolve if velocities are separating
            if (contactVel > 0)
                return;

            float raCrossN = ra.cross(normal);
            float rbCrossN = rb.cross(normal);
            float invMassSum = A->im + B->im + (raCrossN * raCrossN) * A->iI + (rbCrossN * rbCrossN) * B->iI;

            // Calculate impulse scalar
            float j = -(1.0f + e) * contactVel;
            j /= invMassSum;
            j /= (float)contact_count;

            // Apply impulse
            Vector impulse = normal * j;
            A->ApplyImpulse(-impulse, ra);
            B->ApplyImpulse(impulse, rb);

            // Friction impulse
            rv = B->velocity + rb.cross(B->angularVelocity) - A->velocity - ra.cross(A->angularVelocity);

            Vector t = rv - (normal * rv.dot(normal));
            t = t.norm();

            // j tangent magnitude
            float jt = -rv.dot(t);
            jt /= invMassSum;
            jt /= (float)contact_count;

            // Don't apply tiny friction impulses
            if (Utils::Compare(jt, 0.0f))
                return;

            // Coulumb's law
            Vector tangentImpulse;
            if (std::abs(jt) < j * sf)
                tangentImpulse = t * jt;
            else
                tangentImpulse = t * -j * df;

            // Apply friction impulse
            A->ApplyImpulse(-tangentImpulse, ra);
            B->ApplyImpulse(tangentImpulse, rb);
        }
    }

    void Manifold::PositionalCorrection(void)
    {
        const float k_slop = 0.05f; // Penetration allowance
        const float percent = 0.4f; // Penetration percentage to correct
        Vector correction = normal * (std::max(penetration - k_slop, 0.0f) / (A->im + B->im)) * percent;
        A->position -= correction * A->im;
        B->position += correction * B->im;
    }

    void Manifold::InfiniteMassCorrection(void)
    {
        A->velocity = { 0, 0 };
        B->velocity = { 0, 0 };
    }
}
