#pragma once

#include <SFML/Graphics.hpp>

namespace Renderer {
	void updateBoard(Board& board, sf::RenderWindow& window);

	void resizeKeepRatios(const sf::Event::Resized* resized, sf::RenderWindow& window);

	void drawBackground(sf::RenderWindow& window);
	void newThread(sf::RenderWindow& window);
	void renderPawns(sf::RenderWindow& window, Board& board, short index);
};

