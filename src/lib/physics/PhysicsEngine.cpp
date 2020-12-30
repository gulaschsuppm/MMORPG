#include "PhysicsEngine.hpp"
#include "Vector.hpp"
#include "Manifold.hpp"
#include "Utils.hpp"

namespace MMORPG
{
    //void PhysicsEngine::AddObject(Body* object)
    //{
    //    _physical_objects.push_back(object);
    //}

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

    void PhysicsEngine::Run(std::list<Body*>& objects, float dt)
    {
        acc_time += dt;
        if (acc_time > engine_dt)
        {
            acc_time -= engine_dt;
            std::vector<Manifold> contacts;
            for (auto body_a_it = objects.begin(); body_a_it != objects.end(); ++body_a_it)
            {
                Body* A = *body_a_it;

                for (auto body_b_it = next(body_a_it); body_b_it != objects.end(); ++body_b_it)
                {
                    Body* B = *body_b_it;
                    if (A->im == 0 && B->im == 0)
                        continue;
                    Manifold m(A, B);
                    m.Solve();
                    if (m.contact_count)
                        contacts.emplace_back(m);
                }
            }

            // Integrate forces
            for (auto body_a_it = objects.begin(); body_a_it != objects.end(); ++body_a_it)
            {
                IntegrateForces(*body_a_it, engine_dt);
            }

            // Initialize collision
            for (uint32_t i = 0; i < contacts.size(); ++i)
                contacts[i].Initialize(engine_dt);

            // Solve collisions
            for (uint32_t j = 0; j < 10; ++j)
                for (uint32_t i = 0; i < contacts.size(); ++i)
                    contacts[i].ApplyImpulse();

            // Integrate velocities
            for (auto body_a_it = objects.begin(); body_a_it != objects.end(); ++body_a_it)
            {
                IntegrateVelocity(*body_a_it, engine_dt);
            }

            // Correct positions
            for (uint32_t i = 0; i < contacts.size(); ++i)
                contacts[i].PositionalCorrection();

            // Clear all forces
            for (auto body_a_it = objects.begin(); body_a_it != objects.end(); ++body_a_it)
            {
                Body* b = *body_a_it;
                b->force = { 0, 0 };
                b->torque = 0;
            }
        }
    }
}