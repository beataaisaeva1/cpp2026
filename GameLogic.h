#pragma once

#include <vector>
#include <utility>

class GameField;

class GameLogic {
private:
    GameField& field;
public:
    GameLogic(GameField& field);

    bool areNeighbors(int r1, int c1, int r2, int c2) const;

    std::vector<std::pair<int, int>> findMatches();

    void destroyMatches(const std::vector<std::pair<int, int>>& matches);

    void processMatches();

    std::vector<std::pair<int, int>> cellsInRadius(int row, int col, int radius);

    void tryCreateBonus(int row, int col, int color);
};

