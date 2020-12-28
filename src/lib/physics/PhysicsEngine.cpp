#include "PhysicsEngine.hpp"
#include "Vector.hpp"

namespace MMORPG
{
    void PhysicsEngine::AddObject(std::shared_ptr<PhysicalObject> object)
    {
        _physical_objects.push_back(object);
    }

    void PhysicsEngine::Run(float elapsed_time)
    {
        // Apply movement
        for (auto physical_obj_it = _physical_objects.begin(); physical_obj_it != _physical_objects.end(); ++physical_obj_it)
        {
            auto obj = *physical_obj_it;
            auto traj = obj->GetTrajectory();
            // Apply gravity
            Vector gravity = { 0.0f, 100.0f };
            traj += (gravity * elapsed_time);
            obj->SetTrajectory(traj);
            traj = obj->GetTrajectory();
            auto pos = obj->GetPosition();
            obj->SetPosition(pos + (traj * elapsed_time));
        }
    }
}