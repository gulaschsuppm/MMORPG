#pragma once
#include "Vector.hpp"

namespace MMORPG
{
    class PhysicalObject
    {
    public:
        PhysicalObject(Vector pos, Vector traj = { 0.0f, 0.0f }) :
            _position(pos),
            _trajectory(traj)
        {}
        Vector GetPosition() const { return _position; }
        void SetPosition(const Vector& pos) { _position = pos; }
        Vector GetTrajectory() const { return _trajectory; }
        void SetTrajectory(const Vector& traj) { _trajectory = traj; }

        void ApplyForce(const Vector& force) { _trajectory += force; }

    protected:
        Vector _position;
        Vector _trajectory;
    };
}