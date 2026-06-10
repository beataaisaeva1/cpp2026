#include "GameField.h"
#include "Gem.h"
#include "GemFactory.h"
#include <utility>

GameField::GameField(int rows, int cols) : rows(rows), cols(cols) {
    cells.resize(rows);
    for (int i = 0; i < rows; i++) {
        cells[i].resize(cols);
    }
}

bool GameField::inside(int row, int col) const {
    return row >= 0 && row < rows && col >= 0 && col < cols;
}


int GameField::getRows() const {
    return rows;
}

int GameField::getCols() const {
    return cols;
}

Gem* GameField::getCell(int row, int col) const {
    return cells[row][col].get();
}

void GameField::setCell(int row, int col, std::unique_ptr<Gem> gem) {
    cells[row][col] = std::move(gem);
}

void GameField::swapCells(int row1, int col1, int row2, int col2) {
    std::swap(cells[row1][col1], cells[row2][col2]);
}

void GameField::fillField() {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            bool ok = false;
            while (!ok) {
                cells[i][j] = GemFactory::createNormalGem();
                int color = cells[i][j]->getColor();
                ok = true;
                if (j >= 2) {
                    if (cells[i][j - 1]->getColor() == color && cells[i][j - 2]->getColor() == color) {
                        ok = false;
                    }
                }
                if (i >= 2) {
                    if (cells[i - 1][j]->getColor() == color && cells[i - 2][j]->getColor() == color) {
                        ok = false;
                    }
                }
            }
        }
    }
}

void GameField::destroyCell(int row,int col) {
    cells[row][col] = nullptr;
}

void GameField::dropCells() {
    for (int col = 0; col < cols; col++) {
        int writeRow = rows - 1;
        for (int row = rows - 1; row >= 0; row--) {
            if (cells[row][col] != nullptr) {
                cells[writeRow][col] = std::move(cells[row][col]);
                writeRow--;
            }
        }
        while (writeRow >= 0) {
            cells[writeRow][col] = GemFactory::createNormalGem();
            writeRow--;
        }
    }
}



