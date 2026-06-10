#include "BombBonus.h"
#include "GameField.h"
#include <vector>
#include <algorithm>
#include <random>

static std::random_device dev;
static std::mt19937 rng(dev());

BombBonus::BombBonus(int color) : Gem(color) {

}

bool BombBonus::isBonus() const {
    return true;
}

void BombBonus::activate(GameField& field, int row, int col) {
    std::vector<std::pair<int, int>> cells;
    for (int i = 0; i < field.getRows(); i++) {
        for (int j = 0; j < field.getCols(); j++) {
            cells.push_back({ i,j });
        }
    }
    std::shuffle(cells.begin(), cells.end(), rng);

    field.destroyCell(row, col);

    for (int i = 0; i < 4 && i < cells.size(); i++) {
        field.destroyCell(cells[i].first, cells[i].second);
    }
}



