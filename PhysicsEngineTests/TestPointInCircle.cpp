#include "pch.h"
#include "../src/lib/physics/IntersectionDetector.hpp"

TEST(PointInCircle, R)
{
    using namespace MMORPG;

    Vector point = {};
    Circle circle = {};

    bool in_circle = IntersectionDetector::PointInCircle(point, circle);
    EXPECT_TRUE(in_circle);

    circle.SetRadius(3.0f);
    point.x = 3.0f;
    in_circle = IntersectionDetector::PointInCircle(point, circle);
    EXPECT_TRUE(in_circle);

    circle.SetRadius(3.0f);
    point.x = -3.0f;
    in_circle = IntersectionDetector::PointInCircle(point, circle);
    EXPECT_TRUE(in_circle);

    circle.SetRadius(3.0f);
    point.x = 4.0f;
    in_circle = IntersectionDetector::PointInCircle(point, circle);
    EXPECT_FALSE(in_circle);
}
