#include "GameEngine.hpp"
#include "Ball.hpp"
#include "Player.hpp"
#include "Vector.hpp"

namespace MMORPG
{
    void GameEngine::AddDrawingObject(std::shared_ptr<DrawingObject> object)
    {
        _renderer.AddObject(object);
    }

    void GameEngine::AddPhysicalObject(std::shared_ptr<RigidBody> object)
    {
        _physics_engine.AddObject(object);
    }

    void GameEngine::AddInputRegister(std::shared_ptr<InputListener> object)
    {
        _input_listeners.push_back(object);
    }

    bool GameEngine::OnUserCreate()
    {
        // Create a player in the middle
        std::shared_ptr<Player> player = std::make_shared<Player>(Vector(), 3.0f, olc::WHITE);
        AddInputRegister(player);
        AddDrawingObject(player);

        origin = {float(ScreenWidth())/2.0f, float(ScreenHeight()) / 2.0f };

        return true;
    }

    bool GameEngine::OnUserUpdate(float fElapsedTime)
    {
        Clear(olc::DARK_BLUE);

        // Cycle through the listeners
        auto listener_it = _input_listeners.begin();
        while (listener_it != _input_listeners.end())
        {
            if ((*listener_it)->OnInput(this))
            {
                ++listener_it;
            }
            else
            {
                listener_it = _input_listeners.erase(listener_it);
            }
        }

        _physics_engine.Run(fElapsedTime);

        _renderer.Draw(this, origin);
        //// Cycle through all game objects and delete them if they say so
        //auto game_object_it = _drawing_objects.begin();
        //while (game_object_it != _drawing_objects.end())
        //{
        //    if ((*game_object_it)->Draw(this))
        //    {
        //        ++game_object_it;
        //    }
        //    else
        //    {
        //        game_object_it = _drawing_objects.erase(game_object_it);
        //    }
        //}

        return true;
    }
}