#include "PhysicsEngine.hpp"
#include "Vector.hpp"
#include "IntersectionDetector.hpp"

namespace MMORPG
{
    void PhysicsEngine::AddObject(std::shared_ptr<RigidBody> object)
    {
        _physical_objects.push_back(object);
    }

    void PhysicsEngine::Run(float elapsed_time)
    {
        // Collision detection and force changes
        //for (auto focus = _physical_objects.begin(); focus != _physical_objects.end(); ++focus)
        //{
        //    for (auto secondary = _physical_objects.begin(); secondary != _physical_objects.end(); ++secondary)
        //    {
        //        IntersectionDetector::CircleToCircle();
        //    }
        //}

        // Apply movement
        for (auto physical_obj_it = _physical_objects.begin(); physical_obj_it != _physical_objects.end(); ++physical_obj_it)
        {
            auto obj = *physical_obj_it;
            // Apply gravity
            Vector gravity = { 0.0f, 100.0f };
            obj->Accelerate(gravity * elapsed_time);
            obj->SetPosition(obj->GetPosition() + (obj->GetForce() * elapsed_time));
            float rot = obj->GetRotation();
            rot = rot + 360.0f * elapsed_time;
            obj->SetRotation(rot);
        }
    }
}