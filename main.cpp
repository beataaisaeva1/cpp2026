#include <SFML/Graphics.hpp>
#include "GameField.h"
#include "GameLogic.h"
#include "Renderer.h"

int main() {
    GameField field(8, 8);
    GameLogic logic(field);
    do {
        field.fillField();
    } while (!logic.findMatches().empty());   

    Renderer renderer(70);
    sf::RenderWindow window(sf::VideoMode(field.getCols() * 70, field.getRows() * 70), "GEMS");

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
                    int col = event.mouseButton.x / 70;
                    int row = event.mouseButton.y / 70;
                    if (!field.inside(row, col)) {
                        continue;
                    }
                    if (selectedRow == -1) {
                        selectedRow = row;
                        selectedCol = col;
                    }
                    else {
                        if (logic.areNeighbors(selectedRow, selectedCol, row, col)) {
                            field.swapCells(selectedRow, selectedCol, row, col);
                            std::vector<std::pair<int, int>> matches = logic.findMatches();
                            if (matches.empty()) {
                                field.swapCells(selectedRow, selectedCol, row, col);
                            }
                            else {
                                logic.processMatches();
                            }
                        }
                        selectedRow = -1;
                        selectedCol = -1;
                    }
                }
            }
        }
        window.clear(sf::Color(40, 40, 40));

        renderer.draw(window, field, selectedRow, selectedCol);

        window.display();
    }
    return 0;
}




