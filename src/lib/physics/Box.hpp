#pragma once
#include "Vector.hpp"
#include "RigidBody.hpp"
#include <vector>

namespace MMORPG
{
    class Box
    {
    public:
        Box() :
            _size(), _halfsize(), _rigid_body(new RigidBody())
        {}

        Box(const Vector& min, const Vector& max) :
            _size(min - max), _halfsize(_size / 2.0f), _rigid_body(new RigidBody())
        { }

        Vector GetMin() const
        {
            return (_rigid_body->GetPosition() - _halfsize);
        }

        Vector GetMax() const
        {
            return (_rigid_body->GetPosition() + _halfsize);
        }

        std::vector<Vector> GetVertices() const
        {
            auto min = GetMin();
            auto max = GetMax();

            std::vector<Vector> vertices;

            vertices.push_back(min);
            vertices.push_back({ min.x, max.y });
            vertices.push_back({ max.x, min.y });
            vertices.push_back(max);

            // TODO: Do not compare in floating point!
            if (_rigid_body->GetRotation() != 0.0f)
            {
                for (auto vec : vertices)
                {
                    // TODO: Rotate the vertices by rotation (degrees)
                }
            }

            return vertices;
        }

        void SetRigidBody(RigidBody* rb) { _rigid_body = rb; }

        RigidBody* GetRigidBody() const { return _rigid_body; }

    private:
        Vector _size;
        Vector _halfsize;
        RigidBody* _rigid_body;
    };
}