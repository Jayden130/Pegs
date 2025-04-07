#pragma once

#include "Board/Board.hpp"
#include "Core/Timer.hpp"

class IBot
{
public:
    virtual ~IBot() {}

    virtual Move Think(Board board, Timer timer) = 0;
};