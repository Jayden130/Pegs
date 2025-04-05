#pragma once

class GameController
{
public:
	void StartGame(IBot& whiteBot, IBot& blackBot, Board& board, const long long startingMS);

private:
	bool IsLegalMove(Move move, Board& board);
	std::string ToNotation(int startSquare, int targetSquare, int captureSquare);
	std::string GetResultString(GameResult result);
};