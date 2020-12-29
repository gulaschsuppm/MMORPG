#include "Player.hpp"
#include "Vector.hpp"
#include "Square.hpp"

namespace MMORPG
{
    bool Player::OnInput(GameEngine* game_engine)
    {
        // Check if we are shooting
        if (game_engine->GetMouse(0).bPressed)
        {
            // Project to physical engine, which has its origin in the middle of the screen
            Vector center = { float(game_engine->ScreenWidth()) / 2.0f, float(game_engine->ScreenHeight()) / 2.0f };
            Vector mouse_pos = { float(game_engine->GetMouseX()), float(game_engine->GetMouseY()) };

            std::shared_ptr<Square> projectile = std::make_shared<Square>(Vector(), 0.0f, 10.0f, olc::RED);
            projectile->SetForce(mouse_pos - center);
            game_engine->AddPhysicalObject(projectile);
            game_engine->AddDrawingObject(projectile);
        }

        return true;
    }
}