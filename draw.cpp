#include "draw.h"
#include "game.h"

void drawField(sf::RenderWindow& window, int selectedRow, int selectedCol) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            sf::RectangleShape cell;
            cell.setSize(sf::Vector2f(CELL_SIZE - 4, CELL_SIZE - 4));
            cell.setPosition(j * CELL_SIZE + 2, i * CELL_SIZE + 2);
            cell.setFillColor(colors[field[i][j]]);
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
