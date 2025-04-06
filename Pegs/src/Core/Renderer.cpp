#include <SFML/Graphics.hpp>
#include "Core/Renderer.hpp"

void Renderer::main() {
    sf::RenderWindow window(sf::VideoMode({ 256, 384 }), "SFML works!");
    sf::CircleShape shape(100.0f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                (void)window.close();
            }
            else if (auto* resized = event->getIf<sf::Event::Resized>()) {
                Renderer::resizeKeepRatios(window, resized);
            }
        }

        window.clear();

        Renderer::drawBackground(window);

        window.display();
    }
}

void Renderer::drawBackground(sf::RenderWindow& window) {
    for (int row = 0; row < 6; row++) {
        for (int column = 0; column < 4; column++) {
            sf::RectangleShape tile({64.0f, 64.0f});

            if ((row + column) % 2 == 0) {
                sf::Color color(140, 252, 140);
                tile.setFillColor(color);
            } else {
                sf::Color color(92, 196, 84);
                tile.setFillColor(color);
            }
            tile.setPosition({64.0f * column, 64.0f * row });
            window.draw(tile);
        }
    }
}



void Renderer::resizeKeepRatios(sf::RenderWindow& window, const sf::Event::Resized* resized) {
    sf::View view = window.getDefaultView();

    sf::Vector2f newSize = (sf::Vector2f)resized->size;

    // Get the ratio between the new and old size (size 2 to 1 is a ratio of 0.5)
    sf::Vector2f sizeRatios = { newSize.x / view.getSize().x, newSize.y / view.getSize().y };
    float smallestRatio = std::min(sizeRatios.x, sizeRatios.y);

    // Resize view to new size and zoom in (lower value is bigger objects)
    view.setSize(newSize);
    view.zoom(1 / smallestRatio);

    window.setView(view);
}


