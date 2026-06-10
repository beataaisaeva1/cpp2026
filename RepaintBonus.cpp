#include "RepaintBonus.h"
#include "GameField.h"
#include "Gem.h"
#include <vector>
#include <algorithm>
#include <random>

static std::random_device dev;
static std::mt19937 rng(dev());

RepaintBonus::RepaintBonus(int color) : Gem(color) {
}

bool RepaintBonus::isBonus() const {
    return true;
}

void RepaintBonus::activate(GameField& field, int row, int col) {
    std::vector<std::pair<int, int>> cells;

    for (int i = row - 3; i <= row + 3; i++) {
        for (int j = col - 3; j <= col + 3; j++) {
            if (field.inside(i, j) && !(i == row && j == col)) {            
                cells.push_back({ i,j });
            
        }
    }

    std::vector<std::pair<int, int>> variants;

    for (auto cell : cells) {
        int r = cell.first;
        int c = cell.second;

        if (abs(r - row) + abs(c - col) != 1) {      
            variants.push_back(cell);
        }
    }

    std::shuffle(variants.begin(), variants.end(), rng);

    Gem* center = field.getCell(row, col);
    if (center != nullptr) {
        center->setColor(color);
    }

    for (int i = 0; i < 2 && i < variants.size(); i++) {    
        int r = variants[i].first;
        int c = variants[i].second;

        Gem* gem = field.getCell(r, c);
        if (gem != nullptr) {
            gem->setColor(color);
        }
    }
}


