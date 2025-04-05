#pragma once

#include <chrono>

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

private:
	bool isWhiteToMove = true;
	std::chrono::steady_clock::time_point TimeAtStartOfTurn;
};