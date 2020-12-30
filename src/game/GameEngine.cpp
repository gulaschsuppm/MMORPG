#include "GameEngine.hpp"
#include "Body.hpp"
#include "Vector.hpp"
#include "Utils.hpp"
#include "Shape.hpp"
#include <assert.h>

namespace MMORPG
{
    Body* GameEngine::AddObject(Shape* shape, Vector pos, float density)
    {
        assert(shape);
        Body* b = new Body(shape, pos, density);
        _gaming_objects.push_back(b);
        //_physics_engine.AddObject(b);
        //_renderer.AddObject(b->shape);

        return b;
    }

    bool GameEngine::OnUserCreate()
    {
       
        // Bottom left
        _origin = { 0, float(ScreenHeight()) };
        // Y axis is flipped
        _projection = { 1,-1 };
        _renderer.SetOrigin(_origin);
        _renderer.SetProjection(_projection);

        Circle c(5.0f);
        Body* b = AddObject(&c, { 128, 80 });
        b->SetStatic();
        b->name = "Static Ball";

        PolygonShape poly;
        poly.SetBox(30.0f, 1.0f);
        b = AddObject(&poly, { 128, 40 });
        b->SetStatic();
        b->SetOrient(0);
        b->name = "Static box";

        return true;
    }

    bool GameEngine::OnUserUpdate(float fElapsedTime)
    {
        Clear(olc::DARK_BLUE);

        //// Cycle through the listeners
        //auto listener_it = _input_listeners.begin();
        //while (listener_it != _input_listeners.end())
        //{
        //    if ((*listener_it)->OnInput(this))
        //    {
        //        ++listener_it;
        //    }
        //    else
        //    {
        //        listener_it = _input_listeners.erase(listener_it);
        //    }
        //}

        if (GetKey(olc::LEFT).bPressed)
        {
            _origin.x += 1;
            _renderer.SetOrigin(_origin);
        }
        if (GetKey(olc::RIGHT).bPressed)
        {
            _origin.x -= 1;
            _renderer.SetOrigin(_origin);
        }
        if (GetKey(olc::UP).bPressed)
        {
            // Create explosion at mouse
            olc::vf2d center = { float(GetMouseX()), float(GetMouseY()) };
            center = (center - _origin) * _projection;

            Circle c(10.0f);
            Body* b = AddObject(&c, { center.x, center.y }, 5.0f);
            b->name = "explosion";
            b->restitution = 0.0001f;
            b->SetStatic();
            b->isExplosion = true;
        }
        //if (GetKey(olc::DOWN).bPressed)
        //{
        //    _projection *= 2;
        //    _renderer.SetProjection(_projection);
        //}

        if (GetMouse(0).bPressed)
        {
            // Project to physical engine, which has its origin in the middle of the screen
            olc::vf2d center = { float(GetMouseX()), float(GetMouseY()) };

            center = (center - _origin) * _projection;
            Circle c(5.0f);
            Body* b = AddObject(&c, { center.x, center.y });
            b->name = "new ball";
        }
        if (GetMouse(1).bPressed)
        {
            olc::vf2d center = { float(GetMouseX()), float( GetMouseY()) };
            center = (center - _origin) * _projection;

            PolygonShape poly;
            uint32_t count = (uint32_t)Utils::Random(3, MaxPolyVertexCount);
            Vector* vertices = new Vector[count];
            float e = Utils::Random(5, 10);
            for (uint32_t i = 0; i < count; ++i)
                vertices[i] = { Utils::Random(-e, e), Utils::Random(-e, e) };
            poly.Set(vertices, count);
            Body* b = AddObject(&poly, { center.x, center.y });
            b->SetOrient(Utils::Random(-PI, PI));
            b->restitution = 0.2f;
            b->dynamicFriction = 0.2f;
            b->staticFriction = 0.4f;
            delete[] vertices;
        }

        _physics_engine.Run(_gaming_objects, fElapsedTime);
        _renderer.Run(this, _gaming_objects);

        // Clean up
        _gaming_objects.remove_if([](auto obj)
            {
                if (obj->destroy)
                {
                    delete obj;
                    return true;
                }
                return false;
            });

        std::stringstream ss;
        ss << "Objects: ";
        ss << _gaming_objects.size();
        DrawString(20,20,ss.str());

        return true;
    }
}