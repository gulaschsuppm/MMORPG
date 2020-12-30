#include "Collision.hpp"
#include "Manifold.hpp"

namespace MMORPG
{
    CollisionCallback Dispatch[Shape::eCount][Shape::eCount] =
    {
      {
        CircletoCircle, CircletoPolygon
      },
      {
        PolygontoCircle, PolygontoPolygon
      },
    };

    void CircletoCircle(Manifold* m, Body* a, Body* b)
    {
        Circle* A = reinterpret_cast<Circle*>(a->shape);
        Circle* B = reinterpret_cast<Circle*>(b->shape);

        // Calculate translational vector, which is normal
        Vector normal = b->position - a->position;

        float dist_sqr = normal.mag2();
        float radius = A->radius + B->radius;

        // Not in contact
        if (dist_sqr >= radius * radius)
        {
            m->contact_count = 0;
            return;
        }

        float distance = std::sqrt(dist_sqr);

        m->contact_count = 1;

        if (distance == 0.0f)
        {
            m->penetration = A->radius;
            m->normal = Vector(1, 0);
            m->contacts[0] = a->position;
        }
        else
        {
            m->penetration = radius - distance;
            m->normal = normal / distance; // Faster than using Normalized since we already performed sqrt
            m->contacts[0] = m->normal * A->radius + a->position;
        }
    }

    void CircletoPolygon(Manifold* m, Body* a, Body* b)
    {
        Circle* A = reinterpret_cast<Circle*>      (a->shape);
        PolygonShape* B = reinterpret_cast<PolygonShape*>(b->shape);

        m->contact_count = 0;

        // Transform circle center to Polygon model space
        Vector center = a->position;
        center = B->u.Transpose() * (center - b->position);

        // Find edge with minimum penetration
        // Exact concept as using support points in Polygon vs Polygon
        float separation = -FLT_MAX;
        uint32_t faceNormal = 0;
        for (uint32_t i = 0; i < B->m_vertexCount; ++i)
        {
            float s = B->m_normals[i].dot(center - B->m_vertices[i]);

            if (s > A->radius)
                return;

            if (s > separation)
            {
                separation = s;
                faceNormal = i;
            }
        }

        // Grab face's vertices
        Vector v1 = B->m_vertices[faceNormal];
        uint32_t i2 = faceNormal + 1 < B->m_vertexCount ? faceNormal + 1 : 0;
        Vector v2 = B->m_vertices[i2];

        // Check to see if center is within polygon
        if (separation < EPSILON)
        {
            m->contact_count = 1;
            m->normal = -(B->u * B->m_normals[faceNormal]);
            m->contacts[0] = m->normal * A->radius + a->position;
            m->penetration = A->radius;
            return;
        }

        // Determine which voronoi region of the edge center of circle lies within
        float dot1 = (center - v1).dot(v2 - v1);
        float dot2 = (center - v2).dot(v1 - v2);
        m->penetration = A->radius - separation;

        // Closest to v1
        if (dot1 <= 0.0f)
        {
            if (Utils::DistSqr(center, v1) > A->radius * A->radius)
                return;

            m->contact_count = 1;
            Vector n = v1 - center;
            n = B->u * n;
            m->normal = n.norm();
            v1 = B->u * v1 + b->position;
            m->contacts[0] = v1;
        }

        // Closest to v2
        else if (dot2 <= 0.0f)
        {
            if (Utils::DistSqr(center, v2) > A->radius * A->radius)
                return;

            m->contact_count = 1;
            Vector n = v2 - center;
            v2 = B->u * v2 + b->position;
            m->contacts[0] = v2;
            n = B->u * n;
            m->normal = n.norm();
        }

        // Closest to face
        else
        {
            Vector n = B->m_normals[faceNormal];
            if ((center - v1).dot(n) > A->radius)
                return;

            n = B->u * n;
            m->normal = -n;
            m->contacts[0] = m->normal * A->radius + a->position;
            m->contact_count = 1;
        }
    }

    void PolygontoCircle(Manifold* m, Body* a, Body* b)
    {
        CircletoPolygon(m, b, a);
        m->normal = -m->normal;
    }

    float FindAxisLeastPenetration(uint32_t* faceIndex, PolygonShape* A, PolygonShape* B)
    {
        float bestDistance = -FLT_MAX;
        uint32_t bestIndex = 0;

        for (uint32_t i = 0; i < A->m_vertexCount; ++i)
        {
            // Retrieve a face normal from A
            Vector n = A->m_normals[i];
            Vector nw = A->u * n;

            // Transform face normal into B's model space
            Mat2 buT = B->u.Transpose();
            n = buT * nw;

            // Retrieve support point from B along -n
            Vector s = B->GetSupport(-n);

            // Retrieve vertex on face from A, transform into
            // B's model space
            Vector v = A->m_vertices[i];
            v = A->u * v + A->body->position;
            v -= B->body->position;
            v = buT * v;

            // Compute penetration distance (in B's model space)
            float d = n.dot(s - v);

            // Store greatest distance
            if (d > bestDistance)
            {
                bestDistance = d;
                bestIndex = i;
            }
        }

        *faceIndex = bestIndex;
        return bestDistance;
    }

    void FindIncidentFace(Vector* v, PolygonShape* RefPoly, PolygonShape* IncPoly, uint32_t referenceIndex)
    {
        Vector referenceNormal = RefPoly->m_normals[referenceIndex];

        // Calculate normal in incident's frame of reference
        referenceNormal = RefPoly->u * referenceNormal; // To world space
        referenceNormal = IncPoly->u.Transpose() * referenceNormal; // To incident's model space

        // Find most anti-normal face on incident polygon
        int32_t incidentFace = 0;
        float minDot = FLT_MAX;
        for (uint32_t i = 0; i < IncPoly->m_vertexCount; ++i)
        {
            float dot = referenceNormal.dot(IncPoly->m_normals[i]);
            if (dot < minDot)
            {
                minDot = dot;
                incidentFace = i;
            }
        }

        // Assign face vertices for incidentFace
        v[0] = IncPoly->u * IncPoly->m_vertices[incidentFace] + IncPoly->body->position;
        incidentFace = incidentFace + 1 >= (int32_t)IncPoly->m_vertexCount ? 0 : incidentFace + 1;
        v[1] = IncPoly->u * IncPoly->m_vertices[incidentFace] + IncPoly->body->position;
    }

    int32_t Clip(Vector n, float c, Vector* face)
    {
        uint32_t sp = 0;
        Vector out[2] = {
          face[0],
          face[1]
        };

        // Retrieve distances from each endpoint to the line
        // d = ax + by - c
        float d1 = n.dot(face[0]) - c;
        float d2 = n.dot(face[1]) - c;

        // If negative (behind plane) clip
        if (d1 <= 0.0f) out[sp++] = face[0];
        if (d2 <= 0.0f) out[sp++] = face[1];

        // If the points are on different sides of the plane
        if (d1 * d2 < 0.0f) // less than to ignore -0.0f
        {
            // Push interesection point
            float alpha = d1 / (d1 - d2);
            out[sp] = face[0] + ((face[1] - face[0]) * alpha);
            ++sp;
        }

        // Assign our new converted values
        face[0] = out[0];
        face[1] = out[1];

        assert(sp != 3);

        return sp;
    }

    void PolygontoPolygon(Manifold* m, Body* a, Body* b)
    {
        PolygonShape* A = reinterpret_cast<PolygonShape*>(a->shape);
        PolygonShape* B = reinterpret_cast<PolygonShape*>(b->shape);
        m->contact_count = 0;

        // Check for a separating axis with A's face planes
        uint32_t faceA;
        float penetrationA = FindAxisLeastPenetration(&faceA, A, B);
        if (penetrationA >= 0.0f)
            return;

        // Check for a separating axis with B's face planes
        uint32_t faceB;
        float penetrationB = FindAxisLeastPenetration(&faceB, B, A);
        if (penetrationB >= 0.0f)
            return;

        uint32_t referenceIndex;
        bool flip; // Always point from a to b

        PolygonShape* RefPoly; // Reference
        PolygonShape* IncPoly; // Incident

        // Determine which shape contains reference face
        if (Utils::BiasGreaterThan(penetrationA, penetrationB))
        {
            RefPoly = A;
            IncPoly = B;
            referenceIndex = faceA;
            flip = false;
        }
        else
        {
            RefPoly = B;
            IncPoly = A;
            referenceIndex = faceB;
            flip = true;
        }

        // World space incident face
        Vector incidentFace[2];
        FindIncidentFace(incidentFace, RefPoly, IncPoly, referenceIndex);

        //        y
        //        ^  ->n       ^
        //      +---c ------posPlane--
        //  x < | i |\
        //      +---+ c-----negPlane--
        //             \       v
        //              r
        //
        //  r : reference face
        //  i : incident poly
        //  c : clipped point
        //  n : incident normal

        // Setup reference face vertices
        Vector v1 = RefPoly->m_vertices[referenceIndex];
        referenceIndex = referenceIndex + 1 == RefPoly->m_vertexCount ? 0 : referenceIndex + 1;
        Vector v2 = RefPoly->m_vertices[referenceIndex];

        // Transform vertices to world space
        v1 = RefPoly->u * v1 + RefPoly->body->position;
        v2 = RefPoly->u * v2 + RefPoly->body->position;

        // Calculate reference face side normal in world space
        Vector sidePlaneNormal = (v2 - v1).norm();

        // Orthogonalize
        Vector refFaceNormal(sidePlaneNormal.y, -sidePlaneNormal.x);

        // ax + by = c
        // c is distance from origin
        float refC = refFaceNormal.dot(v1);
        float negSide = -sidePlaneNormal.dot(v1);
        float posSide = sidePlaneNormal.dot(v2);

        // Clip incident face to reference face side planes
        if (Clip(-sidePlaneNormal, negSide, incidentFace) < 2)
            return; // Due to floating point error, possible to not have required points

        if (Clip(sidePlaneNormal, posSide, incidentFace) < 2)
            return; // Due to floating point error, possible to not have required points

          // Flip
        m->normal = flip ? -refFaceNormal : refFaceNormal;

        // Keep points behind reference face
        uint32_t cp = 0; // clipped points behind reference face
        float separation = refFaceNormal.dot(incidentFace[0]) - refC;
        if (separation <= 0.0f)
        {
            m->contacts[cp] = incidentFace[0];
            m->penetration = -separation;
            ++cp;
        }
        else
            m->penetration = 0;

        separation = refFaceNormal.dot(incidentFace[1]) - refC;
        if (separation <= 0.0f)
        {
            m->contacts[cp] = incidentFace[1];

            m->penetration += -separation;
            ++cp;

            // Average penetration
            m->penetration /= (float)cp;
        }

        m->contact_count = cp;
    }
}
