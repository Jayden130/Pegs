#pragma once

#include "Board/Board.hpp"
#include "Core/Clock.hpp"

class GameController
{
public:
	void StartGame(IBot& whiteBot, IBot& blackBot, Board& board, const long long startingMS);

private:
	Move MakeMove(IBot& bot);
	bool IsLegalMove(Move move) const;
	std::string ToNotation(int startSquare, int targetSquare, int captureSquare);
	std::string GetResultString(GameResult result);

	Board* board;
	Clock clock;

};