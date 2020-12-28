#pragma once
#include "Vector.hpp"
#include "RigidBody.hpp"
#include <vector>

namespace MMORPG
{
    class Box
    {
        Box() :
            _size(), _half_size()
        {}

        Box(const Vector& min, const Vector& max) :
            _size(min - max), _half_size(_size / 2.0f)
        { }

        Vector GetMin() const
        {
            return (_rigid_body.GetPosition() - _half_size);
        }

        Vector GetMax() const
        {
            return (_rigid_body.GetPosition() + _half_size);
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
            if (_rigid_body.GetPosition() != 0.0f)
            {
                for (auto vec : vertices)
                {
                    // TODO: Rotate the vertices by rotation (degrees)
                }
            }

            return vertices;
        }

    private:
        Vector _size;
        Vector _halfsize;
        RigidBody _rigid_body;
    };
}