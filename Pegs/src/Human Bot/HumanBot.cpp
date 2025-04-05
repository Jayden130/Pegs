#include <iostream>
#include "Board/Board.hpp"
#include "Core/Timer.hpp"

#include "Human Bot/HumanBot.hpp"

Move HumanBot::Think(Board board, Timer timer)
{
    std::string move;

    std::cout << "\nWhat move to play: ";
    std::cin.clear();
    std::cin >> move;

    return GetMoveByNotation(move);
}

Move HumanBot::GetMoveByNotation(std::string s)
{
    int startSquare = 0;
    int targetSquare = 0;
    int captureSquare = 0;

    // Get piece square
    int startFile = s[0] - 'a';
    int startRank = s[1] - '1';
    startSquare = startFile + startRank * 4;

    // Get square to move towards
    int targetFile = s[2] - 'a';
    int targetRank = s[3] - '1';
    targetSquare = targetFile + targetRank * 4;

    // Check if it is a capture
    if (s.length() > 4 && s[4] == '+')
    {
        captureSquare = (startSquare + targetSquare) / 2;
    }
    return Move(startSquare, targetSquare, captureSquare);
}


