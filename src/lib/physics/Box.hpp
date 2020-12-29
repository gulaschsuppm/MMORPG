#pragma once
#include "Vector.hpp"
#include "AABB.hpp"
#include <vector>
#include "Utils.hpp"

namespace MMORPG
{
    class Box : public RigidBody
    {
    public:
        Box() :
            RigidBody(), _length(), _height()
        {}

        Box(Vector pos, float l, float h) :
            RigidBody(pos), _length(l), _height(h)
        {

        }

        Box(Vector vec, float rot, float l, float h) :
            RigidBody(vec, rot), _length(l), _height(h)
        {

        }

        Vector GetMin() const
        {
            Vector min = { GetPosition().x - (_length / 2.0f), GetPosition().y - (_height / 2.0f) };
            return min;
        }

        Vector GetMax() const
        {
            Vector max = { GetPosition().x + (_length / 2.0f), GetPosition().y + (_height / 2.0f) };
            return max;
        }

        std::vector<Vector> GetVertices() const
        {
            auto min = GetMin();
            auto max = GetMax();

            std::vector<Vector> vertices;

            Vector a = min;
            Vector b = { min.x, max.y };
            Vector c = { max.x, min.y };
            Vector d = max;

            if (!Utils::Compare(GetRotation(), 0.0f))
            {
                a = Utils::Rotate(a, GetRotation(), GetPosition());
                b = Utils::Rotate(b, GetRotation(), GetPosition());
                c = Utils::Rotate(c, GetRotation(), GetPosition());
                d = Utils::Rotate(d, GetRotation(), GetPosition());
            }

            vertices.push_back(a);
            vertices.push_back(b);
            vertices.push_back(c);
            vertices.push_back(d);

            return vertices;
        }

    private:
        float _length;
        float _height;
    };
}