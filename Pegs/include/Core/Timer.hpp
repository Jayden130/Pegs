#pragma once

#include <chrono>

class Timer
{
private:
    std::chrono::steady_clock sw;
    long long GameStartTimeMilliseconds = 0;
    long long MillisecondsRemaining = 0;
    long long OpponentMillisecondsRemaining = 0;
    std::chrono::steady_clock::time_point TimeAtStartOfTurn;


public:
    Timer(long long remainingMs, const long long opponentRemainingMs, const long long startingMs);
    long long GetGameStartTimeMiliseconds() const;
    long long GetMilisecondsElapsedThisTurn() const;
    long long GetMilisecondsRemaining() const;
    long long GetOpponentMilisecondsRemaining() const;
};