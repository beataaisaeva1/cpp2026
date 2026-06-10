#include "GameLogic.h"
#include "GameField.h"
#include "Gem.h"
#include "BombBonus.h"
#include "RepaintBonus.h"
#include "GemFactory.h"
#include <queue>
#include <random>
#include <algorithm>
#include <cmath>
#include <iostream>

static std::random_device dev;
static std::mt19937 rng(dev());

GameLogic::GameLogic(GameField& field) : field(field) {
}

bool GameLogic::areNeighbors(int r1, int c1, int r2, int c2) const {
    return abs(r1 - r2) + abs(c1 - c2) == 1;
}

std::vector<std::pair<int, int>> GameLogic::findMatches() {
    int rows = field.getRows();
    int cols = field.getCols();

    std::vector<std::vector<bool>> visited(rows, std::vector<bool>(cols, false));

    std::vector<std::pair<int, int>> result;

    int dr[4] = {-1,1,0,0};
    int dc[4] = {0,0,-1,1};

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (visited[i][j]) {
                continue;
            }

            Gem* start = field.getCell(i, j);
            if (start == nullptr) {
                continue;
            }
            int color = start->getColor();

            std::vector<std::pair<int, int>> group;

            std::queue<std::pair<int, int>> q;
            q.push({ i,j });

            visited[i][j] = true;

            while (!q.empty()) {
                std::pair<int, int> current = q.front();
                q.pop();

                int r = current.first;
                int c = current.second;

                group.push_back({ r,c });

                for (int k = 0; k < 4; k++) {
                    int nr = r + dr[k];
                    int nc = c + dc[k];
                    if (!field.inside(nr, nc)) {
                        continue;
                    }
                    if (visited[nr][nc]) {
                        continue;
                    }

                    Gem* next = field.getCell(nr, nc);
                    if (next == nullptr) {
                        continue;
                    }

                    if (next->getColor() == color) {
                        visited[nr][nc] = true;

                        q.push({nr, nc});
                    }
                }
            }
            if (group.size() >= 3) {
                result.insert(result.end(), group.begin(), group.end());
            }
        }
    }
    return result;
}

void GameLogic::destroyMatches(const std::vector<std::pair<int, int>>& matches) {
    if (matches.empty()) {
        return;
    }

    std::uniform_int_distribution<int>indexDist(0, matches.size() - 1);
    int bonusIndex = indexDist(rng);

    for (int i = 0; i < matches.size(); i++) {
        int row = matches[i].first;
        int col = matches[i].second;

        Gem* gem = field.getCell(row, col);
        if (gem == nullptr) {
            continue;
        }

        int color =
            gem->getColor();

        if (i == bonusIndex) {
            tryCreateBonus(row, col, color);
        }

        field.destroyCell(row, col);
    }
}

void GameLogic::processMatches() {
    std::vector<std::pair<int, int>> matches = findMatches();

    while (!matches.empty()) {
        destroyMatches(matches);

        field.dropCells();
        matches = findMatches();
    }
}

std::vector<std::pair<int, int>>GameLogic::cellsInRadius(int row, int col, int radius) {
    std::vector<std::pair<int, int>> result;

    for (int i = row - radius; i <= row + radius; i++) {
        for (int j = col - radius; j <= col + radius; j++) {
            if (field.inside(i, j) && !(i == row && j == col)) {
                result.push_back({ i,j });
            }
        }
    }
    return result;
}

void GameLogic::tryCreateBonus(int row, int col, int color) {

    std::uniform_int_distribution<int> chanceDist(0, 99);

    int chance = chanceDist(rng);
    if (chance >= 20) {
        return;
    }

    std::vector<std::pair<int, int>> cells = cellsInRadius(row, col, 3);
    if (cells.empty()) {
        return;
    }

    std::uniform_int_distribution<int> cellDist(0, cells.size() - 1);
    std::pair<int, int> target = cells[cellDist(rng)];
    std::uniform_int_distribution<int> typeDist(0, 1);

    int type = typeDist(rng);
    if (type == 0) {
        std::cout << "Bonus: Repaint" << std::endl;
        RepaintBonus bonus(color);
        bonus.activate(field, target.first, target.second);
    }
    else {
        std::cout << "Bonus: Bomb" << std::endl;
        BombBonus bonus(color);
        bonus.activate(field, target.first, target.second);
    }
}



