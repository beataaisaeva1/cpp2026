#include "game.h"
#include "bonuses.h"
#include <queue>
#include <random>
#include <algorithm>
#include <cmath>

std::random_device dev;
std::mt19937 rng(dev());

const int ROWS = 8;
const int COLS = 8;
const int CELL_SIZE = 70;
const int COLORS = 6;

std::vector<std::vector<int>> field(ROWS, std::vector<int>(COLS));

sf::Color colors[COLORS] = { sf::Color::Red, sf::Color::Blue, sf::Color::Green, sf::Color::Yellow, sf::Color::Magenta, sf::Color::Cyan };

int randomColor() {
    std::uniform_int_distribution<int> dist(0, COLORS - 1);
    return dist(rng);
}

bool inside(int r, int c) {
    return r >= 0 && r < ROWS && c >= 0 && c < COLS;
}

bool areNeighbors(int r1, int c1, int r2, int c2) {
    return abs(r1 - r2) + abs(c1 - c2) == 1;
}

void fillField() {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            field[i][j] = randomColor();
        }
    }
}

std::vector<std::pair<int, int>> findMatches() {
    std::vector<std::vector<bool>> visited(ROWS, std::vector<bool>(COLS, false));
    std::vector<std::pair<int, int>> result;

    int dr[4] = { -1, 1, 0, 0 };
    int dc[4] = { 0, 0, -1, 1 };

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (visited[i][j]) {
                continue;
            }
            int color = field[i][j];

            std::vector<std::pair<int, int>> group;
            std::queue<std::pair<int, int>> q;

            q.push({ i, j });

            visited[i][j] = true;

            while (!q.empty()) {
                std::pair<int, int> current = q.front();
                q.pop();
                int r = current.first;
                int c = current.second;
                group.push_back({ r, c });

                for (int k = 0; k < 4; k++) {
                    int nr = r + dr[k];
                    int nc = c + dc[k];
                    if (inside(nr, nc) && !visited[nr][nc] && field[nr][nc] == color) {
                        visited[nr][nc] = true;
                        q.push({ nr, nc });
                    }
                }
            }
            if (group.size() >= 3) {
                for (auto cell : group) {
                    result.push_back(cell);
                }
            }
        }
    }
    return result;
}

void destroyCells(std::vector<std::pair<int, int>> matches) {
    if (matches.empty()) {
        return;
    }

    std::uniform_int_distribution<int> distIndex(0, matches.size() - 1);
    int bonusIndex = distIndex(rng);

    for (int i = 0; i < matches.size(); i++) {
        int r = matches[i].first;
        int c = matches[i].second;

        if (i == bonusIndex) {
            int oldColor = field[r][c];
            tryCreateBonus(r, c, oldColor);
        }
        field[r][c] = -1;
    }
}

void dropCells() {
    for (int c = 0; c < COLS; c++) {
        int writeRow = ROWS - 1;
        for (int r = ROWS - 1; r >= 0; r--) {
            if (field[r][c] != -1) {
                field[writeRow][c] = field[r][c];
                writeRow--;
            }
        }
        while (writeRow >= 0) {
            field[writeRow][c] = randomColor();
            writeRow--;
        }
    }
}

void processMatches() {
    std::vector<std::pair<int, int>> matches = findMatches();

    while (!matches.empty()) {
        destroyCells(matches);
        dropCells();

        matches = findMatches();
    }
}
