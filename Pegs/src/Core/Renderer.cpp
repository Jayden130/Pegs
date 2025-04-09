#include <SFML/Graphics.hpp>

#include <Board/Board.hpp>
#include "Core/Renderer.hpp"


sf::Texture whitePegTex("pawn_white.png", false, sf::IntRect({ 0, 0 }, { 64, 64 }));
sf::Texture blackPegTex("pawn_black.png", false, sf::IntRect({ 0, 0 }, { 64, 64 }));


void Renderer::newThread(sf::RenderWindow& window) {
    whitePegTex.setSmooth(true);
    blackPegTex.setSmooth(true);

    Renderer::drawBackground(window);
    window.display();

    while (const std::optional event = window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            window.close();
        } else if (auto* resized = event->getIf<sf::Event::Resized>()) {
            Renderer::resizeKeepRatios(resized, window);
        }
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

void Renderer::updateBoard(Board& board, sf::RenderWindow& window) {
    window.clear();
    Renderer::drawBackground(window);
    Renderer::renderPawns(window, board, 0);
    Renderer::renderPawns(window, board, 1);

    window.display();
}

void Renderer::renderPawns(sf::RenderWindow& window, Board& board, short index) {
    sf::Texture texture;
    if (index == 0) { 
        texture = whitePegTex;
    } 
    else if (index == 1) {
        texture = blackPegTex;
    }


    uint64_t x = static_cast<uint64_t>(board.bitboards[0]);
    int column = 0;
    int row = 0;
    while (x != 0) {
        if (row == 6) {
            break;
        }

        sf::Sprite sprite(texture);
        sprite.setPosition({ column * 64.f, row * 64.f });

        uint64_t bit = x & 1;
        if (bit == 1) {
            window.draw(sprite);
        }

        if (column == 3) {
            row++;
            column = 0;
        } else {
            column++;
        }

        x >>= 1;
    }
}

void Renderer::resizeKeepRatios(const sf::Event::Resized* resized, sf::RenderWindow& window) {
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


