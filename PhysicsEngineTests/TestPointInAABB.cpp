#include "pch.h"
#include "../src/lib/physics/IntersectionDetector.hpp"

TEST(PointInAABB, R)
{
    using namespace MMORPG;

    {
        Vector point = {};
        AABB aabb = {};

        bool in_aabb = IntersectionDetector::PointInAABB(point, aabb);
        EXPECT_TRUE(in_aabb);
    }

    {
        Vector point = { 2,2 };
        AABB aabb = { point, 2,2};

        bool in_aabb = IntersectionDetector::PointInAABB(point, aabb);
        EXPECT_TRUE(in_aabb);
    }

    // Do not want to test excpetion handling here
    //{
    //    Vector min = {};
    //    Vector max = { 5,5 };
    //    AABB aabb = { max, min };
    //    Vector point = { 2,2 };

    //    EXPECT_ANY_THROW(IntersectionDetector::PointInAABB(point, aabb));
    //}

    {
        AABB aabb = { {0,0}, 5,5 };
        Vector point = { 6,6 };

        bool in_aabb = IntersectionDetector::PointInAABB(point, aabb);
        EXPECT_FALSE(in_aabb);
    }

    {
        AABB aabb = { {0,0}, 5,5 };
        Vector point = { -2,-2 };

        bool in_aabb = IntersectionDetector::PointInAABB(point, aabb);
        EXPECT_TRUE(in_aabb);
    }

    {
        AABB aabb = { {0,0}, 5,5 };
        Vector point = { -3,-2 };

        bool in_aabb = IntersectionDetector::PointInAABB(point, aabb);
        EXPECT_FALSE(in_aabb);
    }
}
