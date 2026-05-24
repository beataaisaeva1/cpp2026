#include <SFML/Graphics.hpp>
#include "game.h"
#include "draw.h"

int main() {
    fillField();

    sf::RenderWindow window(sf::VideoMode(COLS * CELL_SIZE, ROWS * CELL_SIZE), "GEMS");

    int selectedRow = -1;
    int selectedCol = -1;

    while (window.isOpen()) {
        sf::Event event;

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    int col = event.mouseButton.x / CELL_SIZE;
                    int row = event.mouseButton.y / CELL_SIZE;

                    if (!inside(row, col)) {
                        continue;
                    }
                    if (selectedRow == -1) {
                        selectedRow = row;
                        selectedCol = col;
                    }
                    else {
                        if (areNeighbors(selectedRow, selectedCol, row, col)) {
                            std::swap(field[selectedRow][selectedCol], field[row][col]);
                            std::vector<std::pair<int, int>> matches = findMatches();
                            if (matches.empty()) {
                                std::swap(field[selectedRow][selectedCol], field[row][col]);
                            }
                            else {
                                processMatches();
                            }
                        }
                        selectedRow = -1;
                        selectedCol = -1;
                    }
                }
            }
        }
        window.clear(sf::Color(40, 40, 40));
        drawField(window, selectedRow, selectedCol);
        window.display();
    }
    return 0;
}
