#pragma once

#include <SFML/Graphics.hpp>

#include "Core/Clock.hpp"
#include "Core/IBot.hpp"

class GameController
{
public:
	void StartGame(IBot& whiteBot, IBot& blackBot, Board& board, const long long startingMS);
	Board* board;

private:
	Move MakeMove(IBot& bot, sf::RenderWindow& window);
	bool IsLegalMove(Move move) const;
	std::string ToNotation(int startSquare, int targetSquare, int captureSquare);
	std::string GetResultString(GameResult result);

	Clock clock;

};