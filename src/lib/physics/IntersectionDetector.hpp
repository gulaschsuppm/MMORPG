#pragma once
#include "Vector.hpp"
#include "Line.hpp"
#include "Circle.hpp"
#include "AABB.hpp"
#include "Box.hpp"
#include "Utils.hpp"

namespace MMORPG
{
    class IntersectionDetector
    {
    public:
        static bool PointOnLine(const Vector& point, const Line& line)
        {
            // y = k * x + d
            auto dy = line.end.y - line.start.y;
            auto dx = line.end.x - line.start.x;

            // Early exit for vertical lines
            if (dx == 0)
            {
                return (point.x == line.start.x);
            }

            auto k = dy / dx;

            auto d = line.end.y - (k * line.end.x);

            // Check if we can solve with the point now
            return (point.y == (k * point.x + d));
        }

        static bool PointInCircle(const Vector& point, const Circle& circle)
        {
            auto dist = point - circle.GetCenter();
            return (dist.length2() <= (circle.GetRadius() * circle.GetRadius()));
        }

        static bool PointInAABB(const Vector& point, const AABB& aabb)
        {
            auto min = aabb.GetMin();
            auto max = aabb.GetMax();

            return ((point.x >= min.x && point.x <= max.x) && (point.y >= min.y && point.y <= max.y));
        }

        static bool PointInBox(const Vector& point, const Box& box)
        {
            auto point_rotated = Utils::Rotate(point, box.GetRotation(), box.GetPosition());
            auto min = box.GetMin();
            auto max = box.GetMax();

            return ((point_rotated.x >= min.x && point_rotated.x <= max.x) && (point_rotated.y >= min.y && point_rotated.y <= max.y));
        }

        static bool CircleToCircle(const Circle& a, const Circle& b)
        {
            // Get vector from center a to center b
            Vector ray = b.GetPosition() - a.GetPosition();
            float dist2 = ray.length2();
            float radix2 = (a.GetRadius() + b.GetRadius()) * (a.GetRadius() + b.GetRadius());
            return (dist2 <= radix2);
        }
    };
}