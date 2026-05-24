#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

extern const int ROWS;
extern const int COLS;
extern const int CELL_SIZE;
extern const int COLORS;

extern std::vector<std::vector<int>> field;
extern sf::Color colors[];

int randomColor();

bool inside(int r, int c);

bool areNeighbors(int r1, int c1, int r2, int c2);

void fillField();

std::vector<std::pair<int, int>> findMatches();

void destroyCells(std::vector<std::pair<int, int>> matches);

void dropCells();

void processMatches();

