#pragma once

#include <vector>

std::vector<std::pair<int, int>> cellsInRadius(int r, int c, int radius);

void bonusRepaint(int r, int c, int originalColor);

void bonusBomb(int r, int c);

void tryCreateBonus(int r, int c, int originalColor);

