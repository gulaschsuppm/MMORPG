#pragma once
#include "Body.hpp"
#include <memory>
#include <list>

namespace MMORPG
{
    constexpr float engine_dt = 0.01f;

    class PhysicsEngine
    {
    public:
        PhysicsEngine() : acc_time(0.0f) {}
        //void AddObject(Body* object);

        void Run(std::list<Body*>& objects, float dt);
    private:
        float acc_time;
        //std::list<Body*> _physical_objects;
    };
}