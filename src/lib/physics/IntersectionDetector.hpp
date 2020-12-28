#pragma once
#include "Vector.hpp"
#include "Line.hpp"
#include "Circle.hpp"
#include "AABB.hpp"

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

        //static bool PointInBox(const Vector& point, const Box& box)
        //{
        //    auto min = aabb.GetMin();
        //    auto max = aabb.GetMax();

        //    return ((point.x >= min.x && point.x <= max.x) && (point.y >= min.y && point.y <= max.y));
        //}
    };
}