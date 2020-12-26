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
        game_objects.push_back(std::move(std::make_unique<Ball>(float(ScreenWidth())/2.0f, float(ScreenHeight())/2.0f)));
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
            float x_traj = 250.0f;
            float y_traj = 250.0f;
            if (GetMouseX() < (ScreenWidth() / 2.0f))
            {
                x_traj = -x_traj;
            }
            if (GetMouseY() < (ScreenWidth() / 2.0f))
            {
                y_traj = -y_traj;
            }
            game_objects.push_back(std::move(std::make_unique<Ball>(float(ScreenWidth()) / 2.0f, float(ScreenHeight()) / 2.0f, olc::RED, x_traj, y_traj)));
        }

        for (auto game_object = game_objects.begin(); game_object != game_objects.end(); ++game_object)
        {
            (*game_object)->OnUserUpdate(fElapsedTime, this);
        }

        return true;
    }
}