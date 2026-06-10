#pragma once

#include <SFML/Graphics.hpp>

class GameField;

class Renderer {
private:
    int cellSize;

    sf::Color colors[6];
public:
    Renderer(int cellSize);

    void draw(sf::RenderWindow& window, GameField& field, int selectedRow, int selectedCol);
};



