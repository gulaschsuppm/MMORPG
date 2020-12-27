#pragma once

namespace MMORPG
{
    class GameEngine;
}

namespace MMORPG
{
    class InputListener
    {
    public:
        virtual bool OnInput(GameEngine* game_engine) = 0;
    };
}