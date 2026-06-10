#pragma once

#include <vector>
#include <memory>
#include "Gem.h"

class Gem;

class GameField {
private:
    int rows;
    int cols;

    std::vector<std::vector<std::unique_ptr<Gem>>> cells;
public:
    GameField(int rows, int cols);

    bool inside(int row, int col) const;

    int getRows() const;
    int getCols() const;

    Gem* getCell(int row, int col) const;

    void setCell(int row, int col, std::unique_ptr<Gem> gem);

    void swapCells(int row1, int col1, int row2, int col2);

    void fillField();

    void dropCells();

    void destroyCell(int row, int col);
};

