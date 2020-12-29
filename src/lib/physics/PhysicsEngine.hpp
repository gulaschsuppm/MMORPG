#pragma once
#include "RigidBody.hpp"
#include <memory>
#include <list>

namespace MMORPG
{
    class PhysicsEngine
    {
    public:
        void AddObject(std::shared_ptr<RigidBody> object);

        void Run(float elapsed_time);
    private:
        std::list<std::shared_ptr<RigidBody>> _physical_objects;
    };
}