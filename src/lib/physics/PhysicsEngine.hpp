#pragma once
#include "Body.hpp"
#include <memory>
#include <vector>

namespace MMORPG
{
    constexpr float engine_dt = 0.01f;

    class PhysicsEngine
    {
    public:
        PhysicsEngine() : acc_time(0.0f) {}
        void AddObject(Body* object);

        void Run(float dt);
    private:
        float acc_time;
        std::vector<Body*> _physical_objects;
    };
}