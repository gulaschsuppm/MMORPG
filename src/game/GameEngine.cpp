#include "GameEngine.hpp"
#include "Ball.hpp"
#include "Player.hpp"

namespace MMORPG
{
    void GameEngine::AddObject(std::shared_ptr<GameObject> object)
    {
        _game_objects.push_back(object);
    }

    void GameEngine::AddInputRegister(std::shared_ptr<InputListener> object)
    {
        _input_listeners.push_back(object);
    }

    bool GameEngine::OnUserCreate()
    {
        // Create a player in the middle
        std::shared_ptr<Player> player = std::make_shared<Player>(float(ScreenWidth()) / 2.0f, float(ScreenHeight()) / 2.0f);
        AddInputRegister(player);
        AddObject(player);

        // Cycle through all the game objects at this point and let them start up
        for (auto game_object = _game_objects.begin(); game_object != _game_objects.end(); ++game_object)
        {
            (*game_object)->OnUserCreate();
        }
        return true;
    }

    bool GameEngine::OnUserUpdate(float fElapsedTime)
    {
        Clear(olc::DARK_BLUE);

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

        // Cycle through all game objects and delete them if they say so
        auto game_object_it = _game_objects.begin();
        while (game_object_it != _game_objects.end())
        {
            if ((*game_object_it)->OnUserUpdate(fElapsedTime, this))
            {
                ++game_object_it;
            }
            else
            {
                game_object_it = _game_objects.erase(game_object_it);
            }
        }

        return true;
    }
}