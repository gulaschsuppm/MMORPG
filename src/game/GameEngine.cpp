#include "GameEngine.hpp"
#include "Ball.hpp"
#include "Player.hpp"
#include "Vector.hpp"

namespace MMORPG
{
    void GameEngine::AddDrawingObject(std::shared_ptr<DrawingObject> object)
    {
        _drawing_objects.push_back(object);
    }

    void GameEngine::AddPhysicalObject(std::shared_ptr<PhysicalObject> object)
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
        std::shared_ptr<Player> player = std::make_shared<Player>(Vector());
        AddInputRegister(player);
        AddDrawingObject(player);

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

        // Cycle through all game objects and delete them if they say so
        auto game_object_it = _drawing_objects.begin();
        while (game_object_it != _drawing_objects.end())
        {
            if ((*game_object_it)->Draw(this))
            {
                ++game_object_it;
            }
            else
            {
                game_object_it = _drawing_objects.erase(game_object_it);
            }
        }

        return true;
    }
}