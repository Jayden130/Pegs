#pragma once

#include <chrono>
#include "Core/Timer.hpp"

class Clock
{
public:
	void Start(long long startingMS, bool isWhiteToMove);
	void Turn();
	Timer GetWhiteTimer();
	Timer GetBlackTimer();

	std::chrono::steady_clock sw;
	long long GameStartTimeMilliseconds = 0;
	long long WhiteMillisecondsRemaining = 0;
	long long BlackMillisecondsRemaining = 0;

	bool isWhiteToMove = true;

private:
	std::chrono::steady_clock::time_point TimeAtStartOfTurn;
};