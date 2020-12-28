#pragma once
#include "Vector.hpp"

namespace MMORPG
{
    struct Line
    {
        Vector start;
        Vector end;

        Line(Vector s, Vector e) : start(s), end(e) {}
    };
}