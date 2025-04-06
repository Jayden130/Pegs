#pragma once
namespace Renderer {
	void resizeKeepRatios(sf::RenderWindow& window, const sf::Event::Resized* resized);
	void drawBackground(sf::RenderWindow& window);
	void main();
};

