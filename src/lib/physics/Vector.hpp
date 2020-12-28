#pragma once
#include <math.h>

namespace MMORPG
{
    struct Vector
    {
        float x;
        float y;

        Vector() : x(0), y(0) {}
        Vector(float x, float y) : x(x), y(y) {}
        Vector(const Vector& v) : x(v.x), y(v.y) {}
        // Default move operator
        Vector& operator=(const Vector& v) = default;

        Vector  operator +  (const Vector& rhs) const { return Vector(this->x + rhs.x, this->y + rhs.y); }
        Vector  operator -  (const Vector& rhs) const { return Vector(this->x - rhs.x, this->y - rhs.y); }
        Vector  operator *  (const float& rhs)           const { return Vector(this->x * rhs, this->y * rhs); }
        Vector  operator *  (const Vector& rhs) const { return Vector(this->x * rhs.x, this->y * rhs.y); }
        Vector  operator /  (const float& rhs)           const { return Vector(this->x / rhs, this->y / rhs); }
        Vector  operator /  (const Vector& rhs) const { return Vector(this->x / rhs.x, this->y / rhs.y); }
        Vector& operator += (const Vector& rhs) { this->x += rhs.x; this->y += rhs.y; return *this; }
        Vector& operator -= (const Vector& rhs) { this->x -= rhs.x; this->y -= rhs.y; return *this; }
        Vector& operator *= (const float& rhs) { this->x *= rhs; this->y *= rhs; return *this; }
        Vector& operator /= (const float& rhs) { this->x /= rhs; this->y /= rhs; return *this; }
        Vector  operator +  () const { return { +x, +y }; }
        Vector  operator -  () const { return { -x, -y }; }
        bool operator == (const Vector& rhs) const { return (this->x == rhs.x && this->y == rhs.y); }
        bool operator != (const Vector& rhs) const { return (this->x != rhs.x || this->y != rhs.y); }

        // Pythagoras: SQRT(X2 + Y2). Minimize use of this!
        float length() const { return (sqrtf((x * x) + (y * y))); }
        float length2() const { return ((x * x) + (y * y)); }

        Vector unit() const { float r = length();  return Vector(x / r, y / r); }

        float dot(const Vector& v) const { return ((this->x * v.x) + (this->y * v.y)); }

        float cross(const Vector& v) const { return ((this->x * v.y) - (this->y * v.x)); }

        // If the dot product of the unit vectors is 1, then they are parallel
        bool parallel(const Vector& v) const { return (this->unit().dot(v.unit()) == 1.0f); }
        // If the dot product of the unit vectors is 0, then they are perpendicular
        bool perp(const Vector& v) const { return (this->unit().dot(v.unit()) == 0.0f); }
    };
}
