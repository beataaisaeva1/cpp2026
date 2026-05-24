#include "bonuses.h"
#include "game.h"
#include <iostream>
#include <algorithm>
#include <random>

extern std::mt19937 rng;

std::vector<std::pair<int, int>> cellsInRadius(int r, int c, int radius) {
    std::vector<std::pair<int, int>> cells;

    for (int i = r - radius; i <= r + radius; i++) {
        for (int j = c - radius; j <= c + radius; j++) {
            if (inside(i, j) && !(i == r && j == c)) {
                cells.push_back({ i, j });
            }
        }
    }
    return cells;
}

void bonusRepaint(int r, int c, int originalColor) {
    std::vector<std::pair<int, int>> cells = cellsInRadius(r, c, 3);
    std::vector<std::pair<int, int>> variants;
    for (auto cell : cells) {
        if (!areNeighbors(r, c, cell.first, cell.second)) {
            variants.push_back(cell);
        }
    }

    random_shuffle(variants.begin(), variants.end());

    field[r][c] = originalColor;

    for (int i = 0; i < 2 && i < variants.size(); i++) {
        field[variants[i].first][variants[i].second] = originalColor;
    }
    std::cout << "Bonus: repaint\n";
}

void bonusBomb(int r, int c) {
    std::vector<std::pair<int, int>> cells;

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (!(i == r && j == c)) {
                cells.push_back({ i, j });
            }
        }
    }

    random_shuffle(cells.begin(), cells.end());

    field[r][c] = -1;

    for (int i = 0; i < 4 && i < cells.size(); i++) {
        field[cells[i].first][cells[i].second] = -1;
    }
    std::cout << "Bonus: bomb\n";
}

void tryCreateBonus(int r, int c, int originalColor) {
    std::uniform_int_distribution<int> distChance(0, 99);
    int chance = distChance(rng);

    if (chance >= 20) {
        return;
    }

    std::vector<std::pair<int, int>> cells = cellsInRadius(r, c, 3);

    if (cells.empty()) {
        return;
    }

    std::uniform_int_distribution<int> distCell(0, cells.size() - 1);
    std::pair<int, int> target = cells[distCell(rng)];

    std::uniform_int_distribution<int> distBonus(0, 1);
    int bonusType = distBonus(rng);

    if (bonusType == 0) {
        bonusRepaint(target.first, target.second, originalColor);
    }
    else {
        bonusBomb(target.first, target.second);
    }
}
