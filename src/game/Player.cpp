#include "Player.hpp"

namespace MMORPG
{
    bool Player::OnInput(GameEngine* game_engine)
    {
        // Check if we are shooting
        if (game_engine->GetMouse(0).bPressed)
        {
            olc::vf2d center = { float(game_engine->ScreenWidth()) / 2.0f, float(game_engine->ScreenHeight()) / 2.0f };
            olc::vf2d mouse_pos = { float(game_engine->GetMouseX()), float(game_engine->GetMouseY()) };
            std::shared_ptr<Ball> projectile = std::make_shared<Ball>(center, olc::RED, mouse_pos - center);
            game_engine->AddObject(projectile);
        }

        return true;
    }
}