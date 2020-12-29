#pragma once
#include "InputListener.hpp"
#include "RigidBody.hpp"
#include "DrawingObject.hpp"

namespace MMORPG
{
    class GameObject
    {
    public:
        bool HasInputListener()
        {
            return (_input_listener != nullptr);
        }
        bool HasRigidBody()
        {
            return (_rigid_body != nullptr);
        }
        bool HasDrawingObject()
        {
            return (_drawing_object != nullptr);
        }
    private:
        InputListener* _input_listener;
        RigidBody* _rigid_body;
        DrawingObject* _drawing_object;
    };
}