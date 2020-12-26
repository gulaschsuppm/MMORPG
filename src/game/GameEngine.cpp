#include "GameEngine.hpp"
#include "Ball.hpp"

namespace MMORPG
{
    bool GameEngine::RegisterObject(std::unique_ptr<GameObject> object)
    {
        game_objects.push_back(std::move(object));
        return true;
    }

    bool GameEngine::OnUserCreate()
    {
        for (auto game_object = game_objects.begin(); game_object != game_objects.end(); ++game_object)
        {
            (*game_object)->OnUserCreate();
        }
        return true;
    }

    bool GameEngine::OnUserUpdate(float fElapsedTime)
    {
        Clear(olc::DARK_BLUE);

        if (GetMouse(0).bPressed)
        {
            game_objects.clear();
            game_objects.push_back(std::move(std::make_unique<Ball>(GetMouseX(), GetMouseY())));
        }

        for (auto game_object = game_objects.begin(); game_object != game_objects.end(); ++game_object)
        {
            (*game_object)->OnUserUpdate(this);
        }
        return true;
    }
}