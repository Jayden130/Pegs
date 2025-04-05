#pragma once

class IBot
{
public:
    virtual ~IBot() {}

    virtual Move Think(Board board, Timer timer) = 0;
};