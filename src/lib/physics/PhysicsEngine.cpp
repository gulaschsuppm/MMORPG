#include "PhysicsEngine.hpp"
#include "Vector.hpp"
#include "Manifold.hpp"
#include "Utils.hpp"

namespace MMORPG
{
    void PhysicsEngine::AddObject(Body* object)
    {
        _physical_objects.push_back(object);
    }

    void IntegrateForces(Body* b, float dt)
    {
        if (b->im == 0.0f)
            return;

        b->velocity += (b->force * b->im + gravity) * (dt / 2.0f);
        b->angularVelocity += b->torque * b->iI * (dt / 2.0f);
    }

    void IntegrateVelocity(Body* b, float dt)
    {
        if (b->im == 0.0f)
            return;

        b->position += b->velocity * dt;
        b->orient += b->angularVelocity * dt;
        b->SetOrient(b->orient);
        IntegrateForces(b, dt);
    }

    void PhysicsEngine::Run(float elapsed_time)
    {
        acc_time += elapsed_time;
        if (acc_time > engine_dt)
        {
            acc_time -= engine_dt;
            std::vector<Manifold> contacts;
            for (uint32_t i = 0; i < _physical_objects.size(); ++i)
            {
                Body* A = _physical_objects[i];

                for (uint32_t j = i + 1; j < _physical_objects.size(); ++j)
                {
                    Body* B = _physical_objects[j];
                    if (A->im == 0 && B->im == 0)
                        continue;
                    Manifold m(A, B);
                    m.Solve();
                    if (m.contact_count)
                        contacts.emplace_back(m);
                }
            }

            // Integrate forces
            for (uint32_t i = 0; i < _physical_objects.size(); ++i)
                IntegrateForces(_physical_objects[i], engine_dt);

            // Initialize collision
            for (uint32_t i = 0; i < contacts.size(); ++i)
                contacts[i].Initialize(engine_dt);

            // Solve collisions
            for (uint32_t j = 0; j < 10; ++j)
                for (uint32_t i = 0; i < contacts.size(); ++i)
                    contacts[i].ApplyImpulse();

            // Integrate velocities
            for (uint32_t i = 0; i < _physical_objects.size(); ++i)
                IntegrateVelocity(_physical_objects[i], engine_dt);

            // Correct positions
            for (uint32_t i = 0; i < contacts.size(); ++i)
                contacts[i].PositionalCorrection();

            // Clear all forces
            for (uint32_t i = 0; i < _physical_objects.size(); ++i)
            {
                Body* b = _physical_objects[i];
                b->force = { 0, 0 };
                b->torque = 0;
            }
        }
    }
}