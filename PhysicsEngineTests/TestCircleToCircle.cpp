#include "pch.h"
#include "../src/lib/physics/IntersectionDetector.hpp"

TEST(CircleToCircle, Test)
{
    using namespace MMORPG;

    {
        Circle a = {};
        Circle b = {};

        bool touch = IntersectionDetector::CircleToCircle(a, b);
        EXPECT_TRUE(touch);
    }

    {
        Circle a = { {0,0},0 };
        Circle b = { {2,2},0 };

        bool touch = IntersectionDetector::CircleToCircle(a, b);
        EXPECT_FALSE(touch);
    }

    {
        Circle a = { {0,0},2 };
        Circle b = { {0,2},0 };

        bool touch = IntersectionDetector::CircleToCircle(a, b);
        EXPECT_TRUE(touch);
    }

    {
        Circle a = { {0,0},1 };
        Circle b = { {2,2},1 };

        bool touch = IntersectionDetector::CircleToCircle(a, b);
        EXPECT_FALSE(touch);
    }

    {
        Circle a = { {0,0},2 };
        Circle b = { {2,2},1 };

        bool touch = IntersectionDetector::CircleToCircle(a, b);
        EXPECT_TRUE(touch);
    }

    {
        Circle a = { {0,0},2 };
        Circle b = { {2,2},1 };

        bool touch = IntersectionDetector::CircleToCircle(b, a);
        EXPECT_TRUE(touch);
    }

    {
        Circle a = { {0,0},1 };
        Circle b = { {2,2},1 };

        bool touch = IntersectionDetector::CircleToCircle(b, a);
        EXPECT_FALSE(touch);
    }
}
