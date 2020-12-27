#pragma once
#include "PhysicalObject.hpp"

namespace MMORPG
{
    class PhysicsEngine
    {
    public:
        void AddObject(std::shared_ptr<PhysicalObject> object);

        void Run(float elapsed_time);
    private:
        std::list<std::shared_ptr<PhysicalObject>> _physical_objects;
    };
}