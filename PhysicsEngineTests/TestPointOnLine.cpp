#include "pch.h"
#include "../src/lib/physics/IntersectionDetector.hpp"

TEST(PointOnLine, k1_d0)
{
    using namespace MMORPG;
    Vector point = {};
    Vector start = { 0.0f,0.0f };
    Vector end = { 5.0f,5.0f };
    Line line = {start, end};

    bool on_line = IntersectionDetector::PointOnLine(point, line);
    EXPECT_TRUE(on_line);

    point.x = 3.0f;
    point.y = 3.0f;
    on_line = IntersectionDetector::PointOnLine(point, line);
    EXPECT_TRUE(on_line);

    point.x = 5.0f;
    point.y = 5.0f;
    on_line = IntersectionDetector::PointOnLine(point, line);
    EXPECT_TRUE(on_line);

    point.x = -1.0f;
    point.y = -1.0f;
    on_line = IntersectionDetector::PointOnLine(point, line);
    EXPECT_TRUE(on_line);

    point.x = 3.0f;
    point.y = 4.0f;
    on_line = IntersectionDetector::PointOnLine(point, line);
    EXPECT_FALSE(on_line);

    point.x = 6.0f;
    point.y = 6.0f;
    on_line = IntersectionDetector::PointOnLine(point, line);
    EXPECT_TRUE(on_line);

    point.x = 3.0f;
    point.y = 3.0001f;
    on_line = IntersectionDetector::PointOnLine(point, line);
    EXPECT_FALSE(on_line);
}

TEST(PointOnLine, kneg1_d0)
{
    using namespace MMORPG;
    Vector point = {};
    Vector end = { 0.0f,0.0f };
    Vector start = { 5.0f,5.0f };
    Line line = { start, end };

    bool on_line = IntersectionDetector::PointOnLine(point, line);
    EXPECT_TRUE(on_line);

    point.x = 3.0f;
    point.y = 3.0f;
    on_line = IntersectionDetector::PointOnLine(point, line);
    EXPECT_TRUE(on_line);

    point.x = 5.0f;
    point.y = 5.0f;
    on_line = IntersectionDetector::PointOnLine(point, line);
    EXPECT_TRUE(on_line);

    point.x = -1.0f;
    point.y = -1.0f;
    on_line = IntersectionDetector::PointOnLine(point, line);
    EXPECT_TRUE(on_line);

    point.x = 3.0f;
    point.y = 4.0f;
    on_line = IntersectionDetector::PointOnLine(point, line);
    EXPECT_FALSE(on_line);

    point.x = 6.0f;
    point.y = 6.0f;
    on_line = IntersectionDetector::PointOnLine(point, line);
    EXPECT_TRUE(on_line);

    point.x = 3.0f;
    point.y = 3.0001f;
    on_line = IntersectionDetector::PointOnLine(point, line);
    EXPECT_FALSE(on_line);
}

TEST(PointOnLine, horizontal)
{
    using namespace MMORPG;
    Vector point = {};
    Vector start = { 1.5f,1.5f };
    Vector end = { 2.5f,1.5f };
    Line line = { start, end };

    point.x = 0.0f;
    point.y = 1.5f;
    bool on_line = IntersectionDetector::PointOnLine(point, line);
    EXPECT_TRUE(on_line);

    point.x = 3.5f;
    point.y = 1.5f;
    on_line = IntersectionDetector::PointOnLine(point, line);
    EXPECT_TRUE(on_line);

    point.x = 2.0f;
    point.y = 1.4f;
    on_line = IntersectionDetector::PointOnLine(point, line);
    EXPECT_FALSE(on_line);

    point.x = 3.0f;
    point.y = 4.0f;
    on_line = IntersectionDetector::PointOnLine(point, line);
    EXPECT_FALSE(on_line);

    point.x = 6.0f;
    point.y = 6.0f;
    on_line = IntersectionDetector::PointOnLine(point, line);
    EXPECT_FALSE(on_line);

    point.x = 3.0f;
    point.y = 1.5001f;
    on_line = IntersectionDetector::PointOnLine(point, line);
    EXPECT_FALSE(on_line);
}

TEST(PointOnLine, vertical)
{
    using namespace MMORPG;
    Vector point = {};
    Vector start = { 1.5f,1.5f };
    Vector end = { 1.5f,2.5f };
    Line line = { start, end };

    point.x = 1.5f;
    point.y = 0.0f;
    bool on_line = IntersectionDetector::PointOnLine(point, line);
    EXPECT_TRUE(on_line);

    point.x = 1.5f;
    point.y = 3.5f;
    on_line = IntersectionDetector::PointOnLine(point, line);
    EXPECT_TRUE(on_line);

    point.x = 1.4f;
    point.y = 1.4f;
    on_line = IntersectionDetector::PointOnLine(point, line);
    EXPECT_FALSE(on_line);

    point.x = 3.0f;
    point.y = 4.0f;
    on_line = IntersectionDetector::PointOnLine(point, line);
    EXPECT_FALSE(on_line);

    point.x = 6.0f;
    point.y = 6.0f;
    on_line = IntersectionDetector::PointOnLine(point, line);
    EXPECT_FALSE(on_line);

    point.x = 1.5001f;
    point.y = 7.0f;
    on_line = IntersectionDetector::PointOnLine(point, line);
    EXPECT_FALSE(on_line);
}
