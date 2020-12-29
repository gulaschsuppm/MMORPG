#pragma once
#include "Vector.hpp"

namespace MMORPG
{
    class RigidBody
    {
    public:
        RigidBody() : _position(), _rotation(0.0f), _force({ 0.0f,0.0f }) {}

        RigidBody(Vector vec, float rot = 0.0f) : _position(vec), _rotation(rot), _force({ 0.0f,0.0f }) {}

        Vector GetPosition() const { return _position; }
        void SetPosition(Vector pos) { _position = pos; }
        float GetRotation() const { return _rotation; }
        void SetRotation(float rot)
        {
            rot = findMod(rot, 360.0f);
            _rotation = rot;
        }

        Vector GetForce() const { return _force; }
        void SetForce(Vector force) { _force = force; }
        void Accelerate(Vector force) { _force += force; }
        void Brake(Vector force) { _force -= force; }
    protected:
        Vector _position;
        float _rotation;

        Vector _force;

    private:
        float findMod(float a, float b)
        {
            float mod;
            // Handling negative values
            if (a < 0)
                mod = -a;
            else
                mod = a;
            if (b < 0)
                b = -b;

            // Finding mod by repeated subtraction

            while (mod >= b)
                mod = mod - b;

            // Sign of result typically depends
            // on sign of a.
            if (a < 0)
                return -mod;

            return mod;
        }
    };
}