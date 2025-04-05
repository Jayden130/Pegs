#pragma once

#include "Core/IBot.hpp"

class MyBot : public IBot
{
public:
	virtual Move Think(Board board, Timer timer);
};