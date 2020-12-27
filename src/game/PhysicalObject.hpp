#pragma once
#include "olcPixelGameEngine.h"

namespace MMORPG
{
    class PhysicalObject
    {
    public:
        PhysicalObject(olc::vf2d pos, olc::vf2d traj = { 0.0f, 0.0f }) :
            _position(pos),
            _trajectory(traj)
        {}
        olc::vf2d GetPosition() { return _position; }
        void SetPosition(olc::vf2d pos) { _position = pos; }
        olc::vf2d GetTrajectory() { return _trajectory; }
        void SetTrajectory(olc::vf2d traj) { _trajectory = traj; }
    protected:
        olc::vf2d _position;
        olc::vf2d _trajectory;
    };
}