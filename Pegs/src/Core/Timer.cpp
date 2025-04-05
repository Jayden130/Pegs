#include "Core/Timer.hpp"

Timer::Timer(long long remainingMs, const long long opponentRemainingMs, const long long startingMs)
{
	sw = std::chrono::steady_clock();
	TimeAtStartOfTurn = sw.now();

	GameStartTimeMilliseconds = startingMs;
	MillisecondsRemaining = remainingMs;
	OpponentMillisecondsRemaining = opponentRemainingMs;
}

long long Timer::GetGameStartTimeMiliseconds() const
{
	return GameStartTimeMilliseconds;
}

long long Timer::GetMilisecondsElapsedThisTurn() const
{
	auto now = sw.now();
	return std::chrono::duration_cast<std::chrono::milliseconds>(now - TimeAtStartOfTurn).count();
}

long long Timer::GetMilisecondsRemaining() const
{
	return std::max(0ll, MillisecondsRemaining - GetMilisecondsElapsedThisTurn());
}

long long Timer::GetOpponentMilisecondsRemaining() const
{
	return OpponentMillisecondsRemaining;
}
