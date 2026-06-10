#include "Gem.h"

Gem::Gem(int color) : color(color) {
}

Gem::~Gem() {
}

int Gem::getColor() const {
    return color;
}

bool Gem::isBonus() const {
    return false;
}

void Gem::activate(GameField& field, int row, int col) {
}

void Gem::setColor(int color) {
    this->color = color;
}

