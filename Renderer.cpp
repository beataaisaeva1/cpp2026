#include "Renderer.h"
#include "GameField.h"
#include "Gem.h"

Renderer::Renderer(int cellSize) : cellSize(cellSize) {
    colors[0] = sf::Color::Red;
    colors[1] = sf::Color::Blue;
    colors[2] = sf::Color::Green;
    colors[3] = sf::Color::Yellow;
    colors[4] = sf::Color::Magenta;
    colors[5] = sf::Color::Cyan;
}

void Renderer::draw(sf::RenderWindow& window, GameField& field, int selectedRow, int selectedCol) {
    for (int i = 0; i < field.getRows(); i++) {
        for (int j = 0; j < field.getCols(); j++) {
            Gem* gem = field.getCell(i, j);
            if (gem == nullptr) {
                continue;
            }

            sf::RectangleShape cell;
            cell.setSize(sf::Vector2f(cellSize - 4, cellSize - 4));

            cell.setPosition(j * cellSize + 2, i * cellSize + 2);

            cell.setFillColor(colors[gem->getColor()]);

            cell.setOutlineThickness(2);

            if (i == selectedRow && j == selectedCol) {
                cell.setOutlineColor(sf::Color::White);
            }
            else {
                cell.setOutlineColor(sf::Color::Black);
            }
            window.draw(cell);
        }
    }
}


