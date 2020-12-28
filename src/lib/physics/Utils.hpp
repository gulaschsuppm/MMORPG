#pragma once
#include "Vector.hpp"
#include <math.h>
#include <float.h>

namespace MMORPG
{
    class Utils
    {
    public:
        static float ToRadians(float degree)
        {
            const float pi = 3.141592654f;
            return (degree * (pi / 180.0f));
        }

        // Rotate an vector around an origin:
        // x' = x * cos(theta) - y * sin(theta)
        // y' = x * sin(theta) + y * cos(theta)
        static Vector Rotate(const Vector& vec, float angle_deg, const Vector& origin)
        {
            // Move to world origin
            auto moved = vec - origin;

            float cosine = cosf(ToRadians(angle_deg));
            float sine = sinf(ToRadians(angle_deg));

            float x_prime = (moved.x * cosine) - (moved.y * sine);
            float y_prime = (moved.x * sine) + (moved.y * cosine);

            return (Vector(x_prime, y_prime) + origin);
        }

        static bool Compare(float x, float y, float epsilon)
        {
            return abs(x - y) <= (epsilon * fmax(1.0f , fmax(fabs(x), fabs(y))));
        }

        static bool Compare(const Vector& a, const Vector& b, float epsilon)
        {
            return (Compare(a.x, b.x, epsilon) && Compare(a.y, b.y, epsilon));
        }

        static bool Compare(float x, float y)
        {
            return abs(x - y) <= (FLT_MIN * fmax(1.0f, fmax(fabs(x), fabs(y))));
        }

        static bool Compare(const Vector& a, const Vector& b)
        {
            return (Compare(a.x, b.x) && Compare(a.y, b.y));
        }
    };
}