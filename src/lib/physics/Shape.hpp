#pragma once
#include "Vector.hpp"
#include "Body.hpp"
#include "Utils.hpp"
#include <stdint.h>
#include <assert.h>
#include <algorithm>
// TODO: Refactor out
#include "olcPixelGameEngine.h"

namespace MMORPG
{
    constexpr uint32_t MaxPolyVertexCount = 64;

    struct Shape
    {
        enum Type
        {
            eCircle,
            ePoly,
            eCount
        };

        Shape() {}
        virtual Shape* Clone(void) const = 0;
        virtual void Initialize(float density) = 0;
        virtual void ComputeMass(float density) = 0;
        virtual void SetOrient(float radians) = 0;
        virtual void Draw(olc::PixelGameEngine* pge, const olc::vf2d& origin, const olc::vf2d& proj) const = 0;
        virtual Type GetType(void) const = 0;

        Vector Transform(const Vector& pos, const Vector& ori, const Vector& proj) const
        {
            return ori + (pos * proj);
        }

        Body* body;

        // For circle shape
        float radius;

        // For Polygon shape
        Mat2 u; // Orientation matrix from model to world
    };

    struct Circle : public Shape
    {
        Circle(float r)
        {
            radius = r;
        }

        Shape* Clone(void) const
        {
            return new Circle(radius);
        }

        void Initialize(float density)
        {
            ComputeMass(density);
        }

        void ComputeMass(float density)
        {
            body->m = PI * radius * radius * density;
            body->im = (body->m) ? 1.0f / body->m : 0.0f;
            body->I = body->m * radius * radius;
            body->iI = (body->I) ? 1.0f / body->I : 0.0f;
        }

        void SetOrient(float radians)
        {
        }

        void Draw(olc::PixelGameEngine* pge, const olc::vf2d& origin, const olc::vf2d& proj) const
        {
            auto center = origin + (olc::vf2d(body->position.x, body->position.y) * proj);
            pge->DrawCircle(center, int(radius), olc::WHITE);

            // Render line within circle so orientation is visible
            Vector r(0, 1.0f);
            float c = std::cos(body->orient);
            float s = std::sin(body->orient);
            r = { r.x * c - r.y * s, r.x * s + r.y * c };
            r *= radius;
            r = r + body->position;
            olc::vf2d orientation = origin + (olc::vf2d(r.x, r.y) * proj);
            pge->DrawLine(center, orientation, olc::RED);
        }

        Type GetType(void) const
        {
            return eCircle;
        }
    };

    struct PolygonShape : public Shape
    {
        void Initialize(float density)
        {
            ComputeMass(density);
        }

        Shape* Clone(void) const
        {
            PolygonShape* poly = new PolygonShape();
            poly->u = u;
            for (uint32_t i = 0; i < m_vertexCount; ++i)
            {
                poly->m_vertices[i] = m_vertices[i];
                poly->m_normals[i] = m_normals[i];
            }
            poly->m_vertexCount = m_vertexCount;
            return poly;
        }

        void ComputeMass(float density)
        {
            // Calculate centroid and moment of interia
            Vector c(0.0f, 0.0f); // centroid
            float area = 0.0f;
            float I = 0.0f;
            const float k_inv3 = 1.0f / 3.0f;

            for (uint32_t i1 = 0; i1 < m_vertexCount; ++i1)
            {
                // Triangle vertices, third vertex implied as (0, 0)
                Vector p1(m_vertices[i1]);
                uint32_t i2 = i1 + 1 < m_vertexCount ? i1 + 1 : 0;
                Vector p2(m_vertices[i2]);

                float D = p1.cross(p2);
                float triangleArea = 0.5f * D;

                area += triangleArea;

                // Use area to weight the centroid average, not just vertex position
                c += (p1 + p2) * triangleArea * k_inv3;

                float intx2 = p1.x * p1.x + p2.x * p1.x + p2.x * p2.x;
                float inty2 = p1.y * p1.y + p2.y * p1.y + p2.y * p2.y;
                I += (0.25f * k_inv3 * D) * (intx2 + inty2);
            }

            c *= 1.0f / area;

            // Translate vertices to centroid (make the centroid (0, 0)
            // for the polygon in model space)
            // Not floatly necessary, but I like doing this anyway
            for (uint32_t i = 0; i < m_vertexCount; ++i)
                m_vertices[i] -= c;

            body->m = density * area;
            body->im = (body->m) ? 1.0f / body->m : 0.0f;
            body->I = I * density;
            body->iI = body->I ? 1.0f / body->I : 0.0f;
        }

        void SetOrient(float radians)
        {
            u.Set(radians);
        }

        void Draw(olc::PixelGameEngine* pge, const olc::vf2d& origin, const olc::vf2d& proj) const
        {
            Vector o(origin.x, origin.y);
            Vector p(proj.x, proj.y);
            Vector first_v = body->position + u * m_vertices[0];
            Vector last_v = o + first_v * p;
            for (uint32_t i = 1; i < m_vertexCount; ++i)
            {
                Vector v = body->position + u * m_vertices[i];
                v = o + v * p;
                pge->DrawLine(last_v.x, last_v.y, v.x, v.y, olc::GREEN);
                last_v = v;
            }
            first_v = o + first_v * p;
            pge->DrawLine(last_v.x, last_v.y, first_v.x, first_v.y, olc::GREEN);
        }

        Type GetType(void) const
        {
            return ePoly;
        }

        // Half width and half height
        void SetBox(float hw, float hh)
        {
            m_vertexCount = 4;
            m_vertices[0] = { -hw, -hh };
            m_vertices[1] = { hw, -hh };
            m_vertices[2] = { hw, hh };
            m_vertices[3] = { -hw, hh };
            m_normals[0] = { 0.0f, -1.0f };
            m_normals[1] = { 1.0f, 0.0f };
            m_normals[2] = { 0.0f, 1.0f };
            m_normals[3] = { -1.0f, 0.0f };
        }

        void Set(Vector* vertices, uint32_t count)
        {
            // No hulls with less than 3 vertices (ensure actual polygon)
            assert(count > 2 && count <= MaxPolyVertexCount);
            count = std::min(count, uint32_t(MaxPolyVertexCount));

            // Find the right most point on the hull
            uint32_t rightMost = 0;
            float highestXCoord = vertices[0].x;
            for (uint32_t i = 1; i < count; ++i)
            {
                float x = vertices[i].x;
                if (x > highestXCoord)
                {
                    highestXCoord = x;
                    rightMost = i;
                }

                // If matching x then take farthest negative y
                else if (x == highestXCoord)
                    if (vertices[i].y < vertices[rightMost].y)
                        rightMost = i;
            }

            uint32_t hull[MaxPolyVertexCount];
            uint32_t outCount = 0;
            uint32_t indexHull = rightMost;

            for (;;)
            {
                hull[outCount] = indexHull;

                // Search for next index that wraps around the hull
                // by computing cross products to find the most counter-clockwise
                // vertex in the set, given the previos hull index
                uint32_t nextHullIndex = 0;
                for (uint32_t i = 1; i < (uint32_t)count; ++i)
                {
                    // Skip if same coordinate as we need three unique
                    // points in the set to perform a cross product
                    if (nextHullIndex == indexHull)
                    {
                        nextHullIndex = i;
                        continue;
                    }

                    // Cross every set of three unique vertices
                    // Record each counter clockwise third vertex and add
                    // to the output hull
                    // See : http://www.oocities.org/pcgpe/math2d.html
                    Vector e1 = vertices[nextHullIndex] - vertices[hull[outCount]];
                    Vector e2 = vertices[i] - vertices[hull[outCount]];
                    float c = e1.cross(e2);
                    if (c < 0.0f)
                        nextHullIndex = i;

                    // Cross product is zero then e vectors are on same line
                    // therefor want to record vertex farthest along that line
                    if (c == 0.0f && e2.mag2() > e1.mag2())
                        nextHullIndex = i;
                }

                ++outCount;
                indexHull = nextHullIndex;

                // Conclude algorithm upon wrap-around
                if (nextHullIndex == rightMost)
                {
                    m_vertexCount = outCount;
                    break;
                }
            }

            // Copy vertices into shape's vertices
            for (uint32_t i = 0; i < m_vertexCount; ++i)
                m_vertices[i] = vertices[hull[i]];

            // Compute face normals
            for (uint32_t i1 = 0; i1 < m_vertexCount; ++i1)
            {
                uint32_t i2 = i1 + 1 < m_vertexCount ? i1 + 1 : 0;
                Vector face = m_vertices[i2] - m_vertices[i1];

                // Ensure no zero-length edges, because that's bad
                assert(face.mag2() > EPSILON * EPSILON);

                // Calculate normal with 2D cross product between vector and scalar
                m_normals[i1] = Vector(face.y, -face.x).norm();
            }
        }

        // The extreme point along a direction within a polygon
        Vector GetSupport(const Vector& dir)
        {
            float bestProjection = -FLT_MAX;
            Vector bestVertex;

            for (uint32_t i = 0; i < m_vertexCount; ++i)
            {
                Vector v = m_vertices[i];
                float projection = v.dot(dir);

                if (projection > bestProjection)
                {
                    bestVertex = v;
                    bestProjection = projection;
                }
            }

            return bestVertex;
        }

        uint32_t m_vertexCount;
        Vector m_vertices[MaxPolyVertexCount];
        Vector m_normals[MaxPolyVertexCount];
    };
}
