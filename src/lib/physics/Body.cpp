#include "Body.hpp"
#include "Shape.hpp"
#include "Utils.hpp"

namespace MMORPG
{
    Body::Body(Shape* shape_, Vector pos)
        : shape(shape_->Clone())
    {
        shape->body = this;
        position = pos;
        velocity = { 0,0 };
        angularVelocity = 0;
        torque = 0;
        orient = Utils::Random(-PI, PI);
        force = { 0,0 };
        staticFriction = 0.5f;
        dynamicFriction = 0.3f;
        restitution = 0.2f;
        shape->Initialize();
        r = Utils::Random(0.2f, 1.0f);
        g = Utils::Random(0.2f, 1.0f);
        b = Utils::Random(0.2f, 1.0f);
    }

    void Body::SetOrient(float radians)
    {
        orient = radians;
        shape->SetOrient(radians);
    }
}
