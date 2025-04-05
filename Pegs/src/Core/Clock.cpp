#include "Core/Timer.hpp"
#include "Core/Clock.hpp"

void Clock::Start(long long startingMS, bool isWhiteToMove)
{
	GameStartTimeMilliseconds = startingMS;
	WhiteMillisecondsRemaining = startingMS;
	BlackMillisecondsRemaining = startingMS;

	this->isWhiteToMove = isWhiteToMove;
	TimeAtStartOfTurn = sw.now();
}

void Clock::Turn()
{
	auto now = sw.now();
	long long timeSpent = std::chrono::duration_cast<std::chrono::milliseconds>(now - TimeAtStartOfTurn).count();

	if (isWhiteToMove)
		WhiteMillisecondsRemaining = std::max(0ll, WhiteMillisecondsRemaining - timeSpent);
	else
		BlackMillisecondsRemaining = std::max(0ll, BlackMillisecondsRemaining - timeSpent);

	TimeAtStartOfTurn = now;
	isWhiteToMove = !isWhiteToMove;
}

Timer Clock::GetWhiteTimer()
{
	return Timer(WhiteMillisecondsRemaining, BlackMillisecondsRemaining, GameStartTimeMilliseconds);
}

Timer Clock::GetBlackTimer()
{
	return Timer(BlackMillisecondsRemaining, WhiteMillisecondsRemaining, GameStartTimeMilliseconds);
}
