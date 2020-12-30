#pragma once
#include "Vector.hpp"
#include <math.h>
#include <float.h>
#include <cstdlib>

namespace MMORPG
{
    constexpr float PI = 3.141592654f;
    constexpr float EPSILON = 0.0001f;
    //constexpr uint32_t RAND_MAX = 0x7FFF;
    const Vector gravity(0, -10.0f);
    //const float dt = 1.0f / 60.0f;

    class Utils
    {
    public:
        static float Random(float l, float h)
        {
            float a = (float)rand();
            a /= RAND_MAX;
            a = (h - l) * a + l;
            return a;
        } 

        static float ToRadians(float degree)
        {
            //const float pi = 3.141592654f;
            return (degree * (PI / 180.0f));
        }

        static float ToDegrees(float rad)
        {
            //const float pi = 3.141592654f;
            return (rad * 180.0f) / PI;
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

        static float DistSqr(const Vector& a, const Vector& b)
        {
            Vector c = a - b;
            return c.dot(c);
        }

        static bool BiasGreaterThan(float a, float b)
        {
            const float k_biasRelative = 0.95f;
            const float k_biasAbsolute = 0.01f;
            return a >= b * k_biasRelative + a * k_biasAbsolute;
        }
    };

    struct Mat2
    {
        union
        {
            struct
            {
                float m00, m01;
                float m10, m11;
            };

            float m[2][2];
            float v[4];
        };

        Mat2() {}
        Mat2(float radians)
        {
            float c = cosf(radians);
            float s = sinf(radians);

            m00 = c; m01 = -s;
            m10 = s; m11 = c;
        }

        Mat2(float a, float b, float c, float d)
            : m00(a), m01(b)
            , m10(c), m11(d)
        {
        }

        void Set(float radians)
        {
            float c = cosf(radians);
            float s = sinf(radians);

            m00 = c; m01 = -s;
            m10 = s; m11 = c;
        }

        Mat2 Abs(void) const
        {
            return Mat2(abs(m00), abs(m01), abs(m10), abs(m11));
        }

        Vector AxisX(void) const
        {
            return Vector(m00, m10);
        }

        Vector AxisY(void) const
        {
            return Vector(m01, m11);
        }

        Mat2 Transpose(void) const
        {
            return Mat2(m00, m10, m01, m11);
        }

        const Vector operator*(const Vector& rhs) const
        {
            return Vector(m00 * rhs.x + m01 * rhs.y, m10 * rhs.x + m11 * rhs.y);
        }

        const Mat2 operator*(const Mat2& rhs) const
        {
            // [00 01]  [00 01]
            // [10 11]  [10 11]

            return Mat2(
                m[0][0] * rhs.m[0][0] + m[0][1] * rhs.m[1][0],
                m[0][0] * rhs.m[0][1] + m[0][1] * rhs.m[1][1],
                m[1][0] * rhs.m[0][0] + m[1][1] * rhs.m[1][0],
                m[1][0] * rhs.m[0][1] + m[1][1] * rhs.m[1][1]
            );
        }
    };
}