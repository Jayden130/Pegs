#pragma once

#include "Core/IBot.hpp"

// BEEP BOOP, I AM HUMAN
class HumanBot : public IBot
{
public:
	virtual Move Think(Board board, Timer timer);

private:
	Move GetMoveByNotation(std::string s);
};